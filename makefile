TARGET=main
LD=gcc
OBJS=main.o commands.o commandline.o exec.o

all: $(OBJS)
	$(LD) $(OBJS) -o $(TARGET) && clear; ./$(TARGET)

commands.o: commands.c
	$(LD) -c commands.c

main.o: main.c
	$(LD) -c main.c

commandline.o: commandline.c
	$(LD) -c commandline.c

exec.o: exec.c
	$(LD) -c exec.c

debug: 
	$(LD) -g $(OBJS) -o $(TARGET)

clean:
	rm -f *.o