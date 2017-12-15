#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define SOCK_PATH "/tmp/sock"



int server_func(int client_fd) {
	
	while(1){
		int len;
		char *buff;
	
		if (read(client_fd,&len,sizeof(int))==0) {
			return 0;	
		}
		buff=(char*)malloc(len);
		read(client_fd,buff,len);
		printf("%s",buff);
		free(buff);
		printf("IN SERVER FUNC \n");
	}

}

int main() {

	int sock_fd;
	int ret=0;
	struct sockaddr_un sock_addr;
	
	sock_fd=socket(PF_LOCAL,SOCK_STREAM,0); //PF_UNIX, protocol is 0
	
	sock_addr.sun_family=AF_LOCAL;
	strcpy(sock_addr.sun_path, SOCK_PATH);

	bind(sock_fd,&sock_addr, SUN_LEN(&sock_addr));

	listen(sock_fd,1);
	
	do {
		struct sockaddr_un client_addr;
		socklen_t client_addr_len;
		int client_fd;
		client_fd=accept(sock_fd,&client_addr,&client_addr_len);
		printf("ACCEPTED \n:");
		ret=server_func(client_fd);
	}while(!ret);	
	
	close(sock_fd);
	unlink(SOCK_PATH);
}
