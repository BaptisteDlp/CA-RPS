set title "Rock Paper Scisors Simulation"
set key
set yrange [0:1]
set xlabel "Time (sec)"
set ylabel "Density"
plot 'data/data.txt' using 1:2 with lines lw 2 lc 'red' title 'Rocks'
replot 'data/data.txt' using 1:3 with lines lw 2 lc 'green' title 'Papers'
replot 'data/data.txt' using 1:4 with lines lw 2 lc 'blue' title 'Scisors'

