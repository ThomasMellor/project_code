#!/bin/bash

rm ../gL_run_second
python ../plotting/gL_run2.py
python ../plotting/gL_run2_tex.py
pdflatex ./gL_run_second.tex
