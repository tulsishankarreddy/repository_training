#include "errors.h"
#include <signal.h>

int status;

#if 1
int main( void )
{
	int seconds;
	char line[120];
	char message[64];
	pid_t pid; // process ID variable
	
	while(1) {
       /* do{
            status = waitpid(-1, NULL, WNOHANG);   
            if(status == -1)
                break;

        }while(status != 0);
*/

		printf("\nAlarm>");
		if(fgets(line, sizeof(line), stdin) == NULL) exit(0);

		if(strlen(line) <= 1) continue;
		//if given string length is less than = 1 it again prompts for input

		pid = fork ();

		if (pid > 0){
	/*		if(-1 == (status = waitpid(-1, &status, WNOHANG))){
				printf("waitpid failed \n");
				exit(1);
			}
*/
		signal(SIGCHLD, SIG_IGN);//if child is terminated ignore

		}else if (pid == 0) {
			// child process where sleep takes given input seconds as alarm
			if(sscanf(line, "%d %64[^\n]", &seconds, message) < 2) {
				fprintf(stderr, "Bad command \n");
			} else {
				sleep(seconds);
				printf("(%d) %s \n", seconds, message);
			}
			exit (0);//after printing child will exit
		} else {
			perror ("fork failed");
		}
	}

}
#endif
