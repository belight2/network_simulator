#ifndef LINK_H
#define LINK_H

#include "packet.h"
#include <cstdlib>

#include <iostream>
#include <string>

class Node;

class Link {
  friend class LinkInstaller;

private:
  Link(Node *nodeA, Node *nodeB) : nodeA_(nodeA), nodeB_(nodeB) {}

  Node *nodeA_;
  Node *nodeB_;
  
  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
  // 포워딩하는 메시지를 반환
  std::string forwarding_info_message(int src_node_id, int dst_node_id){
    return "Link: forwarding packet from node #"+std::to_string(src_node_id)+", to node #"+std::to_string(dst_node_id);
  }

public:
  // node에서 다른 하나의 노드로 이동
  void forwarding(const Node *node, Packet *packet);
};

#endif