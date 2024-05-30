#!/bin/zsh

# Script to create a backup of a directory

usage() {
  echo "Usage: $0 directory_to_backup"
  exit 1
}

if [ "$#" -ne 1 ]; then
  usage
fi

# Directory to backup
DIR_TO_BACKUP=$1

# Check if the specified directory exists
if [ ! -d "$DIR_TO_BACKUP" ]; then
  echo "Error: Directory '$DIR_TO_BACKUP' does not exist."
  exit 1
fi

BASE_NAME=$(basename "$DIR_TO_BACKUP")

# Create a timestamp
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")

# Backup file name
BACKUP_FILE="${BASE_NAME}_backup_${TIMESTAMP}.tar.gz"

# Create the backup
tar -czvf "$BACKUP_FILE" "$DIR_TO_BACKUP"

# Verify the backup was created successfully
if [ $? -eq 0 ]; then
  echo "Backup of '$DIR_TO_BACKUP' created successfully: $BACKUP_FILE"
else
  echo "Error: Failed to create backup."
  exit 1
fi

