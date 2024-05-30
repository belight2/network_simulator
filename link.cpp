#include "link.h"
#include "node.h"

// node에서 다른 하나의 모드로 이동
void Link::forwarding(const Node *node, Packet *packet){
  Node *dst_node = other(node);
  std::cout << forwarding_info_message(node->id(), dst_node->id()) << std::endl;
  dst_node->receive(packet);
}