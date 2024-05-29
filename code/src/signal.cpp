#include "../headers/signal.hpp"

#include "iostream"

using namespace std;
using namespace std::complex_literals;

Signal::Signal ( int logSamples, float width, bool timeDomain )
{
    _width = width;
    _logSamples = logSamples;
    _N = 1 << logSamples;               // Nejlepsi mocneni - binarni posuv jednicky :D
    _dt = _width/_N;
    _fNyquist = 1.0f/_dt/2.0f;
    _df = _fNyquist/_N;
    _d.resize ( _N, 0.0f + 0.0if );
    _d.resize ( _N, 0.0f + 0.0if );
    _timeDomain = timeDomain;
}

Signal Signal::operator = ( function< complex<float> ( float ) > func )
{
    if ( _timeDomain )
    {
        for ( int n = 0; n < _N; n++ )
        {
            _d[n] = func (_dt*n);
        }
    }
    else
    {
        for ( int n = _N/2+1; n < _N; n++ )
        {
            _d[n] = func (_df*(n-_N));
        }
        for ( int n = 0; n <= _N/2; n++ )
        {
            _d[n] = func (_df*n);
        }
    }
    return *this;
}

Signal Signal::operator * ( function< complex<float> ( float ) > func )
{
    Signal OUT ( _logSamples, _width );
    OUT._timeDomain = _timeDomain;
    if ( _timeDomain )
    {
        for ( int n = 0; n < _N; n++ )
        {
            OUT(n) = _d[n] * func ( _dt*n );
        }
    }
    else
    {
        for ( int n = 0; n <= _N/2; n++ )
        {
            // cout << func(_df*n);
            OUT(n) = _d[n] * func ( _df*n );
        }
        for ( int n = _N/2+1; n < _N; n++ )
        {
            OUT(n) = _d[n] * func ( _df*n-_fNyquist );
        }
    }
    return OUT;
}

complex<float> & Signal::operator () ( int n )
{
    return _d[n];
}

void Signal::transform ( Domain domain )
{
    if ( domain == Domain::Time && _timeDomain != true )        _transform();
    if ( domain == Domain::Spectral && _timeDomain == true )    _transform();
    return ;
}

Signal::Domain Signal::domain ()
{
    if ( _timeDomain )  return Domain::Time;
    else                return Domain::Spectral;
}

int Signal::N () { return _N; }
float Signal::dt() { return _dt; }
float Signal::df() { return _df; }



ostream & operator << ( ostream & OUT, Signal & signal )
{
    if ( signal.domain() == Signal::Domain::Time )
    {
        for ( int n = 0; n < signal.N(); n++ )
        {
            OUT << signal.dt()*n << '\t' << real(signal(n)) << '\t' << imag(signal(n)) << '\n';
        }
    }
    else
    {
        for ( int n = signal.N()/2+1; n < signal.N(); n++ )
        {
            OUT << signal.df()*(n-signal.N()) << '\t' << real(signal(n)) << '\t' << imag(signal(n)) << '\n';
        }
        for ( int n = 0; n <= signal.N()/2; n++ )
        {
            OUT << signal.df()*n << '\t' << real(signal(n)) << '\t' << imag(signal(n)) << '\n';
        }
    }
    return OUT;
}



inline void Signal::_transform ()
{
    if ( _timeDomain )  four1 ( (float*) _d.data()-1, _N,  1 );
    else                four1 ( (float*) _d.data()-1, _N, -1 );
    for ( int n = 0; n < _N; n++ )
    {
    _d[n] /= sqrt(_N);
    }
    _timeDomain = !_timeDomain;
    return;
}

















