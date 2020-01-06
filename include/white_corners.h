#pragma once

/** Local headers */
#include "step.h"
#include "util.h"

class WhiteCorners : Step 
{
  public:

    /** 
    * Main corners constructor
    *
    * @param &cube Cube
    */
    WhiteCorners(Cube &cube);

    /**
    * solveStep function implementation for white corners
    */
    void solveStep();

  private:

    /**
    * Function to setup the target locations on the white corners
    */
    void setupTargetLocations();

    /**
    * Function to reposition pieces from the top to the bottom
    * 
    * @param orientation FaceOrientation the orientation of the face
    * @param i int the i position of the piece on the upper face
    * @param step SolveStep
    */
    void repositionTopToBottom(FaceOrientation orientation,
                               int iUp,
                               SolveStep &step);

    /**
    * Function to find the next unsolved corner piece. This function
    * sets the input item to the next unsolved target.
    *
    * @param &unsolvedPiece SolveStep the item to set
    * @return boolean, true if there is still an unsolved piece, else false
    */
    bool nextUnsolvedCornerPiece(SolveStep &unsolvedPiece);

    /**
    * Function to reposition the bottom piece to its final position
    *
    * @param &step SolveStep a reference to the current solve step
    */
    void respositionBottomToFinal(const SolveStep &step);

    /**
    * Function to find the adjacent face colors on the bottom and right
    * faces
    *
    * @return a 2-item vector of face colors
    */
    std::vector<FaceColor> getBrAdjacentFaceColors();

    /**
    * Function to get the new position of a target after a right rotation
    *
    * @param i int the original i position
    * @param j int the original j position
    * @return a pair of ints representing the new position of the target
    */
    std::pair<int, int> getNewPositionAfterRightRotation(int i, int j);

    /**
    * Main function to reposition a white corner piece
    *
    * @param &unsolvedPiece SolveStep the current solve step
    */
    void repositionWhiteCornerPiece(SolveStep &unsolvedPiece);

    /**
    * Functions to do the actual cube rotations of the front bottom right
    * corner piece
    */
    void doActualCubeRotations();
    void repositionDownCornerDo();
    void repositionDownCornerRi();
    void repositionDownCornerFr();
};