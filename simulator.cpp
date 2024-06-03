#include "simulator.h"

double Simulator::time_ = 0.0;
std::priority_queue<Schedule, std::vector<Schedule>, Schedule_compare_func> Simulator::schedule_queue;

