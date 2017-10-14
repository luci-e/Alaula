set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "Time (s)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set zlabel "Incidence angle (rad)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set view 60,145
set output "DoubleHybridTestSINR3D.png" 

splot 'logDoubleHybridTest.csv' i 2 using ($4/1000):10:11 title "SINR conn1",\
	  'logDoubleHybridTest.csv' i 3 using ($4/1000):10:11 title "SINR conn2"

set term x11

replot
