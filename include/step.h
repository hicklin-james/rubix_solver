#pragma once

/** Local headers */
#include "cube.h"

class Step {
  public:

    /**
    * Main Step constructor
    *
    * @param &cube Cube the cube 
    */
    Step(Cube &cube);

    /**
    * Main function to start the logic to solve the step.
    */
    virtual void solveStep() {};

    // Typedef to shorten TargetLocation iterator
    typedef std::vector<TargetLocation, 
                        std::allocator<TargetLocation>>::iterator TargetIter;

  protected:

    Cube &cube; // the cube - protected to give child access
    std::vector<TargetLocation> targets; // vector of targets

    /**
    * Function to set the retry variable on a target with given
    * orientation, i and j to true
    *
    * @param orientation FaceOrientation the face orientation
    * @param i int the i position
    * @param j int the j position
    */
    void retryTarget(FaceOrientation orientation, int i, int j);

    /**
    * Function to find target that needs a retry
    *
    * @return iterator to TargetLocation
    */
    TargetIter findTargetThatNeedsRetry();

  private:
    
    /**
    * Function to setup the target locations on the step
    */
    virtual void setupTargetLocations() {};
};