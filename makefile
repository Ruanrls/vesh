TARGET=main
LD=gcc
OBJS=main.o commands.o commandline.o

all: $(OBJS)
	$(LD) $(OBJS) -o $(TARGET) && ./$(TARGET)

commands.o: commands.c
	$(LD) -c commands.c

main.o: main.c
	$(LD) -c main.c

commandline.o: commandline.c
	$(LD) -c commandline.c

clean:
	rm -f *.o