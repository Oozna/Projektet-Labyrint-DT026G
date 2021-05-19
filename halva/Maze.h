#pragma once
#include <vector>
#include <stack> 
#include <iostream>

class Maze {
public:
  struct Node {
    int x, y;
    bool wall = false;
    bool start = false;
    bool end = false;
    bool visited = false;
    bool solution = false;
    Maze::Node(int x, int y, bool wall) {
      this->x = x;
      this->y = y;
      this->wall = wall;
    }
  };
  Maze(); // Fyller 11x11 labyrint med noder som inte är väggar
  Maze(int rows, int columns); // Samma som ovan fast en användarbestämd storlek
  ~Maze();
  Node& at(int x, int y);
  void setWall(int x, int y, bool wall);
  void setVisited(int x, int y, bool visited);
  void setStart(int x, int y, bool start);
  void setEnd(int x, int y, bool end);
  void setStartAndEnd();
  void print();
  void generate();
  void reset();
  void openWall(Node n, Node g);
  void solve();
  Node &pickRandomUnvisitedNeigbour(Node n);
  Node &pickRandomPath(Node n);
  bool hasUnvisitedNeighbour(Node n);
  bool hasOpenPath(Node n);

  int rows = 11, columns = 11;
  std::pair<int, int> startCoords;
  std::pair<int, int> endCoords;
  std::vector<std::vector<Node>> *m_maze;
};
