set terminal png size 1500, 800
set output 'plot.png'

set xlabel 'x'
set ylabel 'y'
set title 'Scatter Plot'
plot "plot.txt" using 1:2 with points pointtype 5
