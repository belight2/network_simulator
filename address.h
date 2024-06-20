#ifndef IP_H
#define IP_H

#include <string>

// 주소를 나타내는 클래스
class Address {
private:
  std::string address_;

public:
  Address(){}
  // 문자열을 받는 생성자를 추가
  Address(const std::string &address) : address_(address) {}
  // int형으로 받을 시 문자열로 형변환
  Address(int address) : address_(std::to_string(address)) {}
  // 이제 형변환없이 반환가능
  std::string toString() const { return address_; }
  bool operator==(const Address &rhs) const { return address_ == rhs.address_; }
  bool operator!=(const Address &rhs) const { return address_ != rhs.address_; }
};

#endif