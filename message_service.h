#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "address.h"
#include "host.h"
#include "service.h"
#include <iostream>

// send 함수를 호출하여 메시지를 전송할 수 있는 서비스
class MessageService : public Service {
  friend class MessageServiceInstaller;

private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;
  MessageService(Host *host, short port, Address destAddress, short destPort)
      : Service(host, port), destAddress_(destAddress), destPort_(destPort) {}
  
  // 받은 메시지를 출력한다.
  std::string receive_info_message(std::string src_address, short src_port, std::string message){
    return "MessageService: received \""+message+"\" from "+src_address+":"+std::to_string(src_port);
  }
public:
  ~MessageService() override {}
  
  // 메시지를 전송한다
  void send(std::string message);

  void send(Packet *packet) override;

  void receive(Packet *packet) override;
};

#endif