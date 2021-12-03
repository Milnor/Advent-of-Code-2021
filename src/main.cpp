#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
class Submarine {
    public:
        int x;      // horizontal coordinate
        int y;      // depth coordinate
        int aim;
};
*/

/* Correct answers from Python version:
 *
 * D1P1 = 1482
 * D1P2 = 1518
 * D2P1 = 2199 * 786 = 1728414
 * D2P2 = 2199 * 802965 = 1765720035
 */

struct Submarine {
    int x = 0;
    int y = 0;
    int aim = 0;

    Submarine() {
        printf("We all live in a yellow submarine\n");
    }
};

int main() {

    fstream challenge;
    challenge.open("./data/01depth.txt", ios::in);
    int * depths;
    depths = new int [2000];
    int i = 0;
    int count = 0;
    string current_data;
    while(getline(challenge, current_data)) {
        //cout << current_data << "\n";
        depths[i] = stoi(current_data);
        i++;
    }
    for (i = 1; i < 2000; i++)
    {
        if (depths[i] > depths[i - 1])
        {
            count++;
        }
    }
    challenge.close();

    cout << "Day 1 Challenge 1=" << count << "\n";

    Submarine yellow{};   // obvious Beatles pun
    //yellow.x = 0;       // move to constructor (after I learn how)!
    //yellow.y = 0;
    //yellow.aim = 0;

    cout << "x=" << yellow.x << "\n";
    cout << "y=" << yellow.y << "\n";


    return 0;
}
