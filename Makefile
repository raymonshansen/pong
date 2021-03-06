SOURCE = main.c ball.c paddle.c collision.c filledball.c
HEADER = ball.h paddle.h collision.h

# Change this according to the type of system you are using
all: app_linux

app_linux: $(SOURCE) $(HEADER)
	gcc -Wall -o pong -Iinclude $(SOURCE) -lSDL2 -lSDL2_ttf -lm -lX11

clean:
	rm -f *.o pong.exe pong *~
