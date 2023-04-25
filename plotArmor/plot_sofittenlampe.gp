set term png
set out "plot_sofittenlampe.png"
set title "Spannung an Lampe"
set xlabel "time"
set ylabel "U in V"
set grid
plot "plot_sofittenlampe.txt" using :1 title "" with lines
