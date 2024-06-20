#include "nat.h" 
#include <iostream>

bool Nat::get_nat_entry(Packet *packet, NatEntry &entry){
  for(NatEntry nat_entry : natTable_){
    if(nat_entry.internalAddress == packet->srcAddress() && nat_entry.internalPort == packet->srcPort()){
      entry = nat_entry;
      return 1;
    }
  } 
  return 0;   
}

Packet* Nat::convert_lan_packet(Packet *packet){
  for(NatEntry entry : natTable_){
    if(entry.externalPort != packet->destPort()) continue;
    return new Packet(packet->srcAddress(), entry.internalAddress, packet->srcPort(), entry.internalPort, packet->data());
  }
  return nullptr;
}

Packet* Nat::convert_wan_packet(Packet *packet){
  NatEntry entry; 
  if(!get_nat_entry(packet, entry)){
    entry.externalPort = get_new_port();
    entry.internalPort = packet->srcPort();
    entry.internalAddress = packet->srcAddress();
    natTable_.push_back(entry); 
  }
  return new Packet(this->address_, packet->destAddress(), entry.externalPort, packet->destPort(), packet->data());
}

void Nat::send(Packet *packet){
  Packet *new_packet = convert_lan_packet(packet);
  for(Link *link : links){
    if(link == wanLink_) continue;
    link->forwarding(this, new_packet);
  }
  delete packet;
}

void Nat::receive(Packet *packet){
  if(packet->destAddress() == this->get_address()){
    this->send(packet);
    return;
  } 
  Packet *new_packet = convert_wan_packet(packet);
  this->wanLink_->forwarding(this, new_packet);
  delete packet;
}