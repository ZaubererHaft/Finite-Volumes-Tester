set term png
set output FILE.'.png'
set datafile separator ','

set yrange [0:1.5]

plot FILE u 1:($2+$4) with filledcurves x1 lt rgb "blue", FILE u 1:4 with filledcurves x1 lt rgb "brown"