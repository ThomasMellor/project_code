#!/bin/bash

python ../plotting/gL_log.py
python ../plotting/gL_log_tex.py
pdflatex ./gL_log.tex
