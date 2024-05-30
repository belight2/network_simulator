#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

#include <string>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }
/**** 추가 ****/

  // vitual destructor
  virtual ~Node() {}

  // 패킷을 목적지 경로로 전달한다.
  virtual void send(Packet *packet) = 0;
  
  // 수신한 패킷을 처리한다.
  virtual void receive(Packet *packet) = 0;
protected:
  // 현재 노드와 연결된 링크 목록
  std::vector<Link *> links;

/*************/
};
#endif