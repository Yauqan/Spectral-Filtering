#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include "code/headers/signal.hpp"

#define WIDTH           float  ( 2000.0f )
#define REC_WIDTH       float  ( 1.0f )
#define NUM_EXP         int    ( 20 )
#define CUTOFF          float  ( 0.2f )
#define CUTSHARPNESS    float  ( 0.002f )

#define PI              float  ( 3.14159265f )

using namespace std;

complex<float> rectangle ( float x )
{
    if ( x <= REC_WIDTH && x >= 0.0 )   return 1.0;
    else                                return 0.0;
}

complex<float> lowpass ( float x )
{
    if ( abs(x) >= CUTOFF + CUTSHARPNESS )      return 0.0;
    else if ( abs(x) <= CUTOFF - CUTSHARPNESS ) return 1.0;
    else                                        return 1.0f/2.0f * ( 1.0f + cos ( PI/(2.0f*CUTSHARPNESS) * ( abs(x) - CUTOFF + CUTSHARPNESS ) ) );
}

complex<float> highpass ( float x )
{
    return 1.0f - lowpass (x);
}

int main()
{
    Signal sig ( NUM_EXP, WIDTH );
    sig = rectangle;
    ofstream f;

    f.open ( "result/rectangle.dat" );
    f << sig;
    f.close();

    sig.transform ( Signal::Domain::Spectral );

    f.open ( "result/rectangleSpectrum.dat" );
    f << sig;
    f.close();

    Signal sigF = sig * lowpass;
    Signal Lowpass ( NUM_EXP, WIDTH, false );
    Lowpass = lowpass;

    f.open ( "result/Lowpass.dat" );
    f << Lowpass;
    f.close();

    f.open ( "result/rectangleSpectrumFilteredLowpass.dat" );
    f << sigF;
    f.close();

    sigF.transform ( Signal::Domain::Time );

    f.open ( "result/rectangleFilteredLowpass.dat" );
    f << sigF;
    f.close();

    Signal sigH = sig * highpass;

    f.open ( "result/rectangleSpectrumFilteredHighpass.dat" );
    f << sigH;
    f.close();

    sigH.transform ( Signal::Domain::Time );

    f.open ( "result/rectangleFilteredHighpass.dat" );
    f << sigH;
    f.close();

    return 0;
}