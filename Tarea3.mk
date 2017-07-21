Resultados_hw3.pdf : Resultados_hw3.tex  Ondas.pdf Orbitas.pdf
	pdflatex Resultados_hw3.tex

Ondas.pdf : Onda.py
	python Onda.py 

Orbitas.pdf : Plots_Planetas.py
	python  Plots_Planetas.py
