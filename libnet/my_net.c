#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int listen()
{
	int sock;
	struct sockaddr_in fromAddr;
	struct sockaddr_in fromAddr;
	int recLen;
	unsigned int addrlen;
	char recBuffer[200];
	
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_DUP);
	if( sock < 0)
	{
		printf("%s-%d:create socket error\n", __FILE__,__func__);
		return 1;
	}
	memset(&fromAddr,0,sizeof(fromAddr));
	fromAddr.sin_family=AF_INET;
	fromAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	fromAddr.sin_port = htons(4000);
	if(bind(sock,(struct sockaddr*)&fromAddr,sizeof(fromAddr))<0)
	{
 		printf("bind() 函数使用失败了.\r\n");
 		close(sock);
 		exit(1);
	}
	while(1)
	{
		addrLen = sizeof(toAddr);
		printf("waiting...\n");
		if((recvLen = recvfrom(sock,recvBuffer,128,0,(struct sockaddr*)&toAddr,&addrLen))<0)
		{
			 printf("()recvfrom()函数使用失败了.\r\n");
			 close(sock);
 			exit(1);
		}
		if(sendto(sock,recvBuffer,recvLen,0,(struct sockaddr*)&toAddr,sizeof(toAddr))!=recvLen){
		printf("sendto fail\r\n");
		close(sock);
		exit(0);
		}
	}
	return 0;
}

int start_listen()
{
	pthread_t id1;
	int ret;
	ret = pthread_create(&id1, NULL, (void*)listen, NULL);	
	return ret;
}











	
}
