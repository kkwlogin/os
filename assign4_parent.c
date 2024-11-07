#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int i,j;

void bubble(int arr[],int n)
{
  for(i=0;i<n-1;i++){
  for(j=0;j<n-i-1;j++){
  if(arr[j] > arr[j+1]){
   int temp = arr[j];
   arr[j] = arr[j+1];
   arr[j+1] = temp;
   }
  }
 }
}

int main(){
int n,i;
printf("Enter the number of elements in the array:");
scanf("%d",&n);

int arr[n];
printf("Enter the elements of the array to be sorted : ");
for(i=0;i<n;i++){
scanf("%d",&arr[i]);
}

bubble(arr,n);

printf("Parent sorted array:");
for(i=0;i<n;i++){
printf("\t");
printf("%d",arr[i]);
}

printf("\n");
pid_t pid = fork();

if(pid < 0 ){
perror("Fork Failed");
return 1;
} else if(pid == 0){
// child process

char *args[n+2];
args[0] = "./child";  //file name of child process
for(i=0;i<n;i++){
args[i+1] = (char *)malloc(10*sizeof(char));
sprintf(args[i+1],"%d",arr[i]);
}
args[n+1] = NULL;

execve(args[0],args,NULL);

perror("execve failed");
for(i=0;i<n;i++){
free(args[i]);
}
exit(1);
} else {
wait(NULL);
printf("Parent process completed.\n");
}

return 0;
}
