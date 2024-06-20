#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>

#include <string>
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

  virtual std::string name() override { return "Host"; }

  // 패킷 전송 알림 메시지를 반환
  std::string send_info_message(Packet *packet){
    return "sending packet: "+ packet->toString();
  }

  // 패킷 수신 알림 메시지를 반환
  std::string receive_info_message(Packet *packet, Service *service){
    return "received packet: "+ packet->toString() +", forwarding to " +service->toString();
  }

  // 패킷의 포트에 맞는 서비스가 없다는 알림 메시지를 반환
  std::string no_service_info_message(Packet *packet){
    return "no service for packet: "+ packet->toString();
  } 

public:
  // 호스트의 주소를 반환한다.
  Address address() { return address_; }
  
  // 호스트 생성자
  Host(Address address) : address_(address) {}
  Host(int address) : address_(Address(address)) {}
  Host(std::string address) : address_(Address(address)) {}

  // 호스트 소멸자
  ~Host() override;

  // 호스트와 설치된 서비스를 전부 초기화한다.
  virtual void initialize() override;

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet) override;

  // 수신한 패킷의 포트에 맞는 서비스를 찾아 서비스에 패킷을 전달한다.
  void receive(Packet *packet) override;

};

#endif