#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "func_common.h"

static int my_listen()
{
	int sock;
	struct sockaddr_in toAddr;
	struct sockaddr_in fromAddr;
	int recLen;
	unsigned int addrLen;
	char recBuffer[200];

	sigset_t mask;
	sigset_t oldmask;
	struct sigaction act;
	int me = getpid();
	union sigval val;
	act.sa_sigaction = handler;
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN, &act, NULL);
	sigemptyset(&mask);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);
	val.sival_int = 1;
	MSG *message;
	message = g_new0(MSG,1);
	
	
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
	printf("thread :myid=%d, parentid=%d",getpid(),getppid());
	
	while(1)
	{
		addrLen = sizeof(toAddr);
		printf("waiting...\n");
		if((recLen = recvfrom(sock,recBuffer,128,0,(struct sockaddr*)&toAddr,&addrLen))<0)
		{
			 printf("()recvfrom()函数使用失败了.\r\n");
			 close(sock);
 			exit(1);
		}
		printf("%s 说:%s\n",inet_ntoa(toAddr.sin_addr), recBuffer);
		char* msg;
		msg = g_strdup_printf("%s",recBuffer);
		//do_message(inet_ntoa(toAddr.sin_addr), recBuffer);
		message->msg = msg;
		g_message("tom debug,msg=%s",msg);
		message->ip = g_strdup_printf("%s", inet_ntoa(toAddr.sin_addr));	
		val.sival_ptr = message;
		sigqueue(me, SIGRTMIN, val);
		memset(recBuffer, 0, 200);
		//my_sendto("how are you!", "127.0.0.1",4000);
		//if(sendto(sock,recBuffer,recLen,0,(struct sockaddr*)&toAddr,sizeof(toAddr))!=recLen){
		//if(sendto(sock,recBuffer,10,0,(struct sockaddr*)&toAddr,1)<0){
		//	printf("Error send to\n");
		//	exit(0);
		//}
	}
	return 0;
}

int start_listen()
{
	pthread_t id1;
	int ret;
	ret = pthread_create(&id1, NULL, (void*)my_listen, NULL);	
	return ret;
}

int my_sendto(char* msg, char*host, int port)
{
	struct sockaddr_in toAddr;
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	int recLen;
	unsigned int addrLen;
	char recBuffer[200];
	memset(&toAddr,0,sizeof(toAddr));
	toAddr.sin_family=AF_INET;
	toAddr.sin_addr.s_addr= inet_addr(host);
	toAddr.sin_port = htons(port);
	//if(sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&toAddr,sizeof(toAddr))!=recLen){
	g_message("now send to %s;%d, msg=%s", host,port,msg);
	if(sendto(sock,msg,13,0,(struct sockaddr*)&toAddr,sizeof(struct sockaddr_in))<0){
		printf("sendto fail\r\n");
		close(sock);
		exit(0);
	}
}


	
