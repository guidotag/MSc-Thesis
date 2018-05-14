#!/bin/bash

base_dir=`pwd`
instance_dir="instance"
data_dir="data/bounds"
plot_dir="plot"
seed="1234567"

function generate {
	ns_name=$1[@]
	ps_name=$2[@]
	ns=${!ns_name}
	ps=${!ps_name}

	printf "Creating instances\n"
	for n in ${ns[@]}; do
		for p in ${ps[@]}; do
			instance_file="${instance_dir}/${n}_${p}.in"
			printf "\t ${instance_file}..."
			printf "${seed} ${n} ${n} ${p}" | ./generator > ${instance_file}
			printf "done\n"
		done
	done
}

function timeit {
	bounds_name=$1[@]
	ns_name=$2[@]
	ps_name=$3[@]
	bounds=${!bounds_name}
	ns=${!ns_name}
	ps=${!ps_name}

	for bound in ${bounds[@]}; do
		printf "Running ${bound}\n"
		for n in ${ns[@]}; do
			data_file="${data_dir}/${bound}_${n}.dat"
			rm -f ${data_file}
			for p in ${ps[@]}; do
				instance_file="${instance_dir}/${n}_${p}.in"
				printf "\t on ${instance_file}..."
				printf "${p} " >> ${data_file}
				cat ${instance_file} | ./bounds_timer --${bound} >> ${data_file}
				printf "\n" >> ${data_file}
				printf "done\n"
			done
		done
	done
}

make

# # experiment 1
# bounds1=(dist_x3)
# ns1=(5 10 20 30)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit bounds1 ns1 ps1

# # experiment 2
# bounds1=(clients_count dist_x2 mst vc vc_mst)
# ns1=(5 10 20 30 40 50 60 70 80 90 100)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit bounds1 ns1 ps1

# plotting
bounds1=(clients_count dist_x2 dist_x3 mst vc vc_mst)
ns1=(5 10 20 30 40 50 60 70 80 90 100)
printf "Plotting density vs. value\n"
cd ${plot_dir}
for n in ${ns1[@]}; do
	printf "\t for n = ${n}..."
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" bounds_density_vs_value_epslatex.plt
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" bounds_density_vs_value_png.plt
	printf "done\n"
done
cd ..

bounds1=(dist_x3)
ns1=(5 10 20 30)
printf "Plotting density vs. time (for dist_x3)\n"
cd ${plot_dir}
for n in ${ns1[@]}; do
	printf "\t ${data_dir} for n = ${n}..."
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" dist_x3_density_vs_time_epslatex.plt
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" dist_x3_density_vs_time_png.plt
	printf "done\n"
done
cd ..

bounds1=(clients_count dist_x2 mst vc vc_mst)
ns1=(5 10 20 30 40 50 60 70 80 90 100)
printf "Plotting density vs. time (for all but dist_x3)\n"
cd ${plot_dir}
for n in ${ns1[@]}; do
	printf "\t ${data_dir} for n = ${n}..."
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" bounds_density_vs_time_epslatex.plt
	gnuplot -e "data_dir='${base_dir}/${data_dir}" -e "n=${n}" bounds_density_vs_time_png.plt
	printf "done\n"
done
cd ..