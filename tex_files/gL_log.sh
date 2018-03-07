#!/bin/bash

rm -r ../gL_log
python ../plotting/gL_log.py
python ../plotting/gL_log_tex.py
pdflatex ./gL_log.tex
