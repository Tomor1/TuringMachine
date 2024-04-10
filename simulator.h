#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<set>
#include<vector>
#include<fstream>
#include"parser.h"
using namespace std;
extern string* tape;
extern bool verbose;


int get_tape(string input) {
    for (int i = 0;i < input.length();i++) {
        if (S.find(input[i]) == S.end()) {
            if (verbose==true) {
                cerr << "Input: " << input << endl;
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: Symbol\"" << input[i] << "\"in input is not defined in the set of input symbols" << endl;
                cerr << "Input: " << input << endl;
                cerr << "       ";
                for (int j = 0;j < i;j++) {
                    cerr << " ";
                }
                cerr << "^" << endl;
                cerr << "==================== END ====================" << endl;
                exit(-1);
            }
            else {
                cerr << "illegal input string" << endl;
                exit(-1);
            }
        }
    }
    if (verbose == true) {
        cout << "Input: " << input << endl;
        cout << "==================== RUN ====================" << endl;
    }
        tape = new string[N];
        for (int i = 0;i < N;i++) {
            tape[i] = "_";
        }
        if(input.length()!=0)
            tape[0] = input;
    return 0;
}

int simulate(string input) {
    string old_stage;//对应转移函数中的旧状态
    string new_stage;//对应新状态
    char* old_symbol;//对应旧符号
    char* new_symbol;//对应新符号
    char* direction;//对应纸带头移动方向

    old_stage = q0;
    old_symbol = new char[N];
    new_symbol = new char[N];
    direction = new char[N];

    bool isaccept = false;
    int* pointer = new int[N];
    for (int i = 0;i < N;i++) {
        pointer[i] = 0;
    }


    for (int i = 0;i < N;i++) {
        if (i == 0 && input.length() != 0)old_symbol[0] = input[0];
        else {
            old_symbol[i] = '_';
        }
    }
   /* for (int i = 0;i < N;i++) {
        cout << old_symbol[i] << ' ';
    }cout<<endl;*/
    /*没到结束状态*/
    while (F.find(old_stage) == F.end()) {
        bool halt = true;//没到终止状态就停机
        for (int i = 0;i < trans_func.size();i++) {
            /*找到匹配的zhuangtai*/
            if (trans_func[i][0] == old_stage) {
                for (int j = 0;j < N;j++) {
                    if (((old_symbol[j] != trans_func[i][1][j]) && trans_func[i][1][j] != '*')||(trans_func[i][1][j] == '*'&& old_symbol[j]=='_')) {
                        break;
                    }
                    if (j == N - 1) {
                        /*找到状态以及旧符号匹配的转移函数*/
                        halt = false;

                        //cout << "trans_func:";
                        /*for (int l = 0;l < trans_func[i].size();l++) {
                            cout << trans_func[i][l] << ' ';
                        }cout << endl;*/

                        new_stage = trans_func[i][4];
                        for (int k = 0;k < N;k++) {
                            if (trans_func[i][2][k] == '*') {
                                new_symbol[k] = old_symbol[k];
                            }
                            else {
                                new_symbol[k] = trans_func[i][2][k];
                            }
                            direction[k] = trans_func[i][3][k];
                        }
                    }
                }
            }
            if (halt == false)break;
        }
        //找不到转移函数后停机 并且未接受该字符串
        if (halt == true) {
            cout << "(UNACCEPTED)" << ' ';
            int i = 0;
            int j = tape[0].length() - 1;
            for (;i < tape[0].length();i++) {
                if (tape[0][i] != '_')break;
            }
            for (;j >= 0;j--) {
                if (tape[0][j] != '_')break;
            }
            for (int k = i;k <= j;k++) {
                cout << tape[0][k];
            }cout << endl;
            //cout << tape[0];cout << endl;
            return 0;
        }
        //更改状态
        
        //cout << old_stage << ' ' << new_stage << endl;
        //cout << "old_symbol:";
        //for (int i = 0;i < N;i++) {
        //    cout << old_symbol[i] << ' ';
        //}cout << endl;
        //cout << "new_symbol:";
        //for (int i = 0;i < N;i++) {
        //    cout << new_symbol[i] << ' ';
        //}cout << endl;
        //cout << "direction:";
        //for (int i = 0;i < N;i++) {
        //    cout << direction[i] << ' ';
        //}cout << endl;

        old_stage = new_stage;
        for (int i = 0;i < N;i++) {
            tape[i][pointer[i]] = new_symbol[i];
            if (direction[i] == 'l') {
                if (pointer[i] > 0) {
                    pointer[i] -= 1;
                }
                else {
                    tape[i] = "_" + tape[i];
                }
            }
            else if (direction[i] == 'r') {
                if (pointer[i] == tape[i].length() - 1) {
                    tape[i] = tape[i] + "_";
                }
                pointer[i] += 1;
            }
            else;
        }
        /*for (int i = 0;i < N;i++) {
            if (direction[i] == 'l') {
                if (pointer[i] > 0) {
                    pointer[i] -= 1;
                }
                else {
                    tape[i] = "_" + tape[i];
                }
            }
            else if (direction[i] == 'r') {
                if (pointer[i] == tape[i].length() - 1) {
                    tape[i] = tape[i] + "_";
                }
                pointer[i] += 1;
            }
            else;
        }*/
        for (int i = 0;i < N;i++) {
            old_symbol[i] = tape[i][pointer[i]];
        }
    }
    cout << "(ACCEPTED)" << ' ';
    int i = 0;
    int j = tape[0].length() - 1;
    for (;i < tape[0].length();i++) {
        if (tape[0][i] != '_')break;
    }
    for (;j >= 0;j--) {
        if (tape[0][j] != '_')break;
    }
    for (int k = i;k <= j;k++) {
        cout << tape[0][k];
    }
    cout << endl;
    //cout << tape[0];cout << endl;
    return 0;
}

