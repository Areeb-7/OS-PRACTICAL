#!/bin/zsh

# Script to display the last 20 lines of all .log files in the current directory

for log_file in *.log; do
  if [[ -e "$log_file" ]]; then
    echo "Displaying last 20 lines of: $log_file"
    echo "-------------------------------------"
    # Display the last 20 lines of the log file
    tail -n 20 "$log_file"
    echo "\n"
  else
    echo "No .log files found in the current directory."
    break
  fi
done

