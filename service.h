#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"
#include "object.h"

class Host;

class Service : public Object {
  friend class ServiceInstaller;
private: 
  // 서비스의 포트값을 변경
  void set_port(short port){ port_ = port; }

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, int port) : host_(host), port_(port) {}
public:

  // 서비스의 포트값을 반환받음
  short get_port() const { return port_; }

  virtual ~Service() {}
    
  // 서비스에서 생성한 패킷을 호스트에 전달
  virtual void send(Packet *packet) = 0;

  // 호스트에서 패킷을 받아 처리함
  virtual void receive(Packet *packet) = 0;
};

#endif