all : callback
	gcc callback.o main.c `pkg-config --cflags --libs gtk+-3.0` -o exe -ljson-c -lpthread
callback :
	gcc callback.c `pkg-config --cflags --libs gtk+-3.0` -c  