#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<set>
#include<vector>
#include<fstream>
#include"Turing.h"
using namespace std;
static string* tape;
set<string>Q;
set<char>S;//input symbol
set<char>G;//tape symbol
vector<vector<string>> trans_func;
string q0 = "";
char B = '*';
set<string>F;
int N = 0;

int get_Q(string line) {
    char* temp = new char[line.length() + 1];
    strcpy(temp, line.c_str());
    char Delimiter[] = ",";
    char* temp1 = NULL;
    temp1 = strtok(temp, Delimiter);int j = 1;
    while (temp1 != NULL) {
        string state = temp1;
        for (int i = 0;i < state.length();i++) {
            //cout<<j<<endl;j++;
            if ((state[i] < '0' || state[i]>'9') && (state[i] < 'a' || state[i]>'z') && (state[i] < 'A' || state[i]>'Z') && state[i] != '_') {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }
        //cout<<state<<endl;
        Q.insert(state);
        temp1 = strtok(NULL, Delimiter);
    }
    //cout<<123<<endl;
    return 0;
}

int get_S(string line) {
    char* temp = new char[line.length() + 1];
    strcpy(temp, line.c_str());
    char Delimiter[] = ",";
    char* temp1 = NULL;
    temp1 = strtok(temp, Delimiter);
    while (temp1 != NULL) {
        string symbol = temp1;
        if (symbol[0] == ' ' || symbol[0] == ',' || symbol[0] == ';' || symbol[0] == '{' || symbol[0] == '}' || symbol[0] == '*' || symbol[0] == '_') {
            cerr << "syntax error" << endl;
            exit(1);
        }
        char s = symbol[0];
        S.insert(s);
        temp1 = strtok(NULL, Delimiter);
    }
    return 0;
}

int get_G(string line) {
    char* temp = new char[line.length() + 1];
    strcpy(temp, line.c_str());
    char Delimiter[] = ",";
    char* temp1 = NULL;
    temp1 = strtok(temp, Delimiter);
    while (temp1 != NULL) {
        string symbol = temp1;
        if (symbol[0] == ' ' || symbol[0] == ',' || symbol[0] == ';' || symbol[0] == '{' || symbol[0] == '}' || symbol[0] == '*') {
            cerr << "syntax error" << endl;
            exit(1);
        }
        char s = symbol[0];
        G.insert(s);
        temp1 = strtok(NULL, Delimiter);
    }
    return 0;
}

int get_F(string line) {
    // bool tag=false;
    // for(int i=0;i<line.length();i++){
    //     if(line[i]=','){
    //         tag=true;
    //         break;
    // }
    // }
    char* temp = new char[line.length() + 1];
    strcpy(temp, line.c_str());
    char Delimiter[] = ",";
    char* temp1 = NULL;
    temp1 = strtok(temp, Delimiter);
    while (temp1 != NULL) {
        string state = temp1;
        if (Q.find(state) != Q.end()) {}
        else {
            cerr << "syntax error" << endl;
            exit(1);
        }
        // for(int i=0;i<state.length();i++){
        //     if((state[i]<'0'||state[i]>'9')&&(state[i]<'a'||state[i]>'z')&&(state[i]<'A'||state[i]>'Z')&&state[i]!='_'){
        //     cerr<<"syntax error"<<endl;
        //     exit(1);
        //     }
        // }
        F.insert(state);
        temp1 = strtok(NULL, Delimiter);
    }
    return 0;
}

int get_q0BN(string line, int tag) {
    if (tag == 0) {
        if (Q.find(line) != Q.end()) {
            q0 = line;
            return 0;
        }
        else {
            cerr << "syntax error" << endl;
            exit(1);
        }
    }
    else if (tag == 1) {
        if (line.length() != 1 || line[0] != '_') {
            cerr << "syntax error" << endl;
            exit(1);
        }
        else {
            B = '_';
            return 0;
        }
    }
    else {
        if (line.length() == 0) {
            cerr << "syntax error" << endl;
            exit(1);
        }
        for (int i = 0;i < line.length();i++) {
            if (line[i] < '0' || line[i]>'9') {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }
        N = stoi(line);
        return 0;
    }
}

void trimString(string& str)
{
    int s = str.find_first_not_of(" ");
    int e = str.find_last_not_of(" ");
    str = str.substr(s, e - s + 1);
    return;
}

int parse(string line) {
    if (line.length() == 0)return 0;//忽略空行
    trimString(line);//去除行首行尾空格
    for (int i = 0;i < line.length();i++) {
        if (line[i] == ';') {
            line = line.substr(0, i);
            break;
        }
    }//去除注释
    if (line.length() == 0)return 0;//忽略行首注释

    if (line[0] == '#') {
        switch (line[1])
        {
        case 'Q': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '{') {
                    j = ++i;
                    break;
                }
            }
            line = line.substr(j, line.length() - 1 - j);//只保留{}中的内容
            if (get_Q(line) != 0) {
                exit(-1);
            }
        }
                break;
        case 'S': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '{') {
                    j = ++i;
                    break;
                }
            }
            line = line.substr(j, line.length() - 1 - j);//只保留{}中的内容
            if (get_S(line) != 0) {
                exit(-1);
            }
        }
                break;
        case 'G': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '{') {
                    j = ++i;
                    break;
                }
            }
            line = line.substr(j, line.length() - 1 - j);//只保留{}中的内容
            if (get_G(line) != 0) {
                exit(-1);
            }
        }
                break;
        case 'F': {
            //cout<<"into get_F"<<endl;
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '{') {
                    j = ++i;
                    break;
                }
            }
            line = line.substr(j, line.length() - 1 - j);//只保留{}中的内容
            if (get_F(line) != 0) {
                exit(-1);
            }
        }
                break;
        case 'q': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '=') {
                    j = i + 2;
                    break;
                }
            }
            line = line.substr(j, line.length() - j);//只保留{}中的内容
            if (get_q0BN(line, 0) != 0) {
                exit(-1);
            }
        }
                break;
        case 'B': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '=') {
                    j = i + 2;
                    break;
                }
            }
            line = line.substr(j, line.length() - j);//只保留{}中的内容
            if (get_q0BN(line, 1) != 0) {
                exit(-1);
            }
        }
                break;
        case 'N': {
            int j = 0;
            for (int i = 0;i < line.length();i++) {
                if (line[i] == '=') {
                    j = i + 2;
                    break;
                }
            }
            line = line.substr(j, line.length() - j);//只保留{}中的内容
            if (get_q0BN(line, 2) != 0) {
                exit(-1);
            }
        }
                break;
        default:
            cerr << "syntax error" << endl;
            exit(1);
            break;
        }
        return 0;
    }

    vector<string>temp;
    char* temp1 = new char[line.length() + 1];
    strcpy(temp1, line.c_str());
    char Delimiter[] = " ";
    char* temp2 = NULL;
    temp2 = strtok(temp1, Delimiter);int nums = 1;
    while (temp2 != NULL) {
        string input = temp2;
        //int *tag=new int[N];
        if (nums == 1) {
            //set<int>::iterator iter;
            if (Q.find(input) != Q.end()) {
                temp.push_back(input);
            }
            else {
                //cout<<1<<endl;   
                cerr << "syntax error" << endl;
                exit(1);
            }
        }
        else if (nums == 2) {
            if (input.length() != N) {
                //cout<<input<<' '<<N<<endl;
                cerr << "syntax error" << endl;
                exit(1);
            }
            for (int i = 0;i < input.length();i++) {
                if (G.find(input[i]) == G.end() && input[i] != '*') {
                    //cout<<2<<endl; 
                    cerr << "syntax error" << endl;
                    exit(1);
                }
                //if(input[i]=='*')tag[i]=1;
                //else tag[i]=0;
            }
            temp.push_back(input);
        }
        else if (nums == 3) {
            if (input.length() != N) {
                //cout<<3<<endl;
                cerr << "syntax error" << endl;
                exit(1);
            }
            for (int i = 0;i < input.length();i++) {
                if (G.find(input[i]) == G.end() && input[i] != '*') {
                    //cout<<3<<endl; 
                    cerr << "syntax error" << endl;
                    exit(1);
                }
                //if(input[i]=='*')tag[i]=1;
                //else tag[i]=0;
            }
            temp.push_back(input);
        }
        else if (nums == 4) {
            if (input.length() != N) {
                //cout<<4<<endl;
                cerr << "syntax error" << endl;
                exit(1);
            }
            for (int i = 0;i < input.length();i++) {
                if (input[i] != 'l' && input[i] != 'r' && input[i] != '*') {
                    //cout<<4<<endl; 
                    cerr << "syntax error" << endl;
                    exit(1);
                }
                //if(input[i]=='*')tag[i]=1;
                //else tag[i]=0;
            }
            temp.push_back(input);
        }
        else if (nums == 5) {
            //set<int>::iterator iter;
            if (Q.find(input) != Q.end()) {
                temp.push_back(input);
            }
            else {
                cerr << "syntax error" << endl;
                exit(1);
            }
        }
        else {
            cerr << "syntax error" << endl;
            exit(1);
        }
        temp2 = strtok(NULL, Delimiter);nums++;
    }
    if (temp.size() == 5) {
        trans_func.push_back(temp);
    }
    else {
        cerr << "syntax error" << endl;
        exit(1);
    }
    return 0;
}
int read_file(string filename) {
    ifstream fin;
    fin.open(filename);//创建一个fstream文件流对象
    if (!fin.is_open()) {
        cerr << "failed to open file" << endl;
        exit(1);
    }
    string line; //保存读入的每一行
    while (getline(fin, line))
    {
        if (parse(line) == 0) {
            //cout<<line<<endl;
        }
        else {
            cerr << "syntax error" << endl;
            exit(1);
        }
    }
    if (Q.size() == 0 || S.size() == 0 || G.size() == 0 || F.size() == 0 || q0 == "" || B == '*' || N == 0 ) {
        cerr << "syntax error" << endl;
        exit(1);
    }
    return  0;

}

