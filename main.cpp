#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

//defining two possible state of any location (obstacle or empty)
enum class State {kEmpty, kObstacle, kClosed}; 


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

//Heuristic function here,
int Heuristic(int x1, int y1, int x2, int y2){
  return abs(x1-x2) + abs(y1-y2); //this heuristic is only for up/donw/l/r movements, for diagonal, we need pythagoras
}

//Add to Open function here, to add nodes to array of open nodes
//x,y coordinate and its g-cost till that cell and h-heuristic value.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>>&open_nodes,vector<vector<State>>&state_of_nodes) {
  vector<int> node{x,y,g,h};
  open_nodes.push_back(node);
  state_of_nodes[x][y] = State::kClosed;
}

//Search function stub here. this will have board, start and goal of the maze
vector<vector<State>> Search(vector<vector<State>> board,int init[2], int goal[2]){
  cout<<"No path found!"<<"\n";
  return vector<vector<State>> {};  //returning an empty vector
}

//defining the string to be printed based on state of the position
string CellString(State cell) {    
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    default: return "0   "; 
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
  int init[2] = {0,0}; //defining a start of the path
  int goal[2] = {4,5}; //defining end of the path
  auto board = ReadBoardFile("1.board"); //reading the maze from txt file
  auto solution = Search(board,init,goal); //getting the solution of the maze
  PrintBoard(solution); 
}