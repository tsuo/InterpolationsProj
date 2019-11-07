set terminal png size 800,600
set output 'smooth2.png'

set xlabel 'x'
set ylabel 'y'
set title 'Smoothing'
plot "smooth2.txt" using 1:2 with lines
