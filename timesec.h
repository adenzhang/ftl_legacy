namespace ftl {

    // SUBSECOND factor: 1, 10, 100, ... to 1000000000.
    template<size_t SUBSECOND>
    struct timesec {
        long          sec;   // seconds
        unsigned long nsec;  // sub-second defined as second/SUBSECOND

        timesec():sec(0), nsec(0){}
        timesec(long a) {
            sec = a/SUBSECOND;
            nsec = a%SUBSECOND;
        }
        timesec(long s, unsigned long sub):sec(s), nsec(sub) {}
        timesec& operator =(long a) {
            sec = a/SUBSECOND;
            nsec = a%SUBSECOND;
            return *this;
        }
        template < typename INTTYPE >
        operator INTTYPE () {
            return INTTYPE(sec + nsec * SUBSECOND);
        }
        template < size_t ANOTHERSUB >
        timesec(const timesec<ANOTHERSUB> a):sec(a.sec), nsec(ANOTHERSUB == SUBSECOND?a.nsec:(double)a.nsec*ANOTHERSUB/SUBSECOND) {}

        timesec& operator+=(const timesec& a) {
            nsec += a.nsec;
            long s = nsec/SUBSECOND;
            sec += a.sec + s;
            if(s) nsec %= SUBSECOND;
            return *this;
        }
        timesec& operator-=(const timesec& y) {
            timesec& x = *this;
            x.sec -= y.sec;
            if (x.nsec < y.nsec) {
                x.nsec += (SUBSECOND - y.nsec);
                --x.sec;
            }else{
                x.nsec -= y.nsec;
            }
            return *this;
        }

        friend bool operator <(const timesec& a, const timesec& b) {
            return a.sec < b.sec || a.sec == b.sec && a.nsec < b.nsec;
        }
        friend bool operator >(const timesec& a, const timesec& b) {
            return a.sec > b.sec || a.sec == b.sec && a.nsec > b.nsec;
        }
        friend bool operator ==(const timesec& a, const timesec& b) {
            return a.sec == b.sec && a.nsec == b.nsec;
        }
        friend timesec operator+ (const timesec& a, const timesec& b) {
            timesec res=a;
            return res += b;
        }
        friend timesec operator-(const timesec& a) {
            timesec res = a;
            res.sec = - res.sec;
            return res;
        }
        friend timesec operator- (const timesec& a, const timesec& b) {
            timesec res=a;
            return res -= b;
        }
    };

    typedef timesec<1000000000> timenano;   // nano sec
    typedef timesec<1000000>    timemicro;  //same as sys/timeval
    typedef timesec<1000>       timemilli;  // milli sec
    typedef timesec<1>          timesecond; // second

}  // namespace ftl
