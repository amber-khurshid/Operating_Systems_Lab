
#!/bin/bash

echo "Enter the file name: "
read filename

touch $filename

echo "How many lines do you want to enter?"
read n

# not equal to 0
while [ $n -ne 0 ]
do
    echo "Enter the line: "
    read line
    echo $line >> $filename
    n=`expr $n - 1`
done

# Display the first 5 lines of the file
firstfivelines(){
echo "First 5 lines of the file:"
head -n 5 $filename
}
lastfivelines(){
# Display the last 5 lines of the file
echo "Last 5 lines of the file:"
tail -n 5 $filename
}

wordcount(){
# Display the total word count in the file
echo "Total word count in the file:"
wc -w < $filename
}

while : : 
do 

echo "Enter 1 to print first five lines"
echo "Enter 2 to print last five lines"
echo "Enter 3 to count words in the file"
echo "Enter any other number to exit"

read num

case $num in

1)
firstfivelines ;;

2)
lastfivelines ;;

3)
wordcount ;;

*) break;;

esac

done
