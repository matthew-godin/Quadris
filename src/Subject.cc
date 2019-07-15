#include "Subject.h"
#include <algorithm>

Subject::Subject() {};

Subject::~Subject() {};

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer* o) {
    auto removeIterator = find(observers.begin(), observers.end(), o);
    observers.erase(removeIterator);
}

void Subject::notifyObservers() {
    for (auto &o: observers) {
        o->notify(this);
    }
}