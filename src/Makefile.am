SUBDIRS=  
  
hello_CPPFLAGS = \
        $(GTK_CFLAGS)

bin_PROGRAMS=hello  
hello_SOURCES=func_common.h \
	      desktop.h \
	      desktop.c \
	      my_net.h \
	      my_net.c \
		main.c  

hello_LDADD = \
        -lm \
        $(GTK_LIBS)
