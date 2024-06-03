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
                 const std::vector<Link *> &links) {
    // 전체 노드와 링크 정보를 통해
    // 모든 호스트로 전달될 수 있는 라우팅 테이블을 구성한다
    // TODO: 구현

    // index 정보로 노드를 가져온다.
    std::map<int, Node*> index_to_node;

    // node 정보로 인덱스를 가져온다.
    std::map<Node *, int> node_to_index;

    // 모든 노드의 길이
    size_t node_size = nodes.size();
    
    // mapping
    for(size_t i = 0; i < node_size; i++) {
      index_to_node.insert({i, nodes[i]});
      node_to_index.insert({nodes[i], i});
    }

    // 인접 리스트를 선언한다.
    std::vector<std::vector<Link *>> adj(node_size);

    // 링크 정보를 인접 리스트에 적절히 삽입
    for(Link *link : links){
      int u = node_to_index[link->nodeA()];
      int v = node_to_index[link->nodeB()];
      adj[u].push_back(link);
      adj[v].push_back(link);
    }
    
    // 우선 순위 큐 선언
    std::priority_queue<Entry, std::vector<Entry>, Entry_cmp> priority_queue;    

    // 각 정점에 대한 거리 정보
    std::vector<double> distance(node_size, INF);

    // 각 정점을 최단 거리로 이동할 때, 직전에 들려야하는 정점 정보
    // prev_vertex[i] = j : 최단거리로 i 정점에 도착하려면 j에서 i로 이동해야한다.
    std::vector<int> prev_vertex(node_size, -1);

    // current_vertex_index
    int cur = node_to_index[this];
    
    // 현재 정점까지의 delay는 0.0임
    distance[cur] = 0.0;

    // 우선 순위 큐에 정점 정보와 delay 삽입
    priority_queue.push(Entry(cur, 0.0));

    // // 각 node까지 최단 거리 갱신 시작
    while(!priority_queue.empty()){
      // 우선 순위 큐에서 값을 가져오고 pop함
      Entry entry = priority_queue.top(); priority_queue.pop();
      // 현재 정점 index
      int cur = entry.vertex;
      // 현재 delay값이 거리배열의 값보다 더 크다면 갱신하지 않는다.
      if(distance[cur] < entry.delay) continue;
      // cur의 link 정보를 가져옴
      for(Link *link : adj[cur]){
        // 다음 위치에 대한 노드 인덱스
        int nxt = node_to_index[link->other(index_to_node[cur])]; 

        if(prev_vertex[cur] == nxt) continue;
        
        // 갱신할 딜레이가 현재 딜레이보다 크다면 갱신하지 않는다.
        if(distance[nxt] < entry.delay + link->delay()) continue;
        // 딜레이 갱신 후 우선 순위 큐에 삽입
        distance[nxt] = entry.delay + link->delay();
        priority_queue.push(Entry(nxt, distance[nxt]));
        // 경로 갱신
        prev_vertex[nxt] = cur;
      }
    }

    // distance 배열이 갱신되었음, 이제 nodes 중 "Host" 인 것을 찾고
    // 경로를 복원한 뒤, routingTable_을 갱신해주면 됨
    cur = node_to_index[this];
    for(Node *node : nodes){
      // dynamic_cast를 사용해 호스트로 down casting
      Host *host = dynamic_cast<Host *>(node);
      // down casting 실패한 경우 넘어감
      if(host == nullptr) continue;
      // 도착 정점의 node index
      int next_index = node_to_index[host];
      // 호스트까지 가는 경로가 존재하지 않으면 넘어감
      if(prev_vertex[next_index] == -1) continue;
      // host로 가기 위해 cur이 첫번째로 가야할 노드 정보를 찾는다.
      while(prev_vertex[next_index] != cur){
        next_index = prev_vertex[next_index];
      }
      // 현재 노드와 연결된 링크 중 목적지가 next_index인 링크를 찾아 라우팅 테이블을 갱신
      Node* next_node = index_to_node[next_index];
      for(Link *link : adj[cur]){
        if(next_node == link->other(this)){
          routingTable_.push_back(RoutingEntry(host->address(), link));
          break;
        }
      }
    }
  }
};

#endif