void test() {
    cout << "Q:" << Q.size() << endl;
    for (string c : Q) {//遍历set，注意set会将元素自动排序，插入的顺序是1、3、2，遍历的顺序是1、2、3 
        cout << c << ' ';
    } cout << endl;
    cout << "S:" << S.size() << endl;
    for (char c : S) {//遍历set，注意set会将元素自动排序，插入的顺序是1、3、2，遍历的顺序是1、2、3 
        cout << c << ' ';
    } cout << endl;
    cout << "G:" << G.size() << endl;
    for (char c : G) {//遍历set，注意set会将元素自动排序，插入的顺序是1、3、2，遍历的顺序是1、2、3 
        cout << c << ' ';
    } cout << endl;
    cout << "F:" << F.size() << endl;
    for (string c : F) {//遍历set，注意set会将元素自动排序，插入的顺序是1、3、2，遍历的顺序是1、2、3 
        cout << c << ' ';
    } cout << endl;
    cout << q0 << ' ' << B << ' ' << N << endl;
    cout << "trans_func:" << endl;
    for (int i = 0;i < trans_func.size();i++) {
        for (int j = 0;j < trans_func[i].size();j++) {
            cout << trans_func[i][j] << ' ';
        }cout << endl;
    }
}

// int main(){
//    string filename="../palindrome_detector_2tapes.tm";
//    read_file(filename);
//    //test();
// }