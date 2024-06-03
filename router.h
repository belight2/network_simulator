#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>


struct RoutingEntry {
public:
  RoutingEntry() : destination(), nextLink(nullptr) {}
  RoutingEntry(Address destination, Link* nextLink) : destination(destination), nextLink(nextLink) {}
  Address destination;
  Link *nextLink;
};

class Router : public Node {
private:
  virtual std::string name() override { return "Router"; }
  
  // forwarding packet: 0656<Packet> to 5106<Link>
  std::string forwarding_info_message(std::string packet_info, std::string link_info){
    return "forwarding packet: "+packet_info+" to "+link_info;
  }
  //Router #(Node id): no route for packet (from: src_address, to: dst_address, (data byte) bytes)
  std::string no_route_info_message(std::string packet_info){
    return "no route for packet: "+packet_info;
  }
protected:
  std::vector<RoutingEntry> routingTable_;
  
public:
  // 라우팅 테이블에서 패킷의 목적지 주소와 맞는 엔트리를 찾아 패킷을 전달
  void send(Packet *packet) override;

  // 전달된 패킷을 처리한다.
  void receive(Packet *packet) override;
};

#endif