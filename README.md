# 04_A_Star_search_cpp
Showcase : Implementation of A-Star Search Algorithm for 2D (X,Y) grid

## Print board input file
Setting up obstacles and free space within the grid
- Referring to file `1.board.txt`

![Grid](https://user-images.githubusercontent.com/74514429/105792908-2f47e880-5f56-11eb-90fe-b3243baf6de2.png)

Default **Start** is set to grid point (0,0) and **Goal/Finish** point is set to (0,11)

## Modify default and setting up different Start and Finish point
- Start point can be set here at [LINE 162](https://github.com/CPaladiya/04_A_Star_search_cpp/blob/f98256a46f3397b1016acacad94d11498af3211f/main.cpp#L162) on main.cpp
- Finish/Goal point can be set here at [LINE 163](https://github.com/CPaladiya/04_A_Star_search_cpp/blob/f98256a46f3397b1016acacad94d11498af3211f/main.cpp#L163) on main.cpp

## Example of the output

In the image below
- `"!START!"` represents the default Start Point `(0,0)`
- `"!!HOME!!"` represents the default Goal/Finish Point `(0,11)`
- `"___GO___"` is the path created by application to reach to Goal from the Start Point
- `"XXXXX"` signifies the roadblock/obstacles on the maze

![Output](https://user-images.githubusercontent.com/74514429/105793877-eb55e300-5f57-11eb-9abd-1a8e82aa6ef6.png)

## Other examples

![Output1](https://user-images.githubusercontent.com/74514429/105795365-b303d400-5f5a-11eb-8aef-3f23afce6b32.png)

![Output2](https://user-images.githubusercontent.com/74514429/105795390-c1ea8680-5f5a-11eb-9406-b5f6b0efe3de.png)
