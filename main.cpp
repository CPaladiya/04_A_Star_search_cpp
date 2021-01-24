#include <algorithm> //for sort
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
using std::cout;
using std::ifstream;
using std::sort;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

//defining two possible state of any location (obstacle or empty)
enum class State {kStart, kFinish, kEmpty, kObstacle, kClosed, kPath}; 
const float delta[8][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};


//function to read each line and returning states based on value of 0 and 1
vector<State> ParseLine(string line) {   
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}

//function to read line from the txt file given at some path
vector<vector<State>> ReadBoardFile(string path) {   
  ifstream myfile (path);  //defining a stream named myfile with path given in the bracket
  vector<vector<State>> board{};
  if (myfile) {   //if the stream is created myfile will be true
    string line;
    while (getline(myfile, line)) { //getting line by line from the stream
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

//comparing two nodes for its f=g+h values, true if first node is greater than the next one.
bool Compare(vector<float>a, vector<float>b){
  int f_a = a[2] + a[3];
  int f_b = b[2] + b[3];
  return f_a>f_b;
}

//sorting cell comparing f-score using cell sort - descending order
void CellSort(vector<vector<float>> *v){
  sort(v->begin(), v->end(), Compare);
}

//Heuristic function here (calculating manhattan distance),
int Heuristic(float x1, float y1, float x2, float y2){
  return sqrt(pow(x1-x2,2.0) + pow(y1-y2,2.0)); //this heuristic is only for up/donw/l/r movements, for diagonal, we need pythagoras
}

// TODO: Write CheckValidCell here. Check that the 
// cell is on the grid and not an obstacle (i.e. equals kEmpty).returns true if the cell is empty and on the grid
bool CheckValidCell(float x, float y, vector<vector<State>> &grid){
  bool x_bool = (x>=0 && x<grid.size());
  bool y_bool = (y>=0 && y<grid[0].size());
  if(x_bool && y_bool && grid[x][y] != State::kClosed) 
      return  grid[x][y] == State::kEmpty;
  return false;
}

//Add to Open function here, to add nodes to array of open nodes
//x,y coordinate and its g-cost till that cell and h-heuristic value.
void AddToOpen(float x, float y, float g, float h, vector<vector<float>> &open,vector<vector<State>> &grid) {
  vector<float> node{x,y,g,h};
  open.push_back(node);
  grid[x][y] = State::kClosed;
}

//expand current nodes to neighbours and add them to the open list
void ExpadNeighbors(vector<float> &current_node, float goal[2], vector<vector<float>> &open, vector<vector<State>>&grid){
  float x = current_node[0]; //getting the current node data
  float y = current_node[1];
  
  //getting info on neighbors using directional deltas
  for (int i = 0; i < 8; i++) {
    float x_n = x + delta[i][0];
    float y_n = y + delta[i][1];
    //checking if the neighbor is valid
    if (CheckValidCell(x_n,y_n,grid)){
      float new_g = current_node[2] + Heuristic(current_node[0],current_node[1],x_n,y_n);
      float new_h = Heuristic(x_n,y_n,goal[0],goal[1]);
      AddToOpen(x_n,y_n,new_g,new_h,open,grid);
    }
  }
}

//Search function stub here. this will have grid, start and goal of the maze
vector<vector<State>> Search(vector<vector<State>> grid,float init[2], float goal[2]){
  float x1 = init[0]; //initial point - starting point as first open node
  float y1 = init[1];
  float g = 0;
  float h = Heuristic(x1,y1,goal[0],goal[1]);

  vector<vector<float>> open {};
  AddToOpen(x1,y1,g,h,open,grid);  //adding first node as an open node

  while(open.size()>0){ //checking if the open vector is non empty
    CellSort(&open); //getting current node from sorted open vector
    vector<float> current_node = open.back(); //getting the current node from open vector list
    open.pop_back();//removing the last node from open node

    float x = current_node[0]; //x and y coordinate of the current node
    float y = current_node[1];
    grid[x][y] = State::kPath; //adding that node to the path
    if(x==goal[0] && y==goal[1]){  //checking if we have reached the goal
      grid[x1][y1] = State::kStart;
      grid[x][y] = State::kFinish;
      return grid;
      break;
    }
    ExpadNeighbors(current_node,goal,open,grid);
  }
  
  cout<<"No path found!"<<"\n";
  return vector<vector<State>>{};  //returning an empty vector
}

//defining the string to be printed based on state of the position
string CellString(State cell) {    
  switch(cell) {
    case State::kObstacle: return " XXXX "; //"⛰️   "
    case State::kPath: return "   GO   "; //"🚗   "
    case State::kStart : return " !START! "; //"🚦   "
    case State::kFinish : return " @@@@@ "; //"🏁   "
    default: return " _    _ "; 
  }
}

//loops to print the board - visual output
void PrintBoard(const vector<vector<State>> board) {  
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}


int main() {
  float init[2] = {0,0}; //defining a start of the path
  float goal[2] = {4,5}; //defining end of the path
  auto board = ReadBoardFile("C:/Users/chira/Desktop/Temp/1.board.txt"); //reading the maze from txt file
  auto solution = Search(board,init,goal); //getting the solution of the maze
  PrintBoard(solution); 
  return 0;
}
