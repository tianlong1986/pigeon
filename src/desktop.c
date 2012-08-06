#include "desktop.h"

struct person
{
	char* ip;
	GtkWidget *dialog;
	GtkWidget *text_view;
	GtkWidget *text_edit;
};

typedef struct person_list
{
	struct person *person;
	struct person_list *next;
}PERSON_LIST;

PERSON_LIST *person_head;//record the chat persons,head pointer
GtkWidget *list_vbox;
typedef	struct person CHAT_PERSON;

PERSON_LIST* add_person_to_list(PERSON_LIST* head, CHAT_PERSON* per);

void destroy(GtkWidget *wiget,gpointer *data)/*定义回调函数destroy，关闭窗口时系统自动调用*/
{
        gtk_main_quit();
}

char* clear_text_view(GtkWidget *text_view)
{
	char* msg;
	GtkTextBuffer * buffer;
	GtkTextIter iter, start, end;
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_get_bounds (buffer, &start, &end);
	msg = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        gtk_text_buffer_delete (buffer, &start, &end);
	return msg;
}

int insert_text_view(GtkWidget *text_view, char* text)
{
	GtkTextBuffer * buffer;
	GtkTextIter iter, start, end;
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	g_message("buffer=%ld, text=%s", (long)buffer,text);
        gtk_text_buffer_get_bounds (buffer, &start, &end);
//        gtk_text_buffer_delete (buffer, &start, &end);
	gtk_text_buffer_get_iter_at_offset (buffer,&iter, 0);
	gtk_text_buffer_insert (buffer, &iter, text, -1);
	gtk_text_buffer_insert (buffer, &iter, "\n", -1);

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
void cb_chat_send(gpointer data, GtkWidget *widget)
{
	g_message("Message has send");
	CHAT_PERSON* self;
	char* buf1;
	char* buf2;
	self = (CHAT_PERSON *)data;
	g_message("111111=%s---",self->ip);
	
	buf1 = g_strdup_printf("%s", clear_text_view(self->text_edit));
	buf2 = g_strdup_printf("我说:%s", buf1);
	my_sendto(buf1,self->ip,4000);
	insert_text_view(self->text_view, buf2);
	g_free(buf1);
	g_free(buf2);
}

int create_chat_window(CHAT_PERSON *self)
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
	//char buf[1000];
	GtkWidget *chat_text_view;
	GtkWidget *chat_text_edit;
	GtkTextBuffer * buffer;
	GtkTextIter iter, start, end;
	chat_text_view = gtk_text_view_new();
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text_view));
        gtk_text_buffer_get_bounds (buffer, &start, &end);
        gtk_text_buffer_delete (buffer, &start, &end);
	gtk_text_buffer_get_iter_at_offset (buffer,&iter, 0);
	gdk_color_parse ("#0000FF", &color_white);
	gdk_color_parse ("#FFFF22", &color_grey);
        gtk_widget_modify_text(chat_text_view, GTK_STATE_NORMAL, &color_white);
        gtk_widget_modify_base(chat_text_view, GTK_STATE_NORMAL, &color_grey);
	//gtk_text_buffer_insert (buffer, &iter, buf, -1);
	self->text_view = chat_text_view;

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
	self->text_edit = chat_text_edit;



	widget = gtk_scrolled_window_new(NULL,NULL);	
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER(widget), chat_text_edit);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), widget, FALSE, FALSE,2);
	

	hbox = gtk_hbox_new(FALSE, 6);
        button = gtk_button_new_with_label ("Send");
        g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (cb_chat_send),self);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 6);
        button = gtk_button_new_with_label ("Close");
        g_signal_connect_swapped (G_OBJECT (button), "clicked",G_CALLBACK (gtk_widget_destroy),dialog);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, FALSE, 6);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox, FALSE, FALSE,2);
	
	title = g_strdup_printf("talk with from %s",self->ip);
        gtk_container_border_width(GTK_CONTAINER(dialog),30);
        gtk_window_set_title(GTK_WINDOW(&GTK_DIALOG(dialog)->window), title);
	gtk_window_set_modal(GTK_WINDOW(&GTK_DIALOG(dialog)->window),FALSE);
	gtk_window_resize(GTK_WINDOW(&GTK_DIALOG(dialog)->window), 400, 400);
	self->dialog = dialog;
        gtk_widget_show_all(GTK_WIDGET(dialog));
