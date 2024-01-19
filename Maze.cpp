//
// Created by jessi on 1/18/2024.
//


#include <fstream>
#include <iostream>
#include <vector>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using namespace std;
int lastvalue; //biggest value
vector<vector<int>> parentlist;
vector<int> temp;
vector<int> path;
int parent = 1;
int cost = 0;
//Outputs the full maze is used for testing
void printMaze(){
    for (const auto& row : parentlist) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}
//Gets the last value in the maze
void isItLast(int number){
    if(number < lastvalue){
        return;
    }else{
        lastvalue = number;
    }
}
//Removes the deadend from vector
void deadEndHelper(int dead){
    int j = 0;
    for (auto & element : parentlist){
        j++;
        for(int i =0; i < element.size(); i++){
            if(element[i] == dead){
                element.erase(element.begin()+i);
                if(i==1){
                    parentlist.erase(parentlist.begin()+j);
                }
            }
        }
    }
}
//Finds the dead ends in vector
void isDeadEnd(){
    for (const auto& row : parentlist) {
        for (const auto& elem : row) {
            if(elem != lastvalue && row.size() == 1) {
                deadEndHelper(elem);
            }
        }
    }
}
//Output the shortest path
void shortPath(){
    cout<<"The shortest path is: " << endl;
    cout<< "[";
    for(int i = 0; i < path.size(); i++) {
        if (i == path.size() - 1) {
            cout << path[i] << "]" << endl;
        } else {
            cout << path[i] << ", ";
        }
    }
    cout<<"The path cost is: " << cost << endl;
}
//finds the shortest path
void paths(){
    parent = 1;
    path.clear();
    path.push_back(parent);
    cost = 0;
    cost += parent;
//Goes through the vectors to find the shortest path
    for (auto & element : parentlist){
        for(int i = 0; i < element.size(); i++){
            if(element[0] == lastvalue){
                return;
            }
            if(element[0] == parent ){
//The smallest cost is always the first element
                parent = element[1];
                cost+= parent;
                path.push_back(parent);
            }
        }
    }
}
//Reads from file
void readfile(){
    string filename("C:\\Users\\jessi\\CLionProjects\\Assignment#6\\my-maze.txt");
    int number; int ispair = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        exit(0);
    }
    while (input_file >> number) {
//Resets for next line
        if (number == -1) {
            ispair = 0;
            parentlist.push_back(temp);
            temp.clear();
            continue;
        }
//Start of maze
        if (number == 1) {
            ispair++;
            temp.push_back(number);
            continue;
        }
        ispair++;
//Add the line to a temporary vector
        if (ispair == 1 || ispair == 2 || ispair == 3) {
            isItLast(number);
            temp.push_back(number);
        }
    }
//remove all possible deadends
    for(int i = 0; i < lastvalue; i++){
        isDeadEnd();
    }
    input_file.close();
}
int main() {
    readfile();
    paths();
    shortPath();
}
//Output for test-maze.txt:
// The shortest path is:
// [1, 2, 3, 5, 6]
// The path cost is: 17
//Output for maze.txt:
// The shortest path is:
// [1, 2, 3, 8, 9, 10, 11, 12, 16, 17, 18, 30, 31, 32, 33, 34, 35, 36, 37, 39,
// 40, 41, 42, 45, 46, 47, 48, 49, 50, 51, 52,
// 53, 55, 57, 58, 59, 60, 61, 62, 91, 92, 95, 96, 97, 98, 99, 100]
// The path cost is: 2158
//Output for my-maze.txt:
// The shortest path is:
// [1, 2, 3, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24,
//  26, 27, 28, 29, 30]
// The path cost is: 408