int verbose_simulate(string input) {
    string old_stage;//对应转移函数中的旧状态
    string new_stage;//对应新状态
    char* old_symbol;//对应旧符号
    char* new_symbol;//对应新符号
    char* direction;//对应纸带头移动方向

    old_stage = q0;
    old_symbol = new char[N];
    new_symbol = new char[N];
    direction = new char[N];

    int* pointer = new int[N];
    int* head = new int[N];
    for (int i = 0;i < N;i++) {
        pointer[i] = 0;
        head[i] = 0;
    }


    for (int i = 0;i < N;i++) {
        if (i == 0 && input.length() != 0)old_symbol[0] = input[0];
        else {
            old_symbol[i] = '_';
        }
    }
     /*没到结束状态*/

    int step = 0;
    bool acc = false;
    while (acc == false) {
        if (F.find(old_stage) != F.end()) {
            acc = true;
        }
        bool halt = true;//没到终止状态就停机
        for (int i = 0;i < trans_func.size() && acc == false;i++) {
            /*找到匹配的zhuangtai*/
            if (trans_func[i][0] == old_stage) {
                for (int j = 0;j < N;j++) {
                    if (((old_symbol[j] != trans_func[i][1][j]) && trans_func[i][1][j] != '*') || (trans_func[i][1][j] == '*' && old_symbol[j] == '_')) {
                        break;
                    }
                    if (j == N - 1) {
                        /*找到状态以及旧符号匹配的转移函数*/
                        halt = false;

                        new_stage = trans_func[i][4];
                        for (int k = 0;k < N;k++) {
                            if (trans_func[i][2][k] == '*') {
                                new_symbol[k] = old_symbol[k];
                            }
                            else {
                                new_symbol[k] = trans_func[i][2][k];
                            }
                            direction[k] = trans_func[i][3][k];
                        }
                    }
                }
            }
            if (halt == false)break;
        }

        int left = 0;
        int right = tape[0].length() - 1;
        for (;left < tape[0].length();left++) {
            if (tape[0][left] != '_')break;
        }
        for (;right >= 0;right--) {
            if (tape[0][right] != '_')break;
        }
        cout << "Step   " << (N >= 10 ? " " : "") << ": " << step << endl;
        cout << "State  " << (N >= 10 ? " " : "") << ": " << old_stage << endl;
        cout << "Acc    " << (N >= 10 ? " " : "") << ": ";
        if(acc == false)
            cout<< "No" << endl;
        else
            cout << "Yes" << endl;
        for (int i = 0;i < N;i++) {
            cout << "Index" << i;
            if (N < 10) cout << " : ";
            else {
                if (i < 10)cout << "  : ";
                else cout << " : ";
            }
            int left = 0;
            int right = tape[i].length() - 1;
            for (;left < tape[i].length();left++) {
                if (tape[i][left] != '_')break;
            }
            for (;right >= 0;right--) {
                if (tape[i][right] != '_')break;
            }
            if (left > right) {
                cout << (pointer[i]<=head[i]?(head[i]- pointer[i]): -(head[i] - pointer[i])) << endl;
            }
            else {
                /*只有一个字符*/
                if (tape[i].length() == 1) {
                    cout << 0 << endl;
                }
                else {
                    if (left <= pointer[i] && pointer[i] <= right) {
                        for (int j = left;j <= right;j++) {
                            if (j <= head[i] && j != right)cout << (head[i] - j) << ' ';
                            else if (j <= head[i] && j == right)cout << (head[i] - j);
                            else if (j > head[i] && j != right)cout << (j - head[i]) << ' ';
                            else cout << (j - head[i]);
                        }
                        cout << endl;
                    }
                    else if (pointer[i] < left) {
                        for (int j = pointer[i];j <= right;j++) {
                            if (j <= head[i] && j != right)cout << (head[i] - j) << ' ';
                            else if (j <= head[i] && j == right)cout << (head[i] - j);
                            else if (j > head[i] && j != right)cout << (j - head[i]) << ' ';
                            else cout << (j - head[i]);
                        }
                        cout << endl;
                    }
                    else {
                        for (int j = left;j <= pointer[i];j++) {
                            if (j <= head[i] && j != pointer[i])cout << (head[i] - j) << ' ';
                            else if (j <= head[i] && j == pointer[i])cout << (head[i] - j);
                            else if (j > head[i] && j != pointer[i])cout << (j - head[i]) << ' ';
                            else cout << (j - head[i]);
                        }
                        cout << endl;
                    }
                }
            }

            //cout <<left<<' '<<right<<' ' << pointer[i] << ' ' << head[i] << endl;

            cout << "Tape" << i;
            if (N < 10) cout << "  : ";
            else {
                if (i < 10)cout << "   : ";
                else cout << "  : ";
            }
            if (left > right) {
                cout << '_' << endl;
            }
            else {
                /*只有一个字符*/
                if (tape[i].length() == 1) {
                    cout << tape[i] << endl;
                }
                else {
                    if (left <= pointer[i] && pointer[i] <= right) {
                        for (int j = left;j <= right;j++) {
                            if (j <= head[i] && j != right)cout << tape[i][j] << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == right)cout << tape[i][j];
                            else if (j > head[i] && j != right)cout << tape[i][j] << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << tape[i][j];
                        }
                        cout << endl;
                    }
                    else if (pointer[i] < left) {
                        for (int j = pointer[i];j <= right;j++) {
                            if (j <= head[i] && j != right)cout << tape[i][j] << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == right)cout << tape[i][j];
                            else if (j > head[i] && j != right)cout << tape[i][j] << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << tape[i][j];
                        }
                        cout << endl;
                    }
                    else {
                        for (int j = left;j <= pointer[i];j++) {
                            if (j <= head[i] && j != pointer[i])cout << tape[i][j] << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == pointer[i])cout << tape[i][j];
                            else if (j > head[i] && j != pointer[i])cout << tape[i][j] << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << tape[i][j];
                        }
                        cout << endl;
                    }
                }
            }

            cout << "Head" << i;
            if (N < 10) cout << "  : ";
            else {
                if (i < 10)cout << "   : ";
                else cout << "  : ";
            }
            if (left > right) {
                cout << '^' << endl;
            }
            else {
                if (tape[i].length() == 1) {
                    cout << '^' << endl;
                }
                else {
                    if (left <= pointer[i] && pointer[i] <= right) {
                        for (int j = left;j <= pointer[i];j++) {
                            if (j <= head[i] && j != pointer[i])cout << ' ' << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == pointer[i])cout << '^';
                            else if (j > head[i] && j != pointer[i])cout << ' ' << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << '^';
                        }
                        cout << endl;
                    }
                    else if (pointer[i] < left) {
                        /*for (int j = pointer[i];j <= right;j++) {
                            if (j <= head[i] && j != right)cout << ' ' << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == right)cout << '^';
                            else if (j > head[i] && j != right)cout << ' ' << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << '^';
                        }*/
                        cout << '^';
                        
                        cout << endl;
                    }
                    else {
                        for (int j = left;j <= pointer[i];j++) {
                            if (j <= head[i] && j != pointer[i])cout << ' ' << ((head[i] - j) >= 10 ? "  " : " ");
                            else if (j <= head[i] && j == pointer[i])cout << '^';
                            else if (j > head[i] && j != pointer[i])cout << ' ' << ((j - head[i]) >= 10 ? "  " : " ");
                            else cout << '^';
                        }
                        cout << endl;
                    }
                }
            }
        }
        cout << "---------------------------------------------" << endl;
        step++;
        //找不到转移函数后停机 并且未接受该字符串
        if (halt == true && acc == false) {
            cout << "UNACCEPTED" <<endl;
            cout << "Result: ";
            int i = 0;
            int j = tape[0].length() - 1;
            for (;i < tape[0].length();i++) {
                if (tape[0][i] != '_')break;
            }
            for (;j >= 0;j--) {
                if (tape[0][j] != '_')break;
            }
            for (int k = i;k <= j;k++) {
                cout << tape[0][k];
            }cout << endl;
            cout << "==================== END ====================" << endl;
            return 0;
        }
 
        //更改状态
        old_stage = new_stage;
        for (int i = 0;i < N;i++) {
            tape[i][pointer[i]] = new_symbol[i];
            if (direction[i] == 'l') {
                if (pointer[i] > 0) {
                    pointer[i] -= 1;
                }
                else {
                    tape[i] = "_" + tape[i];
                    head[i]++;
                }
            }
            else if (direction[i] == 'r') {
                if (pointer[i] == tape[i].length() - 1) {
                    tape[i] = tape[i] + "_";
                }
                pointer[i] += 1;
            }
            else;
        }
        for (int i = 0;i < N;i++) {
            old_symbol[i] = tape[i][pointer[i]];
        }
        
        
    }

    cout << "ACCEPTED" << endl;
    cout << "Result: ";
    int i = 0;
    int j = tape[0].length() - 1;
    for (;i < tape[0].length();i++) {
        if (tape[0][i] != '_')break;
    }
    for (;j >= 0;j--) {
        if (tape[0][j] != '_')break;
    }
    for (int k = i;k <= j;k++) {
        cout << tape[0][k];
    }
    cout << endl;
    cout << "==================== END ====================" << endl;
    return 0;
}


//int main() {
//    string filename = "case1.tm";
//    read_file(filename);
//    test();
//    verbose = true;
//    string input = "aaaaaaabbb";
//    if (get_tape(input) == 0) {
//        verbose_simulate(input);
//    }
//    return 0;
//}