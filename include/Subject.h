#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>
#include "Observer.h"

class Observer;

class Subject {
    std::vector<Observer> observers;

public:
    Subject();
    virtual ~Subject();

    void attach(Observer*);
    void detach(Observer*);
    void notifyObservers();
};

#endif