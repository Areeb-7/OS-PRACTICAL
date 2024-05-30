#!/bin/zsh

# Script to rename all .txt files to .bak in the current directory

for txt_file in *.txt; do
  if [[ -e "$txt_file" ]]; then
    # Constructing the new filename with .bak extension
    bak_file="${txt_file%.txt}.bak"
    # Renaming the file
    mv -v "$txt_file" "$bak_file"
  else
    echo "No .txt files found in the current directory."
    break
  fi
done

