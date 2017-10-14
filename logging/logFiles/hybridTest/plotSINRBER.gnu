set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale y2

set y2tics nomirror
set ytics nomirror

set xlabel "Y position (m)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set y2label "log10 BER" rotate parallel offset 1.0

set key box
set pointsize 0.5

set term png size 1000,700 enhanced font 'Verdana,10'
set output "HybridTest.png" 

plot 'BERdata.csv' i 0 using 7:11 with points axes x1y2 title "BER VPPM",\
	 'SINRdata.csv' i 0 using 7:11 with points axes x1y1 title "SINR"


set term wxt

replot
