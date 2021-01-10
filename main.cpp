#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::sort;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;

//defining two possible state of any location (obstacle or empty)
enum class State {kEmpty, kObstacle, kClosed, kPath}; 


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
bool Compare(vector<int>a, vector<int>b){
  int f_a = a[2] + a[3];
  int f_b = b[2] + b[3];
  return f_a>f_b;
}

//sorting cell comparing f-score using cell sort - descending order
void CellSort(vector<vector<int>> *v){
  sort(v->begin(), v->end(), Compare);
}

//Heuristic function here (calculating manhattan distance),
int Heuristic(int x1, int y1, int x2, int y2){
  return abs(x1-x2) + abs(y1-y2); //this heuristic is only for up/donw/l/r movements, for diagonal, we need pythagoras
}

// TODO: Write CheckValidCell here. Check that the 
// cell is on the grid and not an obstacle (i.e. equals kEmpty).


//Add to Open function here, to add nodes to array of open nodes
//x,y coordinate and its g-cost till that cell and h-heuristic value.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open,vector<vector<State>> &grid) {
  vector<int> node{x,y,g,h};
  open.push_back(node);
  grid[x][y] = State::kClosed;
}

//Search function stub here. this will have grid, start and goal of the maze
vector<vector<State>> Search(vector<vector<State>> grid,int init[2], int goal[2]){
  int x = init[0]; //initial point - starting point as first open node
  int y = init[1];
  int g = 0;
  int h = Heuristic(x,y,goal[0],goal[1]);

  vector<vector<int>> open {};
  AddToOpen(x,y,g,h,open,grid);  //adding first node as an open node

  while(open.size()!=0){ //checking if the open vector is non empty
    CellSort(&open); //getting current node from sorted open vector
    vector<int> current_node = open.back(); //getting the current node from open vector list

    int x1 = current_node[0]; //x and y coordinate of the current node
    int y1 = current_node[1];
    grid[x1][y1] = State::kPath; //adding that node to the path
    if(x==goal[0] && y==goal[1]){  //checking if we have reached the goal
      return grid;
    }break; //ending the while loop now
  }
  
  cout<<"No path found!"<<"\n";
  return vector<vector<State>> {};  //returning an empty vector
}

//defining the string to be printed based on state of the position
string CellString(State cell) {    
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
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