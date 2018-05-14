#args: data_dir n

output_file = 'bounds_epslatex/bounds_'.n.'_density_vs_value.tex'

clients_count_file = data_dir.'/clients_count_'.n.'.dat'
dist_x2_file = data_dir.'/dist_x2_'.n.'.dat'
dist_x3_file = data_dir.'/dist_x3_'.n.'.dat'
mst_file = data_dir.'/mst_'.n.'.dat'
vc_file = data_dir.'/vc_'.n.'.dat'
vc_mst_file = data_dir.'/vc_mst_'.n.'.dat'
# col1: p, col2: value, col3: exec time

reset

set terminal epslatex size 7.75cm, 6cm

set style line 1 linecolor rgb "red" linetype 1 pointtype 5 pointsize 1
set style line 2 lc rgb "orange" lt 1 pt 7 ps 1
set style line 3 lc rgb "brown" lt 1 pt 9 ps 1
set style line 4 lc rgb "purple" lt 1 pt 11 ps 1
set style line 5 lc rgb "green" lt 1 pt 13 ps 1
set style line 6 lc rgb "blue" lt 1 pt 15 ps 1
set style line 7 lc rgb "cyan" lt 1 pt 4 ps 1

set ylabel "Valor de la funci\\'on"
set xlabel "Porcentaje de clientes ($p$)"

set output output_file

plot clients_count_file using 1:2 with linespoints ls 1 title "\\texttt{clients\\_count}", \
	dist_x2_file using 1:2 with linespoints ls 2 title "\\texttt{dist\\_x2}", \
	dist_x3_file using 1:2 with linespoints ls 3 title "\\texttt{dist\\_x3}", \
	mst_file using 1:2 with linespoints ls 4 title "\\texttt{mst}", \
	vc_file using 1:2 with linespoints ls 5 title "\\texttt{vc}", \
	vc_mst_file using 1:2 with linespoints ls 6 title "\\texttt{vc\\_mst}"
		
unset output
