CC = clang++
GTKFLAGS := $(shell pkg-config --cflags --libs gtkmm-4.0)

build:
	$(CC) $(GTKFLAGS) program.cpp -o app
run : build
	./app
