#pragma once

#include "cube_face.h"

/** Local headers **/
#include "util.h"

/** System headers **/
#include <array>
#include <string>
#include <vector>

class Cube
{
  private:
    
    std::array<CubeFace, 6> cubeState; // 6-item array holding cube state
    std::vector<std::string> moveHistory; // vector of rotation history

    /**
    * Function to retrieve a face at a specific orientation
    *
    * @param orientation FaceOrientation the orientation of the face to 
    * retrieve
    *
    * @return a const copy of the cube face
    */
    const CubeFace getFaceAtOrientation(FaceOrientation orientation);

  public:

    /**
    * Main cube constructor
    *
    * @param faces std::array<CubeFace, 6> array of CubeFace to model start 
    * state of Rubik's cube
    */
    Cube(std::array<CubeFace, 6> faces);

    /**
    * Function to print the current state of the cube. Format is:
    * 
    *         O W R
    *         W W W -- TOP
    *  LEFT   Y W Y         RIGHT
    *   |     - - -        /
    * G B B | R O R | G G B | W R Y
    * G B R | B O Y | O G B | Y R Y -- BACK
    * W B W | R R W | O Y O | Y O O
    *        /- - -
    *       / G G B
    *  FRONT  O Y R -- DOWN
    *         G G B
    */
    void printCube() const;

    /**
    * Function to print the history of moves that have been performed
    */
    void printMoveHistory() const;

    /**
    * Function to return a read only iterator to the start of the cube faces
    *
    * @return an iterator of type std::array<CubeFace, 6>::const_iterator to 
    * the start of the array of CubeFace
    */
    std::array<CubeFace, 6>::const_iterator roBegin() const;

    /**
    * Function to return a read only iterator to the end of the cube faces
    *
    * @return an iterator of type std::array<CubeFace, 6>::const_iterator to 
    * the end of the array of CubeFace
    */
    std::array<CubeFace, 6>::const_iterator roEnd() const;

    /**
    * Function to return the color of the cell at a specific position on the cube
    *
    * @param orientation FaceOrientation the orientation to lookup
    * @param i int the i position on the face
    * @param j int the j position on the face
    *
    * @return the FaceColor at the specified position
    */
    FaceColor getColorAtFaceAndLocation(FaceOrientation orientation, 
                                        int i, int j);

    /**
    * These functions rotate the entire cube, which means the F, R, L, U, D, 
    * and B faces change
    */
    void rotateCubeClockwise();
    void rotateCubeAntiClockwise();
    void rotateCubeUp();
    void rotateCubeDown();
    void rotateCubeLeft();
    void rotateCubeRight();

    /** 
    * These are the main rotation procedures
    */
    void r();
    void ri();
    void l();
    void li();
    void f();
    void fi();
    void u();
    void ui();
    void d();
    void di();
    void b();
    void bi();
};