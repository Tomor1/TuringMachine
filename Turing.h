#pragma once
#include<string>
#include<string.h>
#include<set>
#include<vector>
using namespace std;

extern set<string>Q;
extern set<char>S;//input symbol
extern set<char>G;//tape symbol
extern vector<vector<string>> trans_func;
extern string q0;
extern char B;
extern set<string>F;
extern int N;
static bool verbose;

