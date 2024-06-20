#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include <iostream>

class AutoRouter : public Router {
private:
  virtual std::string name() override { return "AutoRouter"; }

  // 우선 순위 큐에 삽입할 요소
  struct Entry{
    int vertex;
    double delay;
    Entry(int vertex, double delay): vertex(vertex), delay(delay) {}
  };
  // Entry.delay로 정렬해주는 클래스
  class Entry_cmp{
    public:
      bool operator()(Entry &a, Entry &b){
        return a.delay > b.delay;
      }
  };

  // Infinity value
  const double INF = std::numeric_limits<double>::infinity();

public:
  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links);
};

#endif