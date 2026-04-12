set terminal pngcairo size 1000,700
set datafile separator whitespace
set grid
set key top left

# -------------------------
# BUBBLE
# -------------------------
set output 'bubble.png'
set title 'Bubble: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Kb = 1.43e-6
plot '../dat/bubble.dat' using 1:2 with linespoints title 'T(n)', \
     Kb*x*x with lines lw 2 title 'K*n^2'

# -------------------------
# INSERTION
# -------------------------
set output 'insertion.png'
set title 'Insertion: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Ki = 4.7e-7
plot '../dat/insertion.dat' using 1:2 with linespoints title 'T(n)', \
     Ki*x*x with lines lw 2 title 'K*n^2'

# -------------------------
# SELECTION
# -------------------------
set output 'selection.png'
set title 'Selection: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Ks = 2.79e-7
plot '../dat/selection.dat' using 1:2 with linespoints title 'T(n)', \
     Ks*x*x with lines lw 2 title 'K*n^2'

# -------------------------
# MERGESORT
# -------------------------
set output 'mergesort.png'
set title 'Mergesort: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Km = 1.1e-5
plot '../dat/mergesort.dat' using 1:2 with linespoints title 'T(n)', \
     Km*x*log(x) with lines lw 2 title 'K*n*log(n)'

# -------------------------
# QUICKSORT
# -------------------------
set output 'quicksort.png'
set title 'Quicksort: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Kq = 7.0e-6
plot '../dat/quicksort.dat' using 1:2 with linespoints title 'T(n)', \
     Kq*x*log(x) with lines lw 2 title 'K*n*log(n)'

# -------------------------
# HEAPSORT
# -------------------------
set output 'heapsort.png'
set title 'Heapsort: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Kh = 1.15e-5
plot '../dat/heapsort.dat' using 1:2 with linespoints title 'T(n)', \
     Kh*x*log(x) with lines lw 2 title 'K*n*log(n)'

# -------------------------
# FIBONACCI
# -------------------------
set output 'fibonacci.png'
set title 'Fibonacci: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
phi = (1+sqrt(5))/2.0
Kf = 1.66e-6
plot '../dat/fibonacci.dat' using 1:2 with linespoints title 'T(n)', \
     Kf*(phi**x) with lines lw 2 title 'K*phi^n'

# -------------------------
# HANOI
# -------------------------
set output 'hanoi.png'
set title 'Hanoi: T(n) vs K*f(n)'
set xlabel 'n'
set ylabel 'Tiempo (ms)'
Kho = 2.9e-6
plot '../dat/hanoi.dat' using 1:2 with linespoints title 'T(n)', \
     Kho*(2**x) with lines lw 2 title 'K*2^n'