CC     = gcc
CFLAGS = -Wall
DEPS   = main.h
TARGET = cacheSim
OBJS   = main.o cacheSimulation.o cacheResults.o

%.o: %.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).exe -lm
	$(MAKE) clean

clean:
	rm -f *.o