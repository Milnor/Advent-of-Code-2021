#include "AoC2021/Submarine.hpp"
#include "../include/common.hpp"
#include "../include/challenges.hpp"

using namespace std;

int daynum = 1;

/* Working assumption: all valid answers are positive integers */
const int INVALID = -1;

// TODO(milnor): command line argument to disable
bool verbose = true;    

int do_challenge(string sample_data, string actual_data, string challenge, result (solver)(string path)) {

    cout << BOLDYELLOW << "--- Day " << daynum << ": " << challenge << " ---\n" << RESET;  
    int ret = 0;
    // TODO(milnor): handle errors
    result sample = solver(sample_data);
    cout << MAGENTA << "\t[+] Sample Data: Part 1=" << sample.part1 << ", Part 2=" << sample.part2 << "\n" 
        << RESET;
    
    result actual = solver(actual_data);
    cout << CYAN << "\t[+] Actual Data: Part 1=" << actual.part1 << ", Part 2=" << actual.part2 << "\n"
        << RESET;
    
    daynum++;

    return ret;
}

int main() {

    int failed = 0;

    failed |= do_challenge("./data/01sample.txt", "./data/01depth.txt", "Sonar Sweep", &day01);
    failed |= do_challenge("./data/02sample.txt", "./data/02movement.txt", "Dive!", day02);
    failed |= do_challenge("./data/03.sample.txt", "./data/03binary.txt", "Binary Diagnostic", day03);

    return failed;
}

