#include "step.h"
#include "util.h"
#include <unordered_map>
#include <utility>

class Cross : Step {
  public:
    Cross(Cube &cube);
    bool reachedGoal();
    void reorientWhiteFaceToTop();
    void solveCross();
    FaceColor getAdjacentFaceColor(FaceOrientation orientation, int i, int j);

  private:
  	std::unordered_map<FaceColor, std::pair<int, int>> targets;
  	bool nextUnsolvedCrossPiece(TargetItem &item);

    FaceOrientation findWhiteCenter();
    void setupTargetLocations();
    void repositionWhiteCrossPiece(const TargetItem target);
    void repositionTopWhitePiece(int i, int j);
    void repositionTopInverseWhitePiece(FaceOrientation orientation);
    void repositionMiddleWhitePiece(FaceOrientation orientation, int j);
    void repositionBottomInverseWhitePiece(FaceOrientation orientation);
    void repositionBottomWhitePiece(int i, int j, FaceColor targetFaceColor);
};