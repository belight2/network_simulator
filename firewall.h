#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {
  private:
    virtual std::string name() override { return "FirewallPolicy"; }

  public:
    virtual bool isAllowed(Packet *packet) = 0;
};

class Firewall : public Node {

private:
  virtual std::string name() override { return "FireWall"; }

  class AllowAnyPolicy : public FirewallPolicy {
    private:
      short destPort_;
      virtual std::string name() override { return "AllowAnyPolicy"; }

    public:
      AllowAnyPolicy(short destPort) : destPort_(destPort) {}
      virtual bool isAllowed(Packet *packet) override{
        return packet->destPort() == this->destPort_;
      }
  };

  class AllowSpecificPolicy : public FirewallPolicy {
    private:
      Address srcAddress_;
      short destPort_;
      virtual std::string name() override { return "AllowSpecificPolicy"; }
    public:
      AllowSpecificPolicy(Address srcAddress, short destPort)
         : srcAddress_(srcAddress), destPort_(destPort) {}
      virtual bool isAllowed(Packet *packet) override{
        return (this->srcAddress_ == packet->srcAddress() && this->destPort_ == packet->destPort());
      }
  };

  Address inner_host_address;
  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy*> policies_;


public:
  virtual void initialize() override{
    for(Link* link : links){
      if(link == receiveLink_) continue;
      Host *host = dynamic_cast<Host*>(link->other(this));
      inner_host_address = host->address();
    }
  }
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort){
    policies_.push_back(new AllowAnyPolicy(destPort));
  }

  void addAllowSpecificPolicy(Address srcAddress, short destPort){
    policies_.push_back(new AllowSpecificPolicy(srcAddress, destPort));
  }
  
  void allow_packet(Packet *packet){
    this->send(packet);  
  }

  void drop_packet(Packet *packet){
    std::string message = "Dropping "+packet->toString() + " with src address "+packet->srcAddress().toString() + " and dest port " + std::to_string(packet->destPort());
    Object::log(message);
    delete packet;
  }

  virtual void receive(Packet *packet) override{
    if(packet->srcAddress() == inner_host_address){
      receiveLink_->forwarding(this, packet);
      return;
    }
    
    for(size_t i = 0; i < policies_.size(); i++){
      FirewallPolicy *policy = policies_[i];
      if(policy->isAllowed(packet)){
        allow_packet(packet);
        return;
      }
    }
    drop_packet(packet);
  }

  virtual void send(Packet *packet) override{
    for(Link* link : links){
      if(link == this->receiveLink_) continue;
      link->forwarding(this, packet);
    }
  }
};