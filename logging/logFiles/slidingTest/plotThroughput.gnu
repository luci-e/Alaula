set datafile separator ";"
set datafile commentschars "#"
set nohidden3d

set autoscale x
set autoscale y

set ytics nomirror

set xlabel "Y position (m)"
set ylabel "Throughput log10 (byte/s)" rotate parallel offset -1.0

set key box
set pointsize 0.5

set term png size 1000,700 enhanced font 'Verdana,10'
set output "SlidingTestThroughput.png"

plot 'throughputData.csv' i 0 using ($4/1000*0.5):(log10($6/($4/1000))) with points axes x1y1 title "Throughput"

set term wxt
replot
