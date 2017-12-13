#include<stdio.h>
#include<signal.h>
#include<string.h>
//#include<sys/types.h>
#include<sys/wait.h>
sig_atomic_t count=0;

void signal_handler(int signal) {
	count++;
}

int main() {

	char *arglist []={"ls","-l","."};
	char *arglist1[]={"ps"};
	struct sigaction sigact;
	long int ret=0;
	int wait_st=0;
	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler=&signal_handler;
	sigaction(SIGCHLD,&sigact,NULL);
	while(ret<100000000) {ret++;}
	printf("count is %d \n",count);
	ret=fork();
	if (ret!=0) {
		nice(1001);//Add nice -this process gets less priority 
		printf("parent");
// 		kill(0,SIGTERM);
        	execvp("ps",arglist1);
		wait(&wait_st);
		waitpid(0,&wait_st,0);
		if (WIFEXITED(wait_st)) {
		    printf("exit status %d %d \n",WEXITSTATUS(wait_st),WTERMSIG(wait_st));	
		}		
		fflush(stdout);
	} else {
		nice(-100); 
  		system("ps");
 	 	printf("child");
  		fflush(stdout);
//  		execvp("ls",arglist);
		ret=fork();
		if(ret==0) {
		    printf("Another fork\n");
		    execvp("ls",arglist);
		}
	}	

	return 0;



}
