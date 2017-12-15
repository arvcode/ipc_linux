#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdlib.h>

#define SOCK_PATH "/tmp/sock"


int main() {
	int fd=0;
	struct sockaddr_un sock_addr;
	int len;
 	
	char *buff="client";
	len=strlen(buff)+1;
	fd=socket(PF_LOCAL,SOCK_STREAM,0);

	sock_addr.sun_family=AF_LOCAL;
	strcpy(sock_addr.sun_path,SOCK_PATH);

	connect(fd,&sock_addr,SUN_LEN(&sock_addr));
	
	write(fd,&len,sizeof(len));
	write(fd,buff,len);
	close(fd);
	return 0;
}
