#!/usr/bin/awk -f

{ sum += $1 }

END { print "Sum of values in the first column:", sum }

