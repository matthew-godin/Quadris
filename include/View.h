#ifndef VIEW_H_
#define VIEW_H_
#include "Observer.h"
#include "Block.h"

class View : public Observer {
    std::ostream &outStream;
  public:
    View(std::ostream &);
    void notify(*Subject) override;
    ~View();
};

#endif
