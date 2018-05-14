.PHONY: clean tesis

tesis: tesis.tex tesis.bib
	pdflatex tesis.tex
	bibtex tesis
	pdflatex tesis.tex
	pdflatex tesis.tex

clean:
	rm -f tesis.aux
	rm -f tesis.toc
	rm -f tesis.blg
	rm -f tesis.log
	rm -f tesis.bbl
	rm -f tesis.synctex.gz
	rm -f tesis.out