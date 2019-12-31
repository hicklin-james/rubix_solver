#include "cube.h"
class Step {
  public:
    Step(Cube &cube);
    virtual bool reachedGoal() = 0;

  protected:
    Cube &cube;
};