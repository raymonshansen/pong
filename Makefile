SOURCE = main.c paddle.c
HEADER = paddle.h

# Change this according to the type of system you are using
all: app_linux

app_linux: $(SOURCE) $(HEADER)
	gcc -Wall -o pong -Iinclude $(SOURCE) -lSDL2 -lm -lX11

clean:
	rm -f *.o app.exe pong *~
