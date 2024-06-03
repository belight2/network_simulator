#include "packet_sink_service.h"

void PacketSinkService::receive(Packet *packet){
  total_byte += packet->data().size();
  Object::log(receive_message());
  delete packet;
}
