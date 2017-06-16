#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>

int main (int argc, char* argv[])
{
	const int READ = 0;
	const int WRITE = 1;
	
	if (argc !=2){
		errx(1, "Invalid number of arguments");
	}
	
	//Initialize fd
	int fd[2];

	//Initialize pipe between processes
	pipe(fd);
	
	pid_t cat_pid;
	
	if ((cat_pid = fork()) == -1){
		err(1, "Error in forking cat");
	}
	
	if (cat_pid == 0){
		close(fd[READ]);
	
		if(dup2(fd[WRITE], 1) == -1){
			err(1, "dup2 in cat");
		}
		
		if(execlp("cat", "cat", argv[1], NULL) == -1){
			err(1, "executing cat");
		}
	}
	
	close(fd[1]);
	
	if(dup2(fd[READ], 0) == -1){
		err(1, "dup2 in parent");
	}
	
	if(execlp("sort", "sort", "-", NULL) == -1){
		err(1, "exec sort");
	}
	
	exit(0);
}
