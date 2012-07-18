#include "desktop.h"
void destroy(GtkWidget *wiget,gpointer *data)/*定义回调函数destroy，关闭窗口时系统自动调用*/
{
        gtk_main_quit();
}

int signal_handler_event(GtkWidget *widget, GdkEventButton *event, gpointer func_data)
{
       if (GTK_IS_LIST_ITEM(widget) &&
            (event->type==GDK_2BUTTON_PRESS ))
	{
		g_message("ddddddddddddddd");
        }

		g_message("dddddddddddddddsssssssssssssssssdddddd");
       return FALSE;
}
void cb_chat_send( GtkWidget *widget,gpointer data )
{
	g_message("Message has send");

}

int create_chat_window(char* ip)
{
        GtkDialog *dialog ;
        dialog = GTK_WIDGET(gtk_dialog_new());
        GtkWidget *button;
        GtkWidget *label;
	GdkColor color_white;
	GdkColor color_grey;
	GdkColor color_edit_text;
	GdkColor color_edit_base;
	GtkWidget* scroll_window;
	GtkWidget* hbox;
	GtkWidget* widget;
	char* title;
	char buf[1000];
	GtkWidget *chat_text_view;
	GtkWidget *chat_text_edit;
	GtkTextBuffer * buffer;
	GtkTextIter iter, start, end;
	chat_text_view = gtk_text_view_new();
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text_view));
        gtk_text_buffer_get_bounds (buffer, &start, &end);
        gtk_text_buffer_delete (buffer, &start, &end);
	gtk_text_buffer_get_iter_at_offset (buffer,&iter, 0);
	gdk_color_parse ("#FFFFFF", &color_white);
	gdk_color_parse ("#FFFF22", &color_grey);
        gtk_widget_modify_text(chat_text_view, GTK_STATE_NORMAL, &color_white);
        gtk_widget_modify_base(chat_text_view, GTK_STATE_NORMAL, &color_grey);
	gtk_text_buffer_insert (buffer, &iter, buf, -1);

	gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_text_view),FALSE);
	scroll_window = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER (scroll_window), chat_text_view);
	
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->vbox),scroll_window, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 6);
	widget = gtk_label_new("fen ge fu -----------");
	gtk_box_pack_start(GTK_BOX(hbox), widget, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, FALSE, FALSE,2);

	chat_text_edit = gtk_text_view_new();

	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text_edit));
        gtk_text_buffer_get_bounds (buffer, &start, &end);
        gtk_text_buffer_delete (buffer, &start, &end);
	gtk_text_buffer_get_iter_at_offset (buffer,&iter, 0);
	gdk_color_parse ("#FF5599", &color_edit_text);
	gdk_color_parse ("#112222", &color_edit_base);
        gtk_widget_modify_text(chat_text_edit, GTK_STATE_NORMAL, &color_edit_text);
        gtk_widget_modify_base(chat_text_edit, GTK_STATE_NORMAL, &color_edit_base);
	gtk_text_buffer_insert (buffer, &iter, "nihao", -1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_text_edit),TRUE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chat_text_edit),GTK_WRAP_CHAR);



	widget = gtk_scrolled_window_new(NULL,NULL);	
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER(widget), chat_text_edit);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), widget, FALSE, FALSE,2);
	

	hbox = gtk_hbox_new(FALSE, 6);
        button = gtk_button_new_with_label ("Send");
        g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (cb_chat_send),dialog);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 6);
        button = gtk_button_new_with_label ("Close");
        g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (gtk_widget_destroy),dialog);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 6);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, FALSE, FALSE,2);
	
	title = g_strdup_printf("talk with from %s",ip);
        gtk_container_border_width(GTK_CONTAINER(dialog),30);
        gtk_window_set_title(GTK_WINDOW(&GTK_DIALOG(dialog)->window), title);
	gtk_window_resize(GTK_WINDOW(&GTK_DIALOG(dialog)->window), 400, 400);
        gtk_widget_show_all(GTK_WIDGET(dialog));
        gtk_dialog_run(dialog);
}
void callback( GtkWidget *widget,
gpointer data )
{
	create_chat_window(data);	
}

void add_people(char* ip, GtkWidget* vbox)
{
	GtkWidget *hbox;
	GtkWidget *widget;
	GtkWidget *button;
	widget = gtk_label_new(ip);
	hbox = gtk_hbox_new(FALSE,2);
	gtk_widget_add_events(hbox,  GDK_BUTTON_PRESS_MASK);
       	gtk_signal_connect(GTK_OBJECT(hbox),
                          "button_press_event",
                          G_CALLBACK(signal_handler_event),
                          NULL);
	gtk_widget_add_events(widget,  GDK_BUTTON_PRESS_MASK);
	g_signal_connect (G_OBJECT (widget), "button_press_event",
	G_CALLBACK (signal_handler_event), "button 2");

	button = gtk_button_new_with_label("交谈");
	g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK(callback),ip);	
	gtk_box_pack_start(GTK_BOX(hbox), widget, FALSE, FALSE,2);	
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE,2);	
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE,2);	
}
GtkWidget* create_frame_fixed(GtkWidget* window)
{
        GtkWidget *fixed;
        GtkWidget *widget;
        fixed = gtk_fixed_new();
        widget = gtk_label_new("飞鸽");
        gtk_fixed_put(GTK_FIXED(fixed), widget, 10,10);
	return fixed;
}
GtkWidget* create_frame()
{
	GtkWidget* window;
	GtkWidget * vbox;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destroy),NULL);
        gtk_container_border_width(GTK_CONTAINER(window),10);

	//fixed = create_frame_fixed(window);
	vbox = gtk_vbox_new(FALSE, 10);
	add_people("192.168.1.22", vbox);
	add_people("192.168.1.23", vbox);
	add_people("192.168.1.24", vbox);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show_all(vbox);
	gtk_window_set_title(GTK_WINDOW(window), "feige");
	//gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );
	gtk_window_resize(GTK_WINDOW(window), 240, 600);
	gtk_window_move (window, gdk_screen_width() - 240, 0);
	//gtk_window_move (window,0,0);
	return window;
}

