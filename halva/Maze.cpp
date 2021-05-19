#include "Maze.h"

Maze::Maze(int rows, int columns)
    : rows(rows), columns(columns), m_maze(new std::vector<std::vector<Node>>) {

  for (int i = 0; i < rows; i++) {
    std::vector<Node> temp;
    for (int j = 0; j < columns; j++) {
      if ((!(i % 2)) or (!(j % 2))) {
        temp.push_back(Node(i, j, true));
      } else {
        temp.push_back(Node(i, j, false));
      }
    }
    m_maze->push_back(temp);
  }
}
Maze::Maze()
    : rows(11), columns(11), m_maze(new std::vector<std::vector<Node>>) {
  for (int i = 0; i < rows; i++) {
    std::vector<Node> temp;
    for (int j = 0; j < columns; j++) {
      if ((!(i % 2)) or (!(j % 2))) {
        temp.push_back(Node(i, j, true));
      } else {
        temp.push_back(Node(i, j, false));
      }
    }
    m_maze->push_back(temp);
  }
}
Maze::~Maze() { delete m_maze; }

Maze::Node &Maze::at(int x, int y) { return (*m_maze)[x][y]; }

void Maze::setWall(int x, int y, bool wall) { (*m_maze)[x][y].wall = wall; }
void Maze::setVisited(int x, int y, bool visited) {
  (*m_maze)[x][y].visited = visited;
}
void Maze::setStart(int x, int y, bool start) { (*m_maze)[x][y].start = start; }
void Maze::setEnd(int x, int y, bool end) { (*m_maze)[x][y].end = end; }

