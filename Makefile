CC = gcc
SOURCES = *.c
OBJECTS = 10_server.o 10_client.o
TARGET = server client

$(TARGET): $(OBJECTS)
	     $(CC) -o server 10_server.o
	     $(CC) -o client 10_client.o

$(OBJECTS): $(SOURCES)
	      $(CC) -c $(SOURCES)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
