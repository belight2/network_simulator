CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = simulator.o object.o echo_service.o host.o link.o message_service.o router.o bulk_send_service.o packet_sink_service.o 

all: first second third forth

first: first.o $(OBJECTS)
		$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
		$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
		$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
		$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

first.o: scenarios/first.cpp
		$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
		$(CC) $(CFLAGS) -c scenarios/second.cpp

third.o: scenarios/third.cpp
		$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp
		$(CC) $(CFLAGS) -c scenarios/forth.cpp

simulator.o: simulator.cpp
		$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp
		$(CC) $(CFLAGS) -c object.cpp

echo_service.o: echo_service.cpp
		$(CC) $(CFLAGS) -c echo_service.cpp

host.o: host.cpp
		$(CC) $(CFLAGS) -c host.cpp

link.o: link.cpp
		$(CC) $(CFLAGS) -c link.cpp
router.o: router.cpp
		$(CC) $(CFLAGS) -c router.cpp

message_service.o: message_service.cpp
		$(CC) $(CFLAGS) -c message_service.cpp

packet_sink_service.o: packet_sink_service.cpp
		$(CC) $(CFLAGS) -c packet_sink_service.cpp

bulk_send_service.o: bulk_send_service.cpp
		$(CC) $(CFLAGS) -c bulk_send_service.cpp
clean:
		del -f *.o *.exe
