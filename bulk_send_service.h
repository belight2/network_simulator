#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  Address destAddress;
  short destPort;
  double delay;
  double startTime;
  double stopTime;
  virtual std::string name() {return "BulkSendService";}  
  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0);

public:
  void send(Packet *packet) override;
  void receive(Packet *packet) override; 
};

#endif