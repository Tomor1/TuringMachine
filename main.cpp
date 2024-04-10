#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include"simulator.h"
extern bool verbose;
 using namespace std;
 int main(int argc, char* argv[]){

     if(argc == 1){
         return 1;
     }
     else if (argc == 2) {
         string temp = argv[1];
         if (temp == "-h" || temp == "--help") {
             cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
             return 0;
         }
         else {
             cerr << "syntax error" << endl;
             exit(1);
         }
     }
     else if (argc == 3) {
         string temp = argv[1];
         if (temp == "-v" || temp == "-verbose") {
             string temp1 = argv[2];
             if (temp1 == "-h" || temp1 == "--help") {
                 cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
                 return 0;
             }
             cerr << "syntax error" << endl;
             exit(1);
         }
         else if(temp == "-h" || temp == "--help") {
             cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
             return 0;
         }
         else {
             string filename = argv[1];
             filename=filename;
             string input = argv[2];
             read_file(filename);
             if (get_tape(input) == 0) {
                simulate(input);
             }
             return 0;
         }
     }
     else if (argc == 4) {
         string temp = argv[1];
         if (temp == "-v" || temp == "--verbose") {
             string temp1 = argv[2];
             if (temp1 == "-h" || temp1 == "--help") {
                 cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
                 return 0;
             }
             else {
                 verbose = true;
                 string filename = argv[2];
                 filename=filename;
                 string input = argv[3];
                 read_file(filename);
                 if (get_tape(input) == 0) {
                     verbose_simulate(input);
                 }
                 return 0;
             }
         }
         else if (temp == "-h" || temp == "--help") {
             cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
             return 0;
         }
         else {
             cerr << "syntax error" << endl;
             exit(1);
         }
     }
     else if (argc == 5) {
         string temp = argv[2];
         if (temp == "-h" || temp == "--help") {
             cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
             return 0;
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
 }
