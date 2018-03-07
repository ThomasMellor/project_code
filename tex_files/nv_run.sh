#!/bin/bash

rm -r ../rn_run
python ../plotting/nv_run.py
python ../plotting/nv_run_tex.py
pdflatex ./nv_run.tex
