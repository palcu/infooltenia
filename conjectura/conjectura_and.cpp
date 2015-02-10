#include <fstream>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

char input_string[100000];
int curr_val[100000], aux_val[100000];
ifstream f("conjectura.in");
ofstream g("conjectura.out");

bool Is_Palind() { //of curr_Val
    for (int it = 1, end_it = curr_val[0]; it <= end_it; ++it, --end_it)
     if (curr_val[it] != curr_val[end_it])
        return false;
    return true;
}

void add_aux() {   //of curr_val and aux_val
      int i, t = 0;
      for (i=1; i <= curr_val[0] || i <= aux_val[0] || t; i++, t/=10)
              curr_val[i] = (t += curr_val[i] + aux_val[i]) % 10;
      curr_val[0] = i - 1;
}

int main() {
    int steps=0, T;
    bool ok;

    f >> T;
    while (T--) {
        f >> input_string;
        steps = 0;
        memset(curr_val, 0, sizeof(curr_val));
        memset(aux_val, 0, sizeof(aux_val));
        for (int string_it = strlen(input_string) - 1; string_it >= 0; --string_it)
            curr_val[++curr_val[0]] = input_string[string_it] - '0';

        while (!(ok=Is_Palind()) && steps <1000) {
           ++steps;
           aux_val[0] = 0;
           for (int it = curr_val[0]; it > 0; --it)
              aux_val[++aux_val[0]] = curr_val[it];
            add_aux();
        }
        if (ok)
            g << steps << "\n";
        else
            g << "LYCHREL\n";
    }
    return 0;
}
