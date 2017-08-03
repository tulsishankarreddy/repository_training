#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int a = 10;

int main()
{
	pid_t pid;


	int b = 20;
	char *p = NULL;

	if(NULL == (p = (char *)malloc(sizeof(char) * 10))) {
		printf("malloc is failed \n");
		exit(1);
	}
	strcpy(p, "hello");
	pid = vfork();

	




	if(pid > 0) {
		printf("parent process\n");
		printf("global %d, add = %p \n",a,&a);
		printf("local %d,add = %p \n",b,&b);
		printf("heap %s, add = %p \n",p,&p);
		}
	else if(pid == 0) {
		b = 10;
		a = 15;
		strcpy(p, "hii");
		printf("child process\n");
		printf("global %d, add = %p \n",a,&a);
		printf("local %d,add = %p \n",b,&b);
		printf("heap %s, add = %p \n",p,&p);
		exit(0);
		}
	else 
		printf("fork is failed\n");

	return 0;
}
