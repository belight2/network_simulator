#ifndef ECHO_SERVICE_H
#define ECHO_SERVICE_H

#include "host.h"
#include "service.h"
#include <iostream>
#include <string>

// 수신한 패킷을 전송자에게 다시 전송하는 서비스
class EchoService : public Service {
  friend class EchoServiceInstaller;

private:
  virtual std::string name() { return "EchoService"; }
  EchoService(Host *host, short port) : Service(host, port) {}

  // 받은 메시지를 출력한다.
  std::string receive_info_message(std::string src_address, short src_port, std::string message){
    return "received \""+message+"\" from "+src_address+":"+std::to_string(src_port)+", send reply with same data";
  }

public:
  ~EchoService() override {}
  
  void send(Packet *packet) override;

  void receive(Packet *packet) override;
};

#endif