#!/bin/sh

# Run doxygen
doxygen framework.dox

# PDFLaTeX
rm doc.pdf
cd doxygen/latex
make
cp refman.pdf ../doc.pdf
cd ..

# HTML
ln -s html/index.html doc.html

