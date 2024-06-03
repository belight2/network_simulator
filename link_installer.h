#ifndef LINK_INSTALLER_H
#define LINK_INSTALLER_H

#include "link.h"
#include "service.h"

class LinkInstaller {
public:
  // 노드 a, b 사이에 링크를 설치하고 반환한다.
  Link *install(Node *a, Node *b, double delay = 0.0){
    Link *link = new Link(a, b, delay);
    
    // 각 노드의 링크 목록에 링크를 삽입해준다.
    a->links.push_back(link);
    b->links.push_back(link);
    
    return link;
  }
};

#endif