#include <fstream>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

char curr_val[100000];
ifstream f("conjectura.in");
ofstream g("conjectura.out");

bool Is_Palind() { //of curr_Val
    for (int it = 0, end_it = strlen(curr_val)-1; it <= end_it; ++it, --end_it)
     if (curr_val[it] != curr_val[end_it])
        return false;
    return true;
}

int main() {
    int steps=0;
    f >> curr_val;
    while (!Is_Palind()) {
       ++steps;
       for (int it = strlen(curr_val) - 1, new_pos = it + 1; it >= 0; --it, ++new_pos)
          curr_val[new_pos] = curr_val[it];
    }
    g << strlen(curr_val) << " " << steps;

}
