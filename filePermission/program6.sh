#!/bin/zsh

# Script to list all files in the current directory with their sizes

ls -lh | awk '
BEGIN {
    print "Filename\t\tSize"
    print "---------------------------------"
}
{
    if (NR > 1) { 
        printf "%-20s\t%s\n", $9, $5
    }
}
'

