set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "Distance (m)"
set ylabel "Incidence angle (rad)"
set zlabel "SNR (dB)" rotate parallel offset -3.0

set key box
set pointsize 2.0
set view 76, 276, 1.0, 1.0

set term png
set output "data2.png"

splot 'log.csv' using 5:7:8

#set term x11

#replot
