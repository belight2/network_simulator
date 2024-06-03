#ifndef LINK_H
#define LINK_H

#include "object.h"
#include "packet.h"
#include <cstdlib>

#include <iostream>
#include <string>

#include "simulator.h"
class Node;

// Object class를 상속
class Link : public Object {
  friend class LinkInstaller;

private:
  // 생성자에 delay를 추가
  Link(Node *nodeA, Node *nodeB, double delay = 0.0)
   : nodeA_(nodeA), nodeB_(nodeB), delay_(delay) {}

  Node *nodeA_;
  Node *nodeB_;
  double delay_; // 딜레이를 추가

  virtual std::string name() override { return "Link"; } 
  
  // 포워딩하는 메시지를 반환
  std::string packet_in_message(std::string packet_info, std::string dst_node_info){
    return "packet in: "+packet_info+" from "+dst_node_info;
  }
  std::string packet_out_message(std::string packet_info, std::string dst_node_info){
    return "packet out: "+packet_info+" to "+dst_node_info;
  }

public:
  // node에서 다른 하나의 노드로 이동
  void forwarding(Node *node, Packet *packet);

  // add getter function
  double delay() { return delay_; }

  Node *nodeA() { return nodeA_; }

  Node *nodeB() { return nodeB_; }
  
  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  // private function에서 public으로 이동
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
};

#endif