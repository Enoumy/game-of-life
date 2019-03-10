#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;

const int numberOfFrames = 500;

bool** generateSquareBooleanArray(int n);
bool** generateRandomFrame(int n);
bool** generateTrueFrame(int n);
bool** generateFalseFrame(int n);
bool** generateSaturatedFrame(int n, bool value);
void print2DBooleanArray(bool**, int n);
char getRepresentation(bool x);
bool** generateNextFrame(bool** a, int n);
bool livesOn(bool** a, int n, int y, int x);
int cellsAroundCell(bool** a, int n, int y, int x);
string readFile(string fileName);
bool** readFrameFromFile(string fileName);
int numberOfLinesInFile(string fileName);


bool** generateSquareBooleanArray(int n){
    bool** out = (bool**) malloc(sizeof(bool*) * n);
    for(int y = 0; y < n; y++)
        out[y] = (bool*) malloc(sizeof(bool) * n);
    return out;
}

bool** generateRandomFrame(int n){
    bool** out = generateSquareBooleanArray(n);
    srand(time(0));
    for(int y = 0; y < n; y++)
        for(int x = 0; x < n; x++)
            out[y][x] = rand()%2==1;
    return out;
}

bool** generateSaturatedFrame(int n, bool value){
    bool** out = generateSquareBooleanArray(n);
    srand(time(0));
    for(int y = 0; y < n; y++)
        for(int x = 0; x < n; x++)
            out[y][x] = value;
    return out;
}

bool** generateTrueFrame(int n){
    return generateSaturatedFrame(n, true);
}

bool** generateFalseFrame(int n){
    return generateSaturatedFrame(n, false);
}

void print2DBooleanArray(bool** a, int n){
    cout << " ";
    for(int i = 0; i < n; i++) cout << "_";
    cout << endl;
    for(int y = 0; y < n; y++){
        cout << "|";
        for(int x = 0; x < n; x++) cout << getRepresentation(a[y][x]);
        cout << "|" << endl;
    }
    cout << " ";
    for(int i = 0; i < n; i++) cout << "_";
    cout << endl;
}

char getRepresentation(bool x){
    if(x) return 'X';
    return ' ';
}

bool** generateNextFrame(bool** a, int n){
    bool** out = generateSquareBooleanArray(n);
    for(int y = 0; y < n; y++)
        for(int x = 0; x < n; x++)
            out[y][x] = livesOn(a, n, y, x);
    return out;
}

bool livesOn(bool** a, int n, int y, int x){
    int neighbors = cellsAroundCell(a, n, y, x);
    //Rules for Conway's game of life
    if(a[y][x]&&neighbors<2) return false;
    if(a[y][x]&&neighbors>=2&&neighbors<=3) return true;
    if(a[y][x]&&neighbors>3) return false;
    if(!a[y][x]&&neighbors==3) return true;
    return false;
}

int cellsAroundCell(bool** a, int n, int y, int x){
    int sum = 0;
    if(x>0&&a[y][x-1]) sum++; //Left Cell
    if(x>0&&y>0&&a[y-1][x-1]) sum++; //Top Left Cell
    if(y>0&&a[y-1][x]) sum++; //Top Cell
    if(y>0&&x<n-1&&a[y-1][x+1]) sum++; //Top Right Cell
    if(x<n-1&&a[y][x+1]) sum++; //Right Cell
    if(x<n-1&&y<n-1&&a[y+1][x+1]) sum++; //Bottom Right Cell
    if(y<n-1&&a[y+1][x]) sum++; //Bottom Cell
    if(y<n-1&&x>0&&a[y+1][x-1]) sum++;
    return sum;
}

string readFile(string fileName){
    ifstream t(fileName);
    string str;
    t.seekg(0, ios::end);
    str.reserve(t.tellg());
    t.seekg(0,ios::beg);
    str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    return str;
}

bool** readFrameFromFile(string fileName){
    string file = readFile(fileName);
    vector<string> lines;
    boost::split(lines, file, boost::is_any_of("\n"));
    bool** out = generateSquareBooleanArray(lines.size());
    for(int y = 0; y < lines.size(); y++)
        for(string::size_type i = 0; i < lines[y].size(); i++)
            out[y][i] = lines[y][i] == '1';
    return out;
}

int numberOfLinesInFile(string fileName){
    string file = readFile(fileName);
    vector<string> lines;
    boost::split(lines, file, boost::is_any_of("\n"));
    return lines.size()-1;
}

int main(){
    string fileName = "blinker.txt";
    int n = numberOfLinesInFile(fileName); // Size of square board
    bool** currentFrame;
    bool** nextFrame;

    currentFrame = readFrameFromFile(fileName);
    print2DBooleanArray(currentFrame, n);


    while(true){
        nextFrame = generateNextFrame(currentFrame, n);
        free(currentFrame);
        currentFrame = nextFrame;
        sleep(1);
        system("clear");
        print2DBooleanArray(currentFrame, n);
    }

    // sleep(1);
    // system("clear");
    //
    // nextFrame = generateNextFrame(currentFrame, n);
    // free(currentFrame);
    // currentFrame = nextFrame;
    // print2DBooleanArray(currentFrame, n);

    return 0;
}
