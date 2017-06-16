#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main ()
{
	int status;
    char * fileName = "file.txt";
	char * text1 = "foo";
    char * text2 = "bar";
    //  char c;
	
    int fd = open(fileName, O_WRONLY |  O_CREAT, S_IRUSR | O_TRUNC);
    
        if(fd < 0){
        err(1, "Error in opening file");
    }

	if(fork() > 0){		
        //Remove wait for not waiting 
        wait(&status);            
        write(fd, text2, strlen(text2));
	}
	else{
        write(fd, text1, strlen(text1));		
	}
	
    close(fd);
	exit(0);
}
