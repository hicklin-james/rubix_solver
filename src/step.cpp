/** Class header */
#include "step.h"

/** System headers */

// ------------------------------------------------------------------------- //
Step::Step(Cube &cube) : cube(cube) {}

// ------------------------------------------------------------------------- //
void Step::retryTarget(FaceOrientation orientation, int i, int j)
{
  auto target = std::find_if(
    targets.begin(),
    targets.end(),
    [&] (const auto target)
    {
      return target.face == orientation &&
             target.position.first == i &&
             target.position.second == j;
    }
  );

  if (target != targets.end())
  {
    target->retryTarget = true;
  }
}

// ------------------------------------------------------------------------- //
Step::TargetIter Step::findTargetThatNeedsRetry()
{
  auto targetWithRetrySet = std::find_if(
    targets.begin(),
    targets.end(),
    [] (TargetLocation& targ)
    {
      auto found = targ.retryTarget;
      targ.retryTarget = false;
      return found;
    }
  );
  return targetWithRetrySet;
}