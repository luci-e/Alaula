set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "Time (s)"
set ylabel "log10(BER)" rotate parallel offset -1.0
set zlabel "Incidence angle (rad)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set view 60,141
set output "DoubleHybridTestBER3D.png" 

splot 'logDoubleHybridTest.csv' i 0 using ($4/1000):10:11 title "BER conn1",\
	  'logDoubleHybridTest.csv' i 1 using ($4/1000):10:11 title "BER conn2"
	  
set term x11

replot
