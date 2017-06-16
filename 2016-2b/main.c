#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char* argv[])
{
	int waitStatus;
	char cmd[32];
	int i = 0;
	char * arr = argv[2];
	printf("%s", arr);
	
	if(argc != 1){
		errx(1, "Invalid arguments count");
	}
	
	while(1){
		write(1, "> ", 2);
		
		while( ( read ( 0 , &cmd[i] , 1) ) && cmd[i] != '\n' ){
			if (cmd[i] == ' ' || cmd[i] == '\t'){
				continue;
			}
			else{
				++i;
			}
		}
		
		if ( cmd[i] == '\n'){
			cmd[i] = '\0';
		}
		
		if (strcmp(cmd,"exit") == 0){
			exit(0);
		} 
		else {
			if ( fork() ) {
				wait(&waitStatus);
				i=0;
			}
			else{
				if( execlp(cmd,cmd, NULL) < 0){
					printf("cannot execute %s\n", cmd);
					exit(1);
				}
			}
		}
	}
}
