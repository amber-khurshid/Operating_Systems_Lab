
#!/bin/bash

echo "Enter the file name: "
read filename
touch $filename


#copy contents from hello.c to filename
cat  hello.c > $filename


# while 1 loop

while : : 

do

echo "Enter 1 to compile"
echo "Enter 2 to compile and run"
echo "Enter 3 to print the contents of the original file"
echo "Enter 4 to print the contents of the current directory"
echo "Enter any other number command to exit"

read n

case $n in 

1) gcc $filename
    echo "Compiled Successfully"
;;
2)  gcc $filename
    ./a.out
    echo "Compiled and run successfully"
;;

3)   cat hello.c
     echo "Printing the contents of the original file"
;;

4)
  ls
  echo "listing the contents of current directory"
  ;;
*) break;;

esac

done
