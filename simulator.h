#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }
  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}
};


// 스케줄 객체를 정렬해주는 클래스
class Schedule_compare_func{
  public:
    bool operator() (Schedule &a, Schedule &b){
      return a.time() > b.time();
    }
};

class Simulator {
private:
  // 현재 시간
  static double time_;
  
  // 스케줄 큐를 선언한다.
  static std::priority_queue<Schedule, std::vector<Schedule>, Schedule_compare_func> schedule_queue;

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    // TODO: 구현
    schedule_queue.push(Schedule(time, function));
  }

  static void run() {
    // 모든 스케줄을 실행한다.
    // TODO: 구현
    while(!schedule_queue.empty()){
      auto current_schedule = schedule_queue.top();
      schedule_queue.pop();
      time_ = current_schedule.time();
      current_schedule.call();
    }
  }
};

#endif