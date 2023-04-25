set term png
set out "plot_potentiometers.png"
set title "Spannung Potentiometer 1 & 2"
set xlabel "time"
set ylabel "ADC in V"
set grid
plot "plot_potentiometers.txt" using :1 title "AE0" with lines,\
    "plot_potentiometers.txt" using :2 title "AE1" with lines
