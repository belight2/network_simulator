CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

host.o: host.cpp
	$(CC) $(CFLAGS) -c host.cpp

router.o: router.cpp
	$(CC) $(CFLAGS) -c router.cpp

link.o: link.cpp
	$(CC) $(CFLAGS) -c link.cpp

echo_service.o: echo_service.cpp
	$(CC) $(CFLAGS) -c echo_service.cpp

message_service.o: message_service.cpp
	$(CC) $(CFLAGS) -c message_service.cpp

first: first.o host.o router.o link.o echo_service.o message_service.o
	$(CC) $(CFLAGS) -o first first.o host.o router.o link.o echo_service.o message_service.o

second: second.o host.o router.o link.o echo_service.o message_service.o
	$(CC) $(CFLAGS) -o second second.o host.o router.o link.o echo_service.o message_service.o

clean:
	del -f *.o first second
