set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y

set ytics nomirror

set xlabel "Time (s)"
set ylabel "Throughput (byte/s)" rotate parallel offset -1.0

set key box

set term png size 1000,700 enhanced font 'Verdana,10'
set output "InterferenceTestThroughput.png"

plot 'logInterferenceTest.csv' i 4 using ($4/1000):6 with lines axes x1y1 title "Throughput"

set term x11
replot