void Maze::print() {
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < columns; y++) {
      if ((*m_maze)[x][y].start) {
        std::cout << "S";
      } else if ((*m_maze)[x][y].end) {
        std::cout << "E";
      } else if ((*m_maze)[x][y].wall) {
        std::cout << "#";
      }
        else if ((*m_maze)[x][y].solution) {
          std::cout << ".";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

bool Maze::hasUnvisitedNeighbour(Node n) {
  if ((n.x > 1) && (!(*m_maze)[n.x - 2][n.y].visited)) {
    return true;
  }
  if ((n.x < rows - 2) && (!(*m_maze)[n.x + 2][n.y].visited)) {
    return true;
  }
  if ((n.y > 1) && (!(*m_maze)[n.x][n.y - 2].visited)) {
    return true;
  }
  if ((n.y < columns - 2) && (!(*m_maze)[n.x][n.y + 2].visited)) {
    return true;
  }

  return false;
}

Maze::Node &Maze::pickRandomUnvisitedNeigbour(Node n) {
  std::vector<Node> temp;
  if ((n.x > 1) && (!(*m_maze)[n.x - 2][n.y].visited)) {
    temp.push_back((*m_maze)[n.x - 2][n.y]);
  }
  if ((n.x < rows - 2) && (!(*m_maze)[n.x + 2][n.y].visited)) {
    temp.push_back((*m_maze)[n.x + 2][n.y]);
  }
  if ((n.y > 1) && (!(*m_maze)[n.x][n.y - 2].visited)) {
    temp.push_back((*m_maze)[n.x][n.y - 2]);
  }
  if ((n.y < columns - 2) && (!(*m_maze)[n.x][n.y + 2].visited)) {
    temp.push_back((*m_maze)[n.x][n.y + 2]);
  }
  size_t a = rand() % temp.size();
  return (*m_maze)[temp[a].x][temp[a].y];
}

void Maze::setStartAndEnd() {
  if ((columns == 3) && (rows == 3)) {
    startCoords = std::make_pair(1, 1);
    endCoords = startCoords;
    std::vector<Node> temp;
    temp.push_back((*m_maze)[1][0]);
    temp.push_back((*m_maze)[0][1]);
    temp.push_back((*m_maze)[1][2]);
    temp.push_back((*m_maze)[2][1]);
    int first = rand() % temp.size();
    int second = rand() * (temp.size() - 1) / RAND_MAX;
    if (second >= first)
      second++;
    (*m_maze)[temp[first].x][temp[first].y].start = true;
    (*m_maze)[temp[second].x][temp[second].y].end = true;
  } else {
    std::vector<std::pair<Node, Node>> result;
    for (int x = 1; x < rows - 2; x += 2) {
      result.push_back(std::make_pair((*m_maze)[x][1], (*m_maze)[x][0]));
    } // Vänster
    for (int y = 3; y < columns; y += 2) {
      result.push_back(std::make_pair((*m_maze)[1][y], (*m_maze)[0][y]));
    } // Uppe
    for (int x = 3; x < rows; x += 2) {
      result.push_back(
          std::make_pair((*m_maze)[x][columns - 2], (*m_maze)[x][columns - 1]));
    } // Höger
    for (int y = 1; y < columns - 2; y += 2) {
      result.push_back(
          std::make_pair((*m_maze)[rows - 2][y], (*m_maze)[rows - 1][y]));
    } // Nere

    int first = rand() % result.size();
    int second = rand() * (result.size() - 1) / RAND_MAX;
    if (second >= first)
      second++;

    (*m_maze)[result[first].second.x][result[first].second.y].start = true;
    (*m_maze)[result[first].second.x][result[first].second.y].wall = true;
    startCoords = std::make_pair(result[first].first.x, result[first].first.y);

    (*m_maze)[result[second].second.x][result[second].second.y].end = true;
    (*m_maze)[result[first].second.x][result[first].second.y].wall = true;
    endCoords = std::make_pair(result[second].first.x, result[second].first.y);
  }
}

void Maze::reset() {
  for (auto &&row : (*m_maze)) {
    for (auto &&node : row) {
      node.visited = false;
    }
  }
}

void Maze::openWall(Node n, Node g) {
  if (n.x == (g.x - 2))
    (*m_maze)[n.x + 1][n.y].wall = false;
  if (n.x == (g.x + 2))
    (*m_maze)[n.x - 1][n.y].wall = false;
  if (n.y == (g.y - 2))
    (*m_maze)[n.x][n.y + 1].wall = false;
  if (n.y == (g.y + 2))
    (*m_maze)[n.x][n.y - 1].wall = false;
}

void Maze::generate () { 



    setStartAndEnd();
    reset();
    std::stack<Node> stack;

    Node &n = (*m_maze)[startCoords.first][startCoords.second];
    n.visited = true;
    stack.push(n);
    while (!stack.empty()) {
      n = stack.top();
      stack.pop();
      if (hasUnvisitedNeighbour(n)) {
        stack.push(n);
        Node &g = pickRandomUnvisitedNeigbour(n);
        openWall(n, g);
        g.visited = true;
        stack.push(g);
      }
    }
}

void Maze::solve() {
  reset();

  std::stack<Node> stack;

  Node &n = (*m_maze)[startCoords.first][startCoords.second];
  n.solution = true;
  stack.push(n);
  while (!stack.empty()) {
    n = stack.top();
    stack.pop();
    n.visited = true;
    if ((n.x == endCoords.first) && (n.y == endCoords.second))  {
      break;
    }
    if (hasOpenPath(n)) {
      stack.push(n);
      Node &g = pickRandomPath(n);
      g.solution = true;
      g.visited = true;
      stack.push(g);
    } else {
      (*m_maze)[n.x][n.y].solution=false;
    }
  }
}

Maze::Node &Maze::pickRandomPath(Node n) {
  std::vector<Node> temp;
  if ((!(*m_maze)[n.x - 1][n.y].visited) && (!(*m_maze)[n.x - 1][n.y].wall)) {
    temp.push_back((*m_maze)[n.x - 1][n.y]);
  }
  if ((!(*m_maze)[n.x + 1][n.y].visited) && (!(*m_maze)[n.x + 1][n.y].wall)) {
    temp.push_back((*m_maze)[n.x + 1][n.y]);
  }
  if ((!(*m_maze)[n.x][n.y - 1].visited) && (!(*m_maze)[n.x][n.y - 1].wall)) {
    temp.push_back((*m_maze)[n.x][n.y - 1]);
  }
  if ((!(*m_maze)[n.x][n.y + 1].visited) && (!(*m_maze)[n.x][n.y + 1].wall)) {
    temp.push_back((*m_maze)[n.x][n.y + 1]);
  }
  size_t a = rand() % temp.size();
  return (*m_maze)[temp[a].x][temp[a].y];
}

bool Maze::hasOpenPath(Node n) {
  if ((!(*m_maze)[n.x - 1][n.y].visited) && (!(*m_maze)[n.x - 1][n.y].wall)) {
    return true;
  }
  if ((!(*m_maze)[n.x + 1][n.y].visited) && (!(*m_maze)[n.x + 1][n.y].wall)) {
    return true;
  }
  if ((!(*m_maze)[n.x][n.y - 1].visited) && (!(*m_maze)[n.x][n.y - 1].wall)) {
    return true;
  }
  if ((!(*m_maze)[n.x][n.y + 1].visited) && (!(*m_maze)[n.x][n.y + 1].wall)) {
    return true;
  }

  return false;
}