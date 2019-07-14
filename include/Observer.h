#ifndef OBSERVER_H_
#define OBSERVER_H_
#include "Subject.h"
class Subject;

class Observer {
  public:
    virtual ~Observer();
    virtual void notify(Subject*) = 0;
};

#endif
