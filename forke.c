#include<stdio.h>
#include<signal.h>
#include<string.h>
sig_atomic_t count=0;

void signal_handler(int signal) {
	count++;
}

int main() {

	char *arglist []={"ls","-l","."};
	char *arglist1[]={"ps"};
	struct sigaction sigact;
	long int ret=0;

	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler=&signal_handler;
	sigaction(SIGINT,&sigact,NULL);
	while(ret<100000000) {ret++;}
	printf("count is %d \n",count);
	ret=fork();
	if (ret!=0) {
		nice(1001);//Add nice -this process gets less priority 
		printf("parent");
        execvp("ps",arglist1);
		fflush(stdout);
	} else {
		nice(-100); 
  		system("ps");
 	 	printf("child");
  		fflush(stdout);
  		execvp("ls",arglist);

	}	

	return 0;



}
