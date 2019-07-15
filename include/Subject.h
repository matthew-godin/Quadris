#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>
#include "Observer.h"

using std::vector;
class Observer;

class Subject {
    vector<Observer*> observers;

public:
    Subject();
    virtual ~Subject();

    void attach(Observer*);
    void detach(Observer*);
    void notifyObservers();
};

#endif
