#pragma once

/** Local headers */
#include "step.h"
#include "util.h"

/** System headers */
#include <unordered_map>
#include <utility>

class Cross : Step 
{
  public:

    /** 
    * Main Cross constructor
    *
    * @param &cube Cube
    */
    Cross(Cube &cube);

    /**
    * Main function to start the logic to solve the cross.
    */
    void solveCross();

  private:

    // map of targets for white cross
  	std::unordered_map<FaceColor, std::pair<int, int>> targets;

    /**
    * Function to find the next unsolved cross piece piece. This function
    * sets the input item to the next unsolved target.
    *
    * @param &item SolveStep the item to set
    * @return boolean, true if there is still an unsolved piece, else false
    */
  	bool nextUnsolvedCrossPiece(SolveStep &item);

    /**
    * Function to reorient the cube so that the white face is UP.
    */
    void reorientWhiteFaceToTop();

    /**
    * Function to find the FaceOrientation where the white center is.
    *
    * @return the face orientation of the white center
    */
    FaceOrientation findWhiteCenter();

    /**
    * Function to setup the target locations on the white cross
    */
    void setupTargetLocations();

    /**
    * Main function to reposition a white cross piece to solve the cross.
    *
    * @param target SolveStep the target of the white cross piece
    */
    void repositionWhiteCrossPiece(const SolveStep target);

    /**
    * Function to reposition a top white piece to the bottom.
    *
    * @param i int i position of the piece to reposition
    * @param j int j position of the piece to reposition
    */
    void repositionTopWhitePiece(int i, int j);

    /**
    * Function to reposition a top inverse white piece to the bottom.
    *
    * @param orientation FaceOrientation the orientation where the piece
    *        is located
    */
    void repositionTopInverseWhitePiece(FaceOrientation orientation);

    /**
    * Function to reposition a middle white piece to the bottom.
    *
    * @param orientation FaceOrientation the orientation where the piece
    *        is located
    * @param j int j position of the piece to reposition
    */
    void repositionMiddleWhitePiece(FaceOrientation orientation, int j);

    /**
    * Function to reposition a bottom inverse white piece to the bottom.
    *
    * @param orientation FaceOrientation the orientation where the piece
    *        is located
    */
    void repositionBottomInverseWhitePiece(FaceOrientation orientation);

    /**
    * Function to reposition a bottom inverse white piece to the bottom.
    *
    * @param i int the i position of the piece to reposition
    * @param j int the j position of the piece to reposition
    * @param targetFace FaceColor the FaceColor of the target on the cube
    */
    void repositionBottomWhitePiece(int i, int j, FaceColor targetFace);
};