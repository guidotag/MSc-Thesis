#$1 = file name (no extension)
input_file=${1}.svg
output_file=${1}.pdf
inkscape -D -z --file=$input_file --export-pdf=$output_file --export-latex
