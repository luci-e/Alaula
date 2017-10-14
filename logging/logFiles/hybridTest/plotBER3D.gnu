set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale z

set xlabel "Y position (m)"
set ylabel "log10(BER)" rotate parallel offset -1.0
set zlabel "Incidence angle (rad)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set view 55,33
set output "HybridTestBER3D.png" 

splot 'BERdata.csv' i 0 using 7:10:11 title "BER conn1",\
	  'BERdata.csv' i 1 using 7:10:11 title "BER conn2"
	  
set term x11

replot
