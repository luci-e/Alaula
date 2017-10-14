set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "Y position (m)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set zlabel "Incidence angle (rad)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set view 45,155
set output "HybridTestSINR3D.png" 

splot 'SINRdata.csv' i 0 using 7:10:11 title "SINR conn1",\
	  'SINRdata.csv' i 1 using 7:10:11 title "SINR conn2"

set term x11

replot
