#!/bin/bash

rm -r ../nv_log
python ../plotting/nv_log.py
python ../plotting/nv_overlaid_anitrop.py_.py
pdflatex ./nv_overlaid_anistropic.tex
