#pragma once

/** Local headers */
#include "step.h"
#include "util.h"

/** System headers */
#include <unordered_map>
#include <utility>

class WhiteCross : Step 
{
  public:

    /** 
    * Main Cross constructor
    *
    * @param &cube Cube
    */
    WhiteCross(Cube &cube);

    /**
    * solveStep function implementation for white cross
    */
    void solveStep();

  private:

    /**
    * Function to find the next unsolved cross piece. This function
    * sets the input item to the next unsolved target.
    *
    * @param &unsolvedPiece SolveStep the item to set
    * @return boolean, true if there is still an unsolved piece, else false
    */
  	bool nextUnsolvedCrossPiece(SolveStep &unsolvedPiece);

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
    * Note: "Inverse" means the white cell is on the front, left, right,
    *       or back face
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
    * Note: "inverse" means the white cell is on the front, left, right,
    *       or back face
    *
    * @param orientation FaceOrientation the orientation where the piece
    *        is located
    */
    void repositionBottomInverseWhitePiece(FaceOrientation orientation);

    /**
    * Given an end face for the white cross, this function returns the
    * rotation function needed to move the piece to the final position
    *
    * @param endFace FaceOrientation the orientation of the target face
    * @return an std::function pointing to the rotation function
    */
    std::function<void(Cube&)> getRotationForFinalPosition(
      FaceOrientation endFace
    );

    /**
    * Get the number of down rotations needed to match the startFace
    * with the endFace.
    *
    * @param startFace FaceOrientation the starting face
    * @param endFace FaceOrientation the ending face
    */
    int getNumRotationsBetweenFaces(FaceOrientation startFace,
                                    FaceOrientation endFace);

    /**
    * Function to reposition a bottom white piece to the final position.
    *
    * @param int i the i position of the piece
    * @param int j the j position of the piece
    * @param endFace FaceOrientation the end face of the piece
    */
    void repositionBottomWhitePiece(int i, 
                                    int j, 
                                    FaceOrientation endFace);
};