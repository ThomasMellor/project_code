#!/bin/bash

python ../plotting/gL_run.py
python ../plotting/gL_run_tex.py
pdflatex ./gL_run.tex
