#include <bits/stdc++.h>
#include <mysql.h>

char buff[1024];

struct database {
  char host[64];
  unsigned int port;
  char name[64];
  char user[64];
  char passwd[64];
};

int main() {
  MYSQL domjudge;
  bool res;

  std::unordered_map<std::string, int> school_id;

  database db;
  FILE *fconfig = fopen("database.conf", "r");
  fscanf(fconfig, "%[^:]:%i", db.host, &db.port);
  fscanf(fconfig, "%s", db.name);
  fscanf(fconfig, "%s", db.user);
  fscanf(fconfig, "%s", db.passwd);

  mysql_init(&domjudge);
  printf("[INFO]:Connecting...\n");
  if (!mysql_real_connect(&domjudge, db.host, db.user, db.passwd, db.name, db.port, NULL, CLIENT_FOUND_ROWS)) {
    printf("[INFO]:Database Connect Failed!\n");
    exit(-1);
  }
  printf("[INFO]:Database Connect Successfully!\n");

  mysql_query(&domjudge, "SET NAMES utf8mb4");
  mysql_query(&domjudge, "DELETE FROM team_affiliation");
  mysql_query(&domjudge, "DELETE FROM team");
  mysql_query(&domjudge, "DELETE FROM user WHERE userid > 2");
  mysql_query(&domjudge, "DELETE FROM userrole WHERE userid > 2");

  // Add School
  char shortname[64], sname[64];

  FILE *fschool = fopen("school_list.csv", "r");
  int sid = 1;
  while (fscanf(fschool, "%[^,],%[^\n]\n", shortname, sname) != EOF) {
    if (std::string(shortname).find("shortname") != std::string::npos)
      continue;

    school_id[shortname] = sid;
    sprintf(buff, "INSERT INTO team_affiliation (affilid, shortname, name, country) VALUES (%d, '%s', '%s', 'CHN')", sid, shortname, sname, shortname);
    res = mysql_query(&domjudge, buff);
    if (res) {
      printf("[ERROR]:School %s add error!\n", sname);
      exit(-1);
    }
    printf("[INFO]:School %s add success\n", sname);
    ++sid;
  }
  fclose(fschool);
  printf("[INFO]:School table closed\n");

  // Add User
  char uname[128], school[128];

  int uid = 1;
  FILE *user = fopen("user_list.csv", "r");
  while (fscanf(user, "%[^,],%[^\n]\n", uname, school) != EOF) {
    if (std::string(uname).find("name") != std::string::npos)
      continue;

    printf("[INFO]:Creating user %s\n", uname);

    sprintf(buff, "INSERT INTO team (teamid, name, categoryid, affilid, room) VALUES (%d, '%s', %d, %d, NULL)", uid, uname, uname[0] == '*' ? 2 : 3, school_id[school]);
    res = mysql_query(&domjudge, buff);
    if (res) {
      printf("[ERROR]:Add team %s error!\n", uname);
      exit(-1);
    }

    sprintf(buff, "INSERT INTO user (userid, username, name, enabled, teamid) VALUES (%d, 'team%d', '%s', 1, %d)", uid + 3, uid, uname, uid);
    res = mysql_query(&domjudge, buff);
    if (res) {
      printf("[ERROR]:Add user %s error!\n", uname);
      exit(-1);
    }

    sprintf(buff, "INSERT INTO userrole (userid, roleid) VALUES (%d, 3)", uid + 3);
    res = mysql_query(&domjudge, buff);
    if (res) {
      printf("[ERROR]:Userrole set error!\n");
      exit(-1);
    }

    printf("[INFO]:Sucessfuly insert user %s\n", uname);
    ++uid;
  }
  fclose(user);
  printf("[INFO]:User table closed\n");

  mysql_close(&domjudge);
  printf("[INFO]:Database disconnected\n");
  return 0;
}
