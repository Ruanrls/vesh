TARGET=main
LD=gcc
OBJS=main.o commands.o

all: $(OBJS)
	$(LD) $(OBJS) -o $(TARGET)

commands.o: commands.c
	$(LD) -c commands.c -o commands.o

main.o: main.c
	$(LD) -c main.c -o main.o


clean:
	rm -f *.o