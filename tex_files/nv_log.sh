#!/bin/bash

python ../plotting/nv_log.py
python ../plotting/nv_log_tex.py
pdflatex ./nv_log_tex.tex
