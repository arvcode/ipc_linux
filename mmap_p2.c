#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>

#define FILE_SIZE 0x200

int main () {
	int fd=0;
	void *memmap=NULL;
	char buff[20];
	fd=open("data",O_RDWR, S_IRUSR |S_IWUSR);
	/*
	 *PROT_READ, PROT_WRITE, PROT_EXEC
	 *MAP_FIXED, MAP_PRIVATE, MAP_SHARED
	 */
	memmap=mmap(NULL,FILE_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	sscanf(memmap,"%s",buff);
	printf("Buffer is %s \n",buff);
	sprintf((char*)memmap,"Process two %s","Process two");
	munmap(memmap,FILE_SIZE);	
	return 0;
}
