#include "message_service.h"

void MessageService::send(std::string message){
  Packet *packet = new Packet(host_->address(), destAddress_, this->port_, destPort_, message);
  this->send(packet);
}

void MessageService::send(Packet *packet){
  this->host_->send(packet);
}

void MessageService::receive(Packet *packet){
  std::string message = receive_info_message(packet->srcAddress().toString(), packet->srcPort(), packet->dataString());
  Object::log(message);
  delete packet;
}