#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;
  // 현재 사용중인 포트
  short last_port = 1000;
  Link *wanLink_;
  std::vector<NatEntry> natTable_;

  short get_new_port(){ return last_port++; }

  virtual std::string name() override { return "Nat"; } 

  bool get_nat_entry(Packet *packet, NatEntry &entry);
    
  Packet* convert_lan_packet(Packet *packet);

  Packet* convert_wan_packet(Packet *packet);


public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }
  Address get_address(){ return address_; }

  virtual void initialize() override {}
  
  virtual void send(Packet* packet) override;
  virtual void receive(Packet *packet) override;
};