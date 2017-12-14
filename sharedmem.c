#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>

/* ipcs to show
 * ipcrm -m to remove  */

int main() {

	int shm_id=0;
	char *shared_memory;
	struct shmid_ds shstr;
	int size;

	//shm_id=shmget(IPC_PRIVATE, getpagesize(),IPC_CREAT | IPC_EXCL ,S_IRUSR|S_IWUSR);
	//shmget prototype changed 	
	shm_id=shmget(IPC_PRIVATE, getpagesize(),S_IRUSR|S_IWUSR);
	shared_memory=(char *)shmat(shm_id,NULL, SHM_RND);

	printf ("shared memory attached at address %p \n", shared_memory);
	shmctl(shm_id,IPC_STAT,&shstr);
	size=shstr.shm_segsz;
	printf("Size of segment is %d \n",size);

	sprintf(shared_memory,"WRITE TO SHARED SEGMENT. MEMORY ATTACHED TO VIRTUAL MEMORY SPACE \n");

	shmdt(shared_memory);

	shared_memory=(char*)shmat(shm_id, (void *)0x05000000,0);

	printf("%s \n",shared_memory);
	while(1);
	shmdt(shared_memory);

	shmctl(shm_id,IPC_RMID,0);	

	return 0;


}
