#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int status;
	
	if(argc != 4){
		errx(1, "Invalid number of parameters");
	}
	
	//We are in father
	if(fork() > 0){		
		wait(&status);
		
		printf("PID %d: Process ended\n", getpid());
		
		if(WIFEXITED(status))
		        printf("with exit code %d\n", WEXITSTATUS(status));
		
	}
	else{
		//We are in son 
		if(fork() > 0){
			wait(&status);
			
			printf("PID %d: Process ended\n", getpid());
		
			if(WIFEXITED(status))
		        printf("with exit code %d\n", WEXITSTATUS(status));
		
			if(execlp(argv[3], argv[3], NULL, NULL) == -1){
					err(1, "exec command number 3");
			}
			
			printf("%d\n", getpid());
		}
		//We are in gradnson
		else{
			if(fork() > 0){
				wait(&status);
							
				printf("PID %d: Process ended\n", getpid());
						
				if(WIFEXITED(status))
		        printf("with exit code %d\n", WEXITSTATUS(status));
		        			
				if(execlp(argv[2], argv[2], NULL, NULL) == -1){
					err(1, "exec command number 2");
				}	
			}
			else{
				if(execlp(argv[1], argv[1], NULL, NULL) == -1){
					err(1, "exec command number 1");
				}	
			}
		}	
	}
	
	exit(0);
}
