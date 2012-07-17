#include <gtk/gtk.h>
#include "test.h"
#include "./libnet/my_net.h"

int main(int argc, char ** argv)
{
	gtk_init(&argc, &argv);
	g_message("Main start");
	test_print();
	start_listen();
	gtk_main();
	g_message("Main end");
}

