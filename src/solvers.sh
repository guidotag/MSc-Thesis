#!/bin/bash

instance_dir="instance"
data_dir="data/solvers"
plot_dir="plot"
seed="1234567"
timeout="1h"

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
	solvers_name=$1[@]
	ns_name=$2[@]
	ps_name=$3[@]
	solvers=${!solvers_name}
	ns=${!ns_name}
	ps=${!ps_name}

	for solver in ${solvers[@]}; do
		printf "Running ${solver}\n"
		for n in ${ns[@]}; do
			data_file="${data_dir}/${solver}_${n}.dat"
			rm -f ${data_file}
			for p in ${ps[@]}; do
				instance_file="${instance_dir}/${n}_${p}.in"
				printf "\t on ${instance_file}..."
				result=`cat ${instance_file} | timeout ${timeout} ./solvers_timer --${solver}`
				if [ $? -eq "124" ]; then
					printf "timeout\n"
					return
				fi
				printf "${p} ${result}\n" >> ${data_file}
				printf "done\n"
			done
		done
	done
}

make

# solvers1=(bt_wb)
# ns1=(5)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(bt_wb)
# ns1=(10)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(bt_wb)
# ns1=(15)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wb)
# ns1=(5)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wb)
# ns1=(10)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wb)
# ns1=(15)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(bt_wob)
# ns1=(5)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(bt_wob)
# ns1=(10)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(bt_wob)
# ns1=(15)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wob)
# ns1=(5)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wob)
# ns1=(10)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1

# solvers1=(dp_wob)
# ns1=(15)
# ps1=(10 20 30 40 50 60 70 80 90 100)
# generate ns1 ps1
# timeit solvers1 ns1 ps1