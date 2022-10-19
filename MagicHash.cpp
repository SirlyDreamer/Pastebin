struct magic_hash {
    template<class T>
    size_t operator()(const T &eax) const {
        static const size_t shift(chrono::system_clock::now().time_since_epoch().count());
        size_t o(shift);
        for (auto &e: eax) {
            o += e;
            o += 0x9e3779b97f4a7c15;
            o = (o ^ (o >> 30)) * 0xbf58476d1ce4e5b9;
            o = (o ^ (o >> 27)) * 0x94d049bb133111eb;
        }
        return o ^ (o >> 31);
    }
};