#include <gtk/gtk.h>
#include "test.h"

int main(int argc, char ** argv)
{
	gtk_init(&argc, &argv);
	g_message("Main start");
	test_print();
	g_message("Main end");
}

