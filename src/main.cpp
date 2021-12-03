#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Data Sets
 *
 * https://adventofcode.com/2021/day/1/input
 * https://adventofcode.com/2021/day/2/input
 * https://adventofcode.com/2021/day/3/input
 *
 */

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

const int bit_count = 12;

struct Submarine {
    int x = 0;
    int y = 0;
    int aim = 0;

    Submarine() {
        printf("We all live in a yellow submarine\n");
    }
};

string calculate_gamma(vector<string> raw_bits)
{
    int zeroes[bit_count] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int ones[bit_count] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    cout << "vector size=" << raw_bits.size() << "\n";

    for (int i = 0; i < raw_bits.size(); i++) {

        for (int j = 0; j < bit_count; j++) {
            
            if (raw_bits[i][j] == '0') {
                zeroes[j]++;
            } else if (raw_bits[i][j] == '1') {
                ones[j]++;
            } else if (raw_bits[i][j] == '\n') {
                // pass
            } else {
                cout << "[!] did not expect " << raw_bits[i][j] << "!\n";
            }

        }

    }

    for (int i = 0; i < bit_count; i++) {
        cout << "0s= " << zeroes[i] << ", 1s= " << ones[i] << "\n";
    }

    return "hi";
}

vector<string> get_challenge_data(string filepath) {
    vector <string> daily_input;
    cout << "reading " << filepath << "...\n";
    fstream challenge;
    challenge.open(filepath, ios::in);
    string current_line;
    while(getline(challenge, current_line)) {
        daily_input.push_back(current_line);
    }
    challenge.close();
    return daily_input;
}

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

    vector<string> day03 = get_challenge_data("./data/03binary.txt");
    calculate_gamma(day03);

    Submarine yellow{};   // obvious Beatles pun
    //yellow.x = 0;       // move to constructor (after I learn how)!
    //yellow.y = 0;
    //yellow.aim = 0;

    cout << "x=" << yellow.x << "\n";
    cout << "y=" << yellow.y << "\n";


    return 0;
}
