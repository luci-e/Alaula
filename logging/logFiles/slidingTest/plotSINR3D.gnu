set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "X position (m)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set zlabel "Incidence angle (rad)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set view 56,123
set output "slidingTestSINR3D.png" 

splot 'logSlidingTest.csv' i 1 using 6:10:11 title "SINR"

set term x11

replot
