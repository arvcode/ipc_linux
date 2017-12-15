#include<stdio.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#define FILE_SIZE 0x200

int main() {
	int fd=0;
	void *memmap=NULL;
	fd=open("data",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	//lseek(fd,FILE_SIZE+1,SEEK_SET);
	write(fd,"MEMMAP FILE",12);
	//lseek(fd,0,SEEK_SET);

	memmap=mmap(0,FILE_SIZE,PROT_WRITE,MAP_SHARED,fd,0); //start at 0
	close(fd);

	sprintf((char*)memmap,"%s","File write");
	msync(memmap,FILE_SIZE, MS_SYNC|MS_INVALIDATE);
	munmap(memmap,FILE_SIZE); 
	return 0;
}
