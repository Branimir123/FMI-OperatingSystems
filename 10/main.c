#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char * argv[])
{
	int status;
    
    if(argc != 3){
        errx(1, "Invalid argument count");
    }    

	if(fork() > 0){		
        wait(&status);            
        
        if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
            if(execlp(argv[2], argv[2], NULL, NULL) == -1){
		        err(1, "exec command number 2");
		    }
        }
        else{
            exit(1);
        }
	}
	else{
        if(execlp(argv[1], argv[1], NULL, NULL) == -1){
		    err(1, "exec command number 1");
		}
	}
	
	exit(0);
}
