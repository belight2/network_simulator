#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;
std::priority_queue<Schedule, std::vector<Schedule>, Schedule_compare_func> Simulator::schedule_queue;

void Simulator::run() {
    // 모든 객체를 초기화 한다.
    Object::initializeAll();
    // 모든 스케줄을 실행한다.
    // TODO: 구현
    while(!schedule_queue.empty()){
      auto current_schedule = schedule_queue.top();
      schedule_queue.pop();
      time_ = current_schedule.time();
      current_schedule.call();
    }
    Object::cleanup();
  }