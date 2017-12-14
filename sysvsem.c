#include<stdio.h>
#include<sys/sem.h>
#include<sys/stat.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;	
};

int binary_sem_alloc(key_t key, int semflag) {
	return semget(key,1,semflag);
}

int binary_sem_dealloc(int semid) {
	union semun args;
	return semctl (semid, 1, IPC_RMID, args);
}

int binary_sem_init (int semid) {
	union semun args;
	unsigned short value[1];
	value[0]=1;
	args.array=value;
	return semctl(semid,0,SETALL,args);
}

int binary_sem_wait(int semid) {
	struct sembuf ops[1];
	ops[0].sem_num=0;
	ops[0].sem_op=-1;
	ops[0].sem_flg=SEM_UNDO;
	return semop(semid,ops,1);
}

int binary_sem_post(int semid) {
	struct sembuf ops[1];
	ops[0].sem_num=0;
	ops[0].sem_op=1;
	ops[0].sem_flg=SEM_UNDO;
	return semop(semid,ops,1);

}

int main () {
	int semid=0;
	int ret=0;
	unsigned long v=0;
	semid=binary_sem_alloc(IPC_PRIVATE,S_IWUSR);
	binary_sem_init(semid);

	ret=fork();
	if (ret!=0) {
		printf("Parent \n");
		wait(&v);
	//	binary_sem_post(semid);
		binary_sem_wait(semid);
		printf("WAIT ! \n");
		binary_sem_dealloc(semid);
	} else {
		printf("Child \n");
		while(v<10) {
			sleep(1);
			v++;
		}
		binary_sem_post(semid);
	}
		
	return 0;
}

