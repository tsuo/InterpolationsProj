set terminal png size 1500,800
set output 'smooth.png'

set xlabel 'x'
set ylabel 'y'
set title 'Smoothing'
plot "smooth.txt" using 1:2 with linespoints pointtype 7
