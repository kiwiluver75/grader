/*
PROG: easyprob
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("easyprob.in");
ofstream fout ("easyprob.out");

int main()
{
    int N;
    fin >> N;

    int total = 0, x;
    for(int i = 0; i < N; i++)
    {
   	fin >> x; 
        total += x;
    }
    fout << total  << endl;

    return 0;
}
