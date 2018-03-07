#!/bin/bash

rm -r ../nv_log
python ../plotting/nv_log.py
python ../plotting/nv_overlaid.py
pdflatex ./nv_overlaid.tex
