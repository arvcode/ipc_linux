#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main() {

	int fd=0;
	struct sockaddr_in inetaddr;
	struct hostent* hostinfo;
	char buff[100];
	fd=socket(PF_INET,SOCK_STREAM,0);
	inetaddr.sin_family=AF_INET;
	hostinfo=gethostbyname("www.google.com.sg");
	inetaddr.sin_addr= *((struct in_addr *)hostinfo->h_addr);
	inetaddr.sin_port= htons(80);

	connect(fd,&inetaddr,sizeof(struct sockaddr_in));

	sprintf(buff,"GET /\n");
	write(fd, buff, strlen(buff));
	while(1){
		read(fd,buff,100);
		printf("%s",buff);
	}

}

