#!/bin/bash
echo "switch case"
num(){
   
    return $num
}


while true
do
    echo "Enter a number:"
    read n
   case $n in 
    1) num $n
     if [ $n -eq 1 ]
     then
        echo "Number is 1"
     fi
    ;;
    2) num $n
     if [ $n -eq 2 ]
     then
        echo "Number is 2"
     fi
    ;;
    3) break
    ;;
    *) echo "Invalid number"
    ;;
    esac
done


# #!/bin/bash
# add(){
   
#     echo "Sum is `expr $1 + $2`"
# }

# echo "adition of two numbers"
# add 10 20

# #!/bin/bash
# echo "else if ladder"
# echo "Enter a number"
# read n
# if [ $n -gt 0 ]
# then
#     echo "Number is positive"
# elif [ $n -lt 0 ]
# then
#     echo "Number is negative"
# else
#     echo "Number is zero"
# fi

# #!/bin/bash
# echo "nested loops"
# for i in 1 2 3
# do
#     echo "Outer loop: $i"
#     for j in 1 2 3
#     do
#    if [ $j -eq 1 ]
#    then
#     continue
#    fi
#         echo "Inner loop: $j"
#     done

# done


# #!/bin/bash
# echo "Enter numbers to sum them. Enter 0 to stop."

# sum=0

# while true
# do
#     echo "Enter a number:"
#     read num

#     if [ $num -eq 0 ]; then
#         break
#     fi

#     sum=$(expr $sum + $num)
#     echo "Current sum: $sum"
# done

# echo "Final sum: $sum"
# #!/bin/bash
# echo "testing -ge -gt -lt  -eq -ne  "
# echo "enter a number"
# read a

# while [ $a -lt 10 ]
# do

# echo "a is less than 10" 
# a=`expr $a + 1`
# echo "a is now $a"
# done


# #!/bin/bash
# echo "What do you want "
# read n
# for  i in $(ls)
# do 
# gedit i
# done 

# #!/bin/bash
# echo "table of any number ,write that number"
# read n
# for i in 1 2 3 4 5 6 7 8 9 10
# do 
# echo "$n * $i  = `expr $n \* $i` "
# done



# # #!/bin/bash

# echo "enter a value"
# read a
# echo "enter another value "
# read b

# c=`expr $a + $b`
# echo "sum is " $c

# d=`expr $a - $b`
# echo "difference is " $d

# e=`expr $a \* $b`
# echo "product is  "$e

# f=`expr $a / $b`
# echo "quotient is " $f
 


# cat << 'END' > program.c
# #include <stdio.h>
# #include <stdlib.h>
# #include <pthread.h>

# void* print_message(void* ptr) {
#     char* message = (char*)ptr;
#     printf("From %s\n", message);
#     return NULL;
# }

# int main() {
#     pthread_t thread1, thread2;
#     char* message1 = "thread 1";
#     char* message2 = "thread 2";

#     pthread_create(&thread1, NULL, print_message, (void*)message1);
#     pthread_create(&thread2, NULL, print_message, (void*)message2);
    
#     pthread_join(thread1, NULL);
#     pthread_join(thread2, NULL);

#     return 0;
# }
# END

# # Compile the C program with pthread library
# gcc program.c -lpthread -o program

# # Run the compiled program
# ./program
#