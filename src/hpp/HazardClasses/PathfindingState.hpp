#ifndef HAZARD_PATHFINDERINPUTOBJECT_HPP
#define HAZARD_PATHFINDERINPUTOBJECT_HPP

#include "HazardClasses/GridHandler.hpp"
#include "HazardTypedef.hpp"

struct PathfindingNode;
struct PathfindingNodesBlock;

class PathfindingState {

public:
  PathfindingState(GridHandler* nestedClass);

  PathfindingNode* VisionTargetSearch(int32_t param_1, int32_t param_2, int32_t param_3, uint32_t param_4);
  void GenerateInitialPathNodes(int32_t param_1, int32_t param_2, int32_t eyeRelated);
  int32_t SearchForNearestObject(int32_t param_1, int32_t param_2, int32_t param_3, int32_t unused, int32_t param_5);
  int32_t IsCoordinateVisited(int32_t param_1, int32_t param_2);
  int32_t PushOpenNode(PathfindingNode* param_1, uint32_t param_2, uint32_t param_3, byte param_4, int16_t param_5);
  PathfindingNode* AStarPathfinding_NavigateAroundObjects(int32_t param_1, int32_t param_2, int32_t param_3);
  void SetStartAndTargetCoordinates(int32_t param_1, int32_t param_2, int32_t param_3, int32_t param_4);
  int32_t FindObjectByFlags(int32_t position1, int32_t position2, int32_t eyeValue, uint32_t param_4);

  PathfindingNode* __fastcall PopHighestPriorityNodeFromOpenList();
  PathfindingNode* FindPath_AvoidWallsAndUnits();
  PathfindingNode* FindPath_AvoidWallsOnly();
  PathfindingNode* __fastcall AllocatePathNode();
  void __fastcall ReturnMemoryPool();

  PathfindingNode* currentlyProcessedNode;
  PathfindingNode* headCircularPathList;
  PathfindingNode* currentBestNode;
  PathfindingNode* startOfArray[256];
  int32_t currentPathCost;
  int32_t currentDirection;
  int32_t currentCoord1;
  int32_t currentCoord2;
  int32_t targetPackedCoordinate;
  int32_t countNodesUsed;
  PathfindingNodesBlock* nodeAllocation_2;
  PathfindingNodesBlock* nodeAllocation_1;
  GridHandler* gridHandler;
};

#endif
