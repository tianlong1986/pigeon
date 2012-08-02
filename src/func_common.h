#ifndef _FUNC_COMMON_H
#define _FUNC_COMMON_H 
#include <gtk/gtk.h>
#include <sys/signal.h>
#include "./libnet/my_net.h"

void handler(int signo, siginfo_t * si, void *context);
typedef struct 
{
	char* ip;
	char* msg;
}MSG;

#endif
