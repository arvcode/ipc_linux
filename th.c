#include<stdio.h>
#include<pthread.h>


typedef struct th_args {
	int count;
	char *string;
}th_args_t;

void *handler (void * arg) {
	int i;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	th_args_t *t1;
 	t1=(th_args_t*)arg;
	for (i=0;i<t1->count;i++) {
		printf("%s \n",t1->string);	
		fflush(stdout);
	}	
	
}

int main(char **argv, int argc) {
    int a=0;
    th_args_t t1,t2;
	pthread_t tid,tid1;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	t1.count=100000;
	t1.string="test";
	t2.count=20000;
	t2.string="code";

	pthread_create(&tid,NULL,&handler,(void*)&t1);
	pthread_create(&tid1,&attr,&handler,(void*)&t2);
	printf("print main thread \n");
	pthread_attr_destroy(&attr);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
 	pthread_detach(tid);	

}
