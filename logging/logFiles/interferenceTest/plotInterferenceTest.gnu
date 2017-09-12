set datafile separator ","
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

set term png size 1000,700 enhanced font 'Verdana,10'
set output "data.png"

plot 'logInterferenceTest.csv' i 0 using 6:7 with lines axes x1y2 title "BER VPPM conn 1",\
	 'logInterferenceTest.csv' i 1 using 6:7 with lines axes x1y2 title "BER VPPM conn 2",\
 	 'logInterferenceTest.csv' i 2 using 6:7 with lines axes x1y1 title "SINR conn 1",\
 	 'logInterferenceTest.csv' i 3 using 6:7 with lines axes x1y1 title "SINR conn 2"
	 


set term x11
replot
