set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y
set autoscale y2

set y2tics nomirror
set ytics nomirror

set xlabel "Time (s)"
set ylabel "SINR (dB)" rotate parallel offset -1.0
set y2label "log10 BER" rotate parallel offset 1.0

set key box
set pointsize 0.5

set term png size 1000,700 enhanced font 'Verdana,10'
set output "DoubleNoWiFiTest.png" 

plot 'BERdata.csv' i 0 using ($4/1000):11 with points axes x1y2 title "BER VPPM r1",\
	 'BERdata.csv' i 1 using ($4/1000):11 with points axes x1y2 title "BER VPPM r2",\
	 'SINRdata.csv' i 0 using ($4/1000):11 with points axes x1y1 title "SINR r1",\
	 'SINRdata.csv' i 1 using ($4/1000):11 with points axes x1y1 title "SINR r2"


set term wxt

replot
