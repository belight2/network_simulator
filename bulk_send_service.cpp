#include "bulk_send_service.h"

BulkSendService::BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay, double startTime,
                  double stopTime)
: Service(host, 1000), destAddress(destAddress), destPort(destPort), delay(delay), startTime(startTime), stopTime(stopTime) {}

void BulkSendService::send(Packet *packet){
  Object::log("sending data");
  this->host_->send(packet);
}

void BulkSendService::receive(Packet *packet){
  // delete packet;  
}

void BulkSendService::initialize(){
  std::string data;
  for(int i = 0; i < PACKET_SIZE; i++){ data += "A"; }
  double time = startTime;
  while(time < stopTime){
    Packet *packet = new Packet(Service::host_->address(), destAddress, this->port_, destPort, data);
    Service *service = this;
    Simulator::schedule(time+Simulator::now(), [service, packet]()->void{
      service->send(packet);
    });
    time += delay;
  }
}