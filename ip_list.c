#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
int main() {

	struct addrinfo info, *resp, *tree;
	char ip[INET6_ADDRSTRLEN];
	int ret;

	memset(&info,0,sizeof(info));
	info.ai_family=AF_UNSPEC;//Auto-choose AF_INET or AF_INET6
	info.ai_socktype=SOCK_STREAM;

	if ((ret=getaddrinfo("10.77.8.70",NULL,&info,&resp))!=0) {
		fprintf(stderr,"getaddrinfo error %s \n",gai_strerror(ret));
		return -1;
	}
	
	for (tree=resp; tree!=NULL;tree=tree->ai_next) {
		void *addr;
		char *ipver;

		if (tree->ai_family ==AF_INET) {
			struct sockaddr_in *ipv4=(struct sockaddr_in *)tree->ai_addr;
			addr=&(ipv4->sin_addr);
			ipver="IPv4";
		} else {
			struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)tree->ai_addr;
			addr=&(ipv6->sin6_addr);
			ipver="IPv6";
		}
		inet_ntop(tree->ai_family, addr, ip, sizeof(ip));
		printf("IP : %s %s \n",ipver,ip);
	}
	freeaddrinfo(resp);
	return 0;




}
