#include<stdio.h>

int main (int argc, char **argv) {

int a =argc;

char *b;
if (a!=0) {
 b=argv[0];
}
b=*argv[1];

printf("%s %s %s \n",argv[0],argv[1],argv[2]);
abort();

return 0;

}
