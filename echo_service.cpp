#include "echo_service.h"

void EchoService::send(Packet *packet){
  host_->send(packet); 
}

void EchoService::receive(Packet *packet){
  std::cout << receive_info_message(packet->srcAddress().toString(), packet->srcPort(), packet->dataString()) << std::endl;
  Packet *new_packet = new Packet(host_->address(), packet->srcAddress(), this->port_, packet->srcPort(), packet->data());
  delete packet;
  this->send(new_packet);
}