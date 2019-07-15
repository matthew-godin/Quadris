#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "Subject.h"
#include <memory>


class Subject;

class Observer {
public:
    Observer();
    virtual ~Observer();
    virtual void notify(Subject*) = 0;
};

#endif