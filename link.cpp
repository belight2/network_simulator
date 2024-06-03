#include "link.h"
#include "node.h"

// node에서 다른 하나의 모드로 이동
void Link::forwarding(Node *node, Packet *packet){
  Node *dst_node = other(node);
  Object::log(packet_in_message(packet->toString(), node->toString()));
  Simulator::schedule(Simulator::now()+this->delay(), [this, dst_node, packet]()->void{
    this->log(packet_out_message(packet->toString(), dst_node->toString()));
    dst_node->receive(packet);
  });
}