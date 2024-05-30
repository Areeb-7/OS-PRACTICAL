#!/bin/zsh

# Script to find and delete all files with a .tmp extension

find . -type f -name "*.tmp" -exec rm -v {} \;

