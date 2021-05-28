all : callback
	gcc callback.o main.c `pkg-config --cflags --libs gtk+-2.0` -o exe -ljson-c
callback :
	gcc callback.c `pkg-config --cflags --libs gtk+-2.0` -c  