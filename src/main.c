#include "func_common.h"
#include "desktop.h"
void handler(int signo, siginfo_t * si, void *context)
{
	printf("\n,收到的信息：%s", si->si_value.sival_ptr);

	do_message( ((MSG*)(si->si_value.sival_ptr))->ip, ((MSG*)(si->si_value.sival_ptr))->msg);
	g_free(((MSG*)(si->si_value.sival_ptr))->msg);
	g_free(((MSG*)(si->si_value.sival_ptr))->ip);
	g_free((MSG*)(si->si_value.sival_ptr));
}

int main(int argc, char ** argv)
{
	GtkWindow* window;
	gtk_init(&argc, &argv);
	g_message("Main start");
	printf("main:myid=%d, parentid=%d\n",getpid(),getppid());
	start_listen();
	
	window = create_frame();
	gtk_widget_show(window);
	gtk_main();
	g_message("Main end");
}

