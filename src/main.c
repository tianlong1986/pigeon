#include "func_common.h"
#include "desktop.h"

int main(int argc, char ** argv)
{
	GtkWindow* window;
	gtk_init(&argc, &argv);
	g_message("Main start");
	start_listen();
	
	window = create_frame();
	gtk_widget_show(window);
	gtk_main();
	g_message("Main end");
}

