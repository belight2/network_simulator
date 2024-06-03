#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
friend class PacketSinkServiceInstaller;
private:
  virtual std::string name() override {return "PacketSinkService";}

  size_t total_byte{};

  PacketSinkService(Host *host, short port) : Service(host, port) {}

  std::string receive_message(){
    return "received total "+std::to_string(total_byte)+" bytes";
  }
public:
  void send(Packet *packet) override {};
  void receive(Packet *packet) override;
};

#endif