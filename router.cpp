#include "router.h"
void Router::send(Packet *packet){
  std::string message;
  for(RoutingEntry entry : routingTable_){
    if(entry.destination == packet->destAddress()){
      // 목적지 주소로 가는 엔트리를 찾아서 패킷을 전달한다는 알림 메시지를 출력
      message = forwarding_info_message(packet->toString(), entry.nextLink->toString());
      this->log(message); 
      // 패킷을 링크를 통해 전달
      entry.nextLink->forwarding(this, packet);
     
      return;
    }
  }
  message = no_route_info_message(packet->toString()); 
  this->log(message);
  delete packet;
}

void Router::receive(Packet *packet){
  // 전달받은 패킷을 별도의 처리없이 전달한다.
  this->send(packet);
}