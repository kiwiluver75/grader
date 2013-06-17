/*
PROG: easyprob
LANG: C++
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
    int N;
    scanf( "%d", &N);
    int total = 0, x;
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &x);
        total += x;
    }
    printf("%d\n", total);

    return 0;
}
