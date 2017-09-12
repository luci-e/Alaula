set datafile separator ","
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale y2

set y2tics nomirror
set ytics nomirror

set xlabel "Incidence Angle (rad)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set y2label "log10 BER" rotate parallel offset 1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set output "data.png" 

plot 'logSlidingTest.csv' i 0 using 6:7 with lines axes x1y2 title "BER VPPM",\
	 'logSlidingTest.csv' i 1 using 6:7 with lines axes x1y1 title "SINR"


set term x11

replot
