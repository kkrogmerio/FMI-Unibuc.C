#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int functie(int n)
{
	printf("%d ",n);
	if(n==1){return 1;}
	if(n%2==0)
	return functie(n/2);
	else
	return functie(3*n+1);
}
int main(int argc,char*argv[])
{int i;
for(i=1;i<argc;++i)
{
pid_t pid=fork();
if(pid<0)
	perror("Fork failed");
if(pid==0)
{
	
	functie(atoi(argv[i]));
	printf("Parent %d Me%d\n",getppid(),getpid());
	exit(0);	
}
else{	
	
}
}
for(i=1;i<argc;++i)
	wait(NULL);

return 0;
}
