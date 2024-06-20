#include "host.h"
int Node::nextId_ = 0;

Host::~Host(){
  // 호스트에 설치된 서비스 삭제
  for(Service *service : services_){
    delete service;
  }
}
void Host::initialize(){
  link_size = links.size();
}

void Host::send(Packet *packet){
  // 패킷을 전송한다는 알림 메시지를 출력
  std::string message = send_info_message(packet);
  Object::log(message);
  
  // 링크를 랜덤으로 하나 선택
  int link_index = rand() % link_size;
  Link *link = links[link_index];

  // 링크를 통해 연결된 노드로 패킷을 전달
  link->forwarding(this, packet);
}

void Host::receive(Packet *packet){
  // 목적지 경로가 아니면 아무 작업도 하지 않음.
  if(this->address() != packet->destAddress()) return;
  std::string message;
  for(Service *service : services_){
    // 서비스의 포트와 패킷의 목적지 포트가 맞는 서비스를 찾았음
    if(service->get_port() == packet->destPort()){
      // 패킷을 수신했다는 알림 메시지를 출력
      message = receive_info_message(packet, service);
      Object::log(message);
      
      // 포트가 맞는 서비스에 패킷을 전달
      service->receive(packet);
      
      return;
    }
  }

  // 포트에 맞는 서비스가 없다는 메시지를 출력
  message = no_service_info_message(packet);
  Object::log(message);
  // 패킷을 폐기함
  // delete packet;
}