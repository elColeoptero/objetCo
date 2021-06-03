all : callback bdd
	gcc callback.o bdd.o main.c `pkg-config --cflags --libs gtk+-3.0` `pkg-config --cflags --libs x11` -o exe -ljson-c -lpthread -lX11 -lmysqlclient 
callback :
	gcc callback.c `pkg-config --cflags --libs gtk+-3.0` -c  
bdd :
	gcc bdd.c `pkg-config --cflags --libs gtk+-3.0` -c  