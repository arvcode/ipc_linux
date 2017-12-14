#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<signal.h>
int a=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

sem_t semap;

pthread_cond_t cv;

pthread_t gtid;

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
	sem_wait(&semap);
//	sem_trywait(&semap);
	sem_getvalue(&semap,&i);
	pthread_mutex_lock(&mutex);
	pthread_mutex_trylock(&mutex);	
	a=a+1;
	sem_post(&semap);
	pthread_cond_wait(&cv,&mutex);
	pthread_kill(gtid,SIGKILL);
	pthread_mutex_unlock(&mutex); //RECURSIVE
	pthread_mutex_unlock(&mutex);
	
}

void *thread2 (void *arg) {
printf("Operation V \n");
pthread_mutex_lock(&mutex);
sem_post(&semap);
//pthread_cond_signal(&cv);
pthread_cond_broadcast(&cv);
pthread_mutex_unlock(&mutex);

}

int main(char **argv, int argc) {
    int a=0;
    th_args_t t1,t2;
	pthread_t tid,tid1,tid2;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_mutexattr_t mut_attr;

	pthread_mutexattr_init(&mut_attr);
	pthread_mutexattr_setkind_np(&mut_attr,PTHREAD_MUTEX_ERRORCHECK_NP);
	pthread_mutexattr_setkind_np(&mut_attr,PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&mutex,&mut_attr);
	pthread_mutexattr_destroy(&mut_attr);

	sem_init(&semap,0,0);

	pthread_cond_init(&cv,NULL);

	t1.count=10;
	t1.string="test";
	t2.count=20;
	t2.string="code";
	gtid=tid1;
	pthread_create(&tid,NULL,&handler,(void*)&t1);
	pthread_create(&tid1,&attr,&handler,(void*)&t2);
	pthread_create(&tid2,&attr,&thread2,NULL);
	printf("print main thread \n");
	pthread_attr_destroy(&attr);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
 	pthread_detach(tid);	
	sem_destroy(&semap);
}
