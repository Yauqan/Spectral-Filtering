set terminal pdf size 20cm,10cm

set output "01-timeDomain.pdf"
set yrange [-0.1:1.1]
set xrange [0.0:2.0]
plot "rectangle.dat" with lines notitle
unset yrange
unset xrange

set output "02-SpectralDomain.pdf"
plot "rectangleSpectrum.dat" with lines notitle

set output "03-Lowpass.pdf"
plot "Lowpass.dat" with lines notitle

set output "04-SpectralDomainFiltered.pdf"
plot "rectangleSpectrumFilteredLowpass.dat" with lines title "Lowpass", "rectangleSpectrumFilteredHighpass.dat" with lines title "Highpass"

set output "05-timeDomainFiltered.pdf"
set yrange [-0.1:1.1]
set xrange [0.0:2.0]
plot "rectangleFilteredLowpass.dat" with lines title "Lowpass", "rectangleFilteredHighpass.dat" with lines title "Highpass"
