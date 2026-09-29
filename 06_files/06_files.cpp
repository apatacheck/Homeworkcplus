#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");

    string s;
    while (getline(fin, s)) {
        int first = s.find(',');   
        int last = s.rfind(',');   

        if (first != last && first != -1) {
            fout << s.substr(first + 1, last - first - 1) << endl;
        }
        else {
            fout << endl;
        }
    }

    fin.close();
    fout.close();
    return 0;
}