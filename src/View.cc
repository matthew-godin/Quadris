#include <string>
#include "../include/Observer.h"
#include "../include/Block.h"
#include "../include/View.h"

View::View(std::ostream &sout) : outStream{sout} {}

StreamView::~StreamView() {
  subject->detach(this);
}

void StreamView::notify(Subject *subject) {
  
}
