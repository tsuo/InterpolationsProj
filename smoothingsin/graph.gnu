set terminal png size 1500,600
set output 'smooth2.png'

set xlabel 'x'
set ylabel 'y'
set title 'Smoothing'
plot "smooth.txt" using 1:2 with linespoints
