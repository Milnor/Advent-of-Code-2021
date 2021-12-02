//#define _XOPEN_SOURCE 500

#include <iostream>
//#include <cwchar>
//#include <stdio.h>
//#include <wchar.h>
using namespace std;

class Submarine {
    public:
        int x;      // horizontal coordinate
        int y;      // depth coordinate
        int aim;
};

int main() {

    Submarine yellow;   // obvious Beatles pun
    yellow.x = 0;       // move to constructor (after I learn how)!
    yellow.y = 0;
    yellow.aim = 0;

    cout << "x=" << yellow.x << "\n";
    cout << "y=" << yellow.y << "\n";


    return 0;
}
