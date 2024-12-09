
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

if [ $n -eq 1 ]
then
    gcc $filename
    echo "Compiled Successfully"

else if [ $n -eq 2 ]
then
    gcc $filename
    ./a.out
    echo "Compiled and run successfully"
else if [ $n -eq 3 ]
then
    echo "Printing the contents of the original file"
    cat hello.c
    

else if [ $n -eq 4 ]
then
    echo "listing the contents of current directory"
    ls
else 
  break
fi
fi
fi
fi

done
