#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  // 연결된 링크의 개수
  size_t link_size;

  // 패킷 전송 알림 메시지를 반환
  std::string send_info_message(std::string src_address, std::string dst_address, std::string data_bytes){
    return "Host #"+std::to_string(this->id())+": sending packet (from: "+src_address+", to: "+dst_address+", "+data_bytes+" bytes)";
  }

  // 패킷 수신 알림 메시지를 반환
  std::string receive_info_message(std::string dst_port){
    return "Host #"+std::to_string(this->id())+": received packet, destination port: "+dst_port;
  }

  // 패킷의 포트에 맞는 서비스가 없다는 알림 메시지를 반환
  std::string no_service_info_message(std::string src_address, std::string dst_address, std::string data_bytes){
    return "Host #"+std::to_string(this->id())+": no service for packet (from: "+src_address+", to: "+dst_address+", "+data_bytes+" bytes)";
  } 

public:
  // 호스트의 주소를 반환한다.
  Address address() { return address_; }
  
  // 호스트 생성자
  Host(Address address) : address_(address) {}

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet) override;

  // 수신한 패킷의 포트에 맞는 서비스를 찾아 서비스에 패킷을 전달한다.
  void receive(Packet *packet) override;

  // // 디버그용 정보 출력 함수
  // std::string toString(){
  //   std::string info =  "Host #"+std::to_string(this->id())+"[Address: "+address().toString()+"serviceSize= "+std::to_string(service_size)+"]";
  //   for(Service *service : services_){
  //     // 서비스의 종류와 서비스의 포트 정보 info에 삽입
  //   }
  //   return info;
  // }

};

#endif