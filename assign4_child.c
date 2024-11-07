#include<stdio.h>
#include<stdlib.h>

int i;

int main(int argc,char * argv[]){
if(argc < 2){
printf("No array elements received.\n");
return 1;
}

printf("Child process received array in reverse order:");
for(i=argc-1;i>0;i--){
printf("\t");
printf("%s",argv[i]);
}
printf("\n");

return 0;
}
