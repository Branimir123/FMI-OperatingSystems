#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
	int status;
	char * text = "foobar";
    char c;

	if(argc != 2){
		errx(1, "Invalid number of parameters");
	}
	
    int fd = open(argv[1], O_WRONLY | O_TRUNC);
    
        if(fd < 0){
        err(1, "Error in opening file");
    }

	if(fork() > 0){		
        wait(&status);            
        
        int fd1 = open(argv[1], O_RDONLY);        
        int counter = 0;
        char interval = ' ';

        while(read(fd1, &c, 1)){
            if(counter == 2){
                write(1, &interval, 1);
                counter = 0;            
                write(1, &c, 1);
            }
            else{
                write(1, &c, 1);
            }
            counter++;
        }
	    
        close(fd1);		
	}
	else{
        write(fd, text, strlen(text));		
        close(fd);
	}
	
	exit(0);
}
