#include "step.h"
#include "util.h"

class Cross : Step {
  public:
    Cross(Cube &cube);
    bool reachedGoal();
    void reorientWhiteFaceToTop();

  private:
    FaceOrientation findWhiteCenter();
};