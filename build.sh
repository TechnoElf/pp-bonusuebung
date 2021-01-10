#!/bin/bash

MAIN="main.tex"
BUILD_FILE_SUFFIXES=("aux" "bbl" "bcf" "blg" "idx" "ilg" "ind" "ist" "lof" "log" "lot" "out" "sig" "slo" "sls" "tdn" "tld" "tlg" "toc" "xml")

# Gather source files
ls chapters/*.tex | awk '{printf "\\input{%s}\n", $1}' > _chapters.tex

# Compile the document
pdflatex -shell-escape -file-line-error -halt-on-error -interaction=nonstopmode $MAIN
result=$?
if [ $result -eq 0 ]; then
    pdflatex -shell-escape -interaction=nonstopmode $MAIN > /dev/null 2> /dev/null
fi

# Clean up build files
rm _chapters.tex
for suffix in ${BUILD_FILE_SUFFIXES[@]}; do
    rm *.$suffix 2> /dev/null
    rm chapters/*.$suffix 2> /dev/null
    rm structure/*.$suffix 2> /dev/null
done

# Print a status message
if [ $result -eq 0 ]; then
    echo -e $'\e[1;32m'The document was compiled successfully.$'\e[0m'
else
    echo -e $'\e[1;31m'There were errors compiling the document.$'\e[0m'
fi
