#!/bin/bash

echo "Enter the name of a directory:"
read dir_name


[ -d "$dir_name" ] || mkdir "$dir_name"
mkdir -p "$dir_name/Images" "$dir_name/Documents" "$dir_name/Others"


echo "Enter the number of files to generate for each subdirectory:"
read num_files

for i in $(seq 1 $num_files)
do

    file_name="file_$i"
    rand=$((i % 3))
    if [ $rand -eq 0 ]; then
        touch "$dir_name/Images/$file_name"
    elif [ $rand -eq 1 ]; then
        touch "$dir_name/Documents/$file_name"
    else
        touch "$dir_name/Others/$file_name"
    fi
done

echo "Summary of created directories and files:"
echo "Directory: $dir_name"
echo "Subdirectory: Images"
ls "$dir_name/Images"
echo "Subdirectory: Documents"
ls "$dir_name/Documents"
echo "Subdirectory: Others"
ls "$dir_name/Others"