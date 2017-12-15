#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
main() {

	int fd[2];
	int write_fd,read_fd;
	int ret=0;	
	pipe(fd);
	read_fd=fd[0];
	write_fd=fd[1];	
	ret=fork();

	if (ret!=0) {
		FILE *stream;
		close(read_fd);
		stream=fdopen(write_fd,"w");
		fprintf(stream,"Write to pipe\n");
		fprintf(stream,"10\n");
		fprintf(stream,"@\n");
		fprintf(stream,"1\n");
		fflush(stream);
		sleep(2);	
		close(write_fd);
		waitpid(0,NULL,0);	

	} else {
		FILE *stream;
		char buff[20];
		close(write_fd);
//		stream=fdopen(read_fd,"r");
//		fgets(buff,sizeof(buff),stream);
//		fputs(buff,stdout);
//		fflush(stream);
//		close(read_fd);
		dup2(read_fd,STDIN_FILENO);
		execlp("sort","sort",NULL);
		close(read_fd);
	}	
	
}
