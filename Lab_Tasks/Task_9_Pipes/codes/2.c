#include <unistd.h>
#include<stdio.h>
int main()
{
int pfd[2];

pipe(pfd);

printf("pfd[0] = %d, pfd[1] = %d\n", pfd[0], pfd[1]);
}