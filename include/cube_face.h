#pragma once

/** Local headers */
#include "util.h"

/** System headers */
#include <array>

class CubeFace
{
  private:

    FaceOrientation currentOrientation; // The current orientation of the face

  public:

    std::array<std::array<FaceColor,3>,3> squares; // the colors on the face
    
    /**
    * Default CubeFace constructor
    *
    * Note: 
    * A CubeFace constructed with the default constructor is not a valid 
    * cubeface. The currentOrientation and squares variables must be defined 
    * to use the face.
    */
    CubeFace();

    /**
    * Main CubeFace constructor
    *
    * @param orientation FaceOrientation the orientation of the face
    * @param squares std::array<std::array<FaceColor,3>,3> a 3x3 matrix to 
    *        define the state of the face
    */
    CubeFace(FaceOrientation orientation, 
             std::array<std::array<FaceColor,3>,3> squares);

    /**
    * Function to print a row of the CubeFace
    *
    * @param rowIndex int the index of the row to print
    * @param &stringBuf std::ostream the stream to print to
    */    
    void printRow(int rowIndex, std::ostream &stringBuf) const;

    /**
    * Function to set the orientation of the face
    *
    * @param newOrientation FaceOrientation the face orientation to use
    */
    void setOrientation(FaceOrientation newOrientation);

    /**
    * Function to get the orientation of the face
    *
    * @return the current orientation of the face
    */
    FaceOrientation getOrientation() const;

    /**
    * Function to get the color at a specific location on the face
    *
    * @param i int the i position
    * @param j int the j position
    * @return the FaceColor at the given i,j position
    */
    FaceColor getColorAtIndices(int i, int j) const;

    /**
    * Function to rtoate the face clockwise
    */
    void rotateFaceClockwise();

    /**
    * Function to rtoate the face anti-clockwise
    */
    void rotateFaceAntiClockwise();
};