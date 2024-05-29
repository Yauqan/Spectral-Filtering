#ifndef SIGNAL
#define SIGNAL

#include <functional>
#include <vector>
#include <complex>
#include <ostream>
#include "four1.h"

class Signal
{
    public: enum Domain
    {
        Time,
        Spectral,
    };
    
    public:
        Signal ( int logSamples, float width, bool timeDomain = true );
        Signal operator = ( std::function< std::complex<float> ( float ) > func );
        Signal operator * ( std::function< std::complex<float> ( float ) > func );
        std::complex<float> & operator () ( int n );
        void transform ( Domain domain );
        Domain domain ();
        int N();
        float dt();
        float df();
    private:
        bool _timeDomain;
        std::vector<std::complex<float>> _d;
        float _width;
        int _N;
        float _dt;
        float _fNyquist;
        float _df;
        int _logSamples;

        inline void _transform ();
};

std::ostream & operator << ( std::ostream & OUT, Signal & signal );

#endif