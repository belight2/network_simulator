#include "host.h"
int Node::nextId_ = 0;

void Host::initialize(){
  link_size = links.size();
  srand(time(nullptr));
}

void Host::send(Packet *packet){
  // 패킷을 전송한다는 알림 메시지를 출력
  std::cout << send_info_message(packet->srcAddress().toString(), packet->destAddress().toString(), std::to_string(packet->data().size())) << std::endl;    
  
  // 링크를 랜덤으로 하나 선택
  int link_index = rand() % link_size;
  Link *link = links[link_index];

  // 링크를 통해 연결된 노드로 패킷을 전달
  link->forwarding(this, packet);
}

void Host::receive(Packet *packet){
  for(Service *service : services_){
    // 서비스의 포트와 패킷의 목적지 포트가 맞는 서비스를 찾았음
    if(service->get_port() == packet->destPort()){
      // 패킷을 수신했다는 알림 메시지를 출력
      std::cout << receive_info_message(std::to_string(packet->destPort())) << std::endl;
      // 포트가 맞는 서비스에 패킷을 전달
      service->receive(packet);
      return;
    }
  }

  // 포트에 맞는 서비스가 없다는 메시지를 출력
  std::cout << no_service_info_message(packet->srcAddress().toString(), packet->destAddress().toString(), std::to_string(packet->data().size())) << std::endl;    
  // 패킷을 폐기함
  delete packet;
}