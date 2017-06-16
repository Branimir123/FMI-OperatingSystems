#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int status;
	
	if(argc != 2){
		errx(1, "Invalid number of parameters");
	}
	
	//We are in father
	if(fork()>0){
		wait(&status);
		if(status == 0){
			printf("%s", argv[1]);
		}
	}
	//We are in son
	else{
		if(execlp(argv[1], argv[1], NULL, NULL) == -1){
			err(1, "exec command");
		}	
	}
	
	exit(0);
}
