#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

//cat, sort, wc -l
int main(int argc, char* argv []){
	
	const int READ = 0;
	const int WRITE = 1;

	if (argc != 2){
		errx(1, "Invalid number of arguments");
	}	
	
	int fd[2];
	int fd2[2];
	
	if(pipe(fd) == -1){
		err(1, "pipe fd");
	}

	pid_t first_pid;

	if((first_pid = fork()) == -1){
		err(1, "err in first fork");
	}

	if(first_pid == 0){
		if(pipe(fd2) == -1){
			err(1, "pipe fd2");
		}
		
		pid_t second_pid; 

		if((second_pid = fork()) == -1){
			err(1, "second fork");
		}
		
		//Child of the child
		if(second_pid == 0){
             close (fd[WRITE]);
         	 close (fd[READ]);
			 close (fd2[WRITE]);
             
             dup2 (fd2[READ],0);
             close (fd2[READ]);

			
			//Third command
			if(execlp("wc", "wc", "-l", NULL) == -1){
				err(1, "error exec sort");
			}
			
		}
		//Child of the father
		else{
			close (fd[WRITE]);
            
            if((dup2(fd[READ],0)) == -1){
                err(1, "dup2 fd child");
            }
            close (fd[READ]);

            close (fd2[READ]);

            if((dup2(fd2[WRITE],1)) == -1){
                err(1, "dup2 fd2 child");
            }
            close (fd2[WRITE]);
			
			//Second command
			if(execlp("sort", "sort", NULL, NULL) == -1){
				err(1, "error exec sort");
			}
		}
	}
	//Father
	else{
		close(fd[READ]);

		if((dup2(fd[WRITE], 1)) == -1){
            err(1, "dup2 parent");
        }
		close(fd[WRITE]);

		//Last command
		if(execlp("cat", "cat", argv[1], NULL) == -1){
			err(1, "error exec sort");
		}
	}
	exit(0);
}