//        gtk_dialog_run(dialog);
}
void callback( GtkWidget *widget,
gpointer data )
{
	create_chat_window(data);	
}

CHAT_PERSON* add_people(char* ip, GtkWidget* vbox)
{
	GtkWidget *hbox;
	GtkWidget *widget;
	GtkWidget *button;
	CHAT_PERSON *self;
	self = g_new0(CHAT_PERSON,1);
	self->ip=g_strdup(ip);
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
	g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK(callback),self);	
	gtk_box_pack_start(GTK_BOX(hbox), widget, FALSE, FALSE,2);	
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE,2);	
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE,2);	
	self->dialog = NULL;
	return self;
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

CHAT_PERSON * get_person_by_ip(char*ip)
{
	PERSON_LIST* tmp;
	g_return_val_if_fail(person_head!=NULL, NULL);
	tmp = person_head;
	while(tmp != NULL)
	{
		if(tmp->person)
		{
			if(g_strrstr(tmp->person->ip, ip))
			{
				return tmp;
			}
		}
		tmp = tmp->next;	
	}	
	return NULL;
}
void do_message(char*ip, char*message)
{
	CHAT_PERSON *person;
	char* buf;

	g_message("%s-%s-%d",__FILE__,__func__,__LINE__);
	gdk_threads_enter();
	g_message("%s-%s-%d",__FILE__,__func__,__LINE__);
	person = get_person_by_ip(ip);
	if (person == NULL)
	{
		person = add_people(ip, list_vbox);
		person_head = add_person_to_list(person_head, person);
	}
	if(person->dialog == NULL)
	{
		create_chat_window(person);	
	}
	g_message("%s-%s-%d,ip=%s,msg=%s",__FILE__,__func__,__LINE__,ip,message);
	buf = g_strdup_printf("%s说:%s", ip, message);
	g_message("%s-%s-%d,buf=%s",__FILE__,__func__,__LINE__,buf);
	insert_text_view(person->text_view, buf);
	g_message("%s-%s-%d,buf=%s",__FILE__,__func__,__LINE__,buf);
	gdk_threads_leave();
	g_free(buf);
	buf=NULL;
}

PERSON_LIST* add_person_to_list(PERSON_LIST* head, CHAT_PERSON* per)
{
	PERSON_LIST *tmp;
	PERSON_LIST *per_list;
	per_list = g_new0(PERSON_LIST, 1);
	if( head == NULL)
	{
		head = per_list;
		per_list->person = per;
		per_list->next=NULL;
	}
	else
	{
		per_list->next = head->next;	
		head->next = per_list;
	}
	return head;
}
GtkWidget* create_frame()
{
	GtkWidget* window;
	GtkWidget * vbox;
	CHAT_PERSON *person;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destroy),NULL);
        gtk_container_border_width(GTK_CONTAINER(window),10);

	//fixed = create_frame_fixed(window);
	vbox = gtk_vbox_new(FALSE, 10);
	list_vbox = vbox;
	person = add_people("192.168.1.131", vbox);
	person_head = add_person_to_list(person_head, person);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show_all(vbox);
	gtk_window_set_title(GTK_WINDOW(window), "feige");
	//gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );
	gtk_window_resize(GTK_WINDOW(window), 240, 600);
	gtk_window_move (window, gdk_screen_width() - 240, 0);
	//gtk_window_move (window,0,0);
	return window;
}

