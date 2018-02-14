#!/bin/bash

python ../plotting/nv_run2.py
python ../plotting/nv_run2_tex.py
pdflatex ./nv_run_second.tex
