#include "AoC2021/Submarine.hpp"

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

/* Linux terminal color codes */
#define RESET       "\033[0m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDRED     "\033[1m\033[31m"
#define CYAN        "\033[36m"
#define MAGENTA     "\033[35m"
#define GREEN       "\033[32m"

/* Working assumption: all valid answers are positive integers */
const int INVALID = -1;

// TODO(milnor): command line argument to disable
bool verbose = true;    

// Generic help functions
vector<string> get_challenge_data(string filepath) {
    vector <string> daily_input;
    if (verbose) {
        cout << GREEN << "\t[!] reading " << filepath << "...\n" << RESET;
    }
    fstream challenge;
    challenge.open(filepath, ios::in);
    string current_line;
    while(getline(challenge, current_line)) {
        daily_input.push_back(current_line);
    }
    challenge.close();
    return daily_input;
}


vector<int> strVecToIntVec(vector<string> input) {
    vector<int> output = {};
    for (auto line : input) {
        cout << "line = " << line << "\n";
        string number = "";
        for (auto digit : line) {
            //string number = "";
            cout << "[ ] digit = " << digit << "\n";
            if (isdigit(digit)) {
                number.push_back(digit);

                cout << "[?] " << number << "\n";
            } else {
                if (number.size() > 0) {
                    output.push_back(stoi(number, 0, 10));
                    cout << "[!] added " << number << "\n";
                    number.clear();
                }
            }
        }
        
    if (number.size() > 0) {
        output.push_back(stoi(number, 0, 10));
    }
    }
    return output;
}


// TODO(milnor): relocate stuff for specific challenges
int fuel_economy(vector<int> crabs, bool expensive) {
    int horizontal_max = 0, fuel_cost = 0, best_position = 0;
    
    for (auto crab : crabs) {
        if (crab > horizontal_max) {
            horizontal_max = crab;
        }
    }

    cout << "horizontal max = " << horizontal_max << "\n";

    fuel_cost = INT32_MAX;
    for (int i = 0; i <= horizontal_max; i++) {
        cout << "[!] trying pos i = " << i << "\n";
        // try every possible horizontal position
        int test_cost = 0;
        for (auto crab : crabs) {
            int hi, low;
            if (crab > i) {
                hi = crab;
                low = i;
            } else {
                hi = i;
                low = crab;
            }
            int distance = (hi - low);
            test_cost += distance;
            if (expensive && (distance > 1)) {
                // i.e. Day 7 Part 2 instead of Part 1
                for (int j = (distance - 1); j > 0; j--) {
                    test_cost += j;
                }
            }
        }
        if (test_cost < fuel_cost) {
            cout << "[!] found better position at " << i << "\n";
            fuel_cost = test_cost;
        }

    }

    return fuel_cost;
}

struct display {

    string in01, in02, in03, in04, in05, in06, in07, in08, in09, in10;
    string out01, out02, out03, out04;

};

vector<display> parseDisplays(vector<string> data) {
    vector<display> parsed = {};
    for (auto line : data) {
        display next_set;
        string intermediate[15];
        int i = 0;
        cout << "[!] = " << line << "\n";
        string delimiter = " ";
        // adapted from: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        size_t pos = 0;
        string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            cout << token << endl;
            line.erase(0, pos + delimiter.length());
            intermediate[i] = token;
            i++;
        }
        intermediate[14] = line;
        next_set.in01 = intermediate[0];
        next_set.in02 = intermediate[1];
        next_set.in03 = intermediate[2];
        next_set.in04 = intermediate[3];
        next_set.in05 = intermediate[4];
        next_set.in06 = intermediate[5];
        next_set.in07 = intermediate[6];
        next_set.in08 = intermediate[7];
        next_set.in09 = intermediate[8];
        next_set.in10 = intermediate[9];
        next_set.out01 = intermediate[11];
        next_set.out02 = intermediate[12];
        next_set.out03 = intermediate[13];
        next_set.out04 = intermediate[14];
        cout << "current = " << next_set.in01 << "," << next_set.in02 << "\n";
        cout << "dumping the " << intermediate[10] << "\n";
        parsed.push_back(next_set);
    }

    return parsed;
}

// 2, 4, 3, 7 are the output string lengths of 1, 4, 7, 8

int countEasyDigits(vector<display> displays) {
    int count = 0;
    for (auto d : displays) {
        int aa = d.out01.length();
        int bb = d.out02.length();
        int cc = d.out03.length();
        int dd = d.out04.length();
        if (aa == 2 || aa == 4 || aa == 3 || aa == 7) {
            count++;
        }
        if (bb == 2 || bb == 4 || bb == 3 || bb == 7) {
            count++;
        }
        if (cc == 2 || cc == 4 || cc == 3 || cc == 7) {
            count++;
        }
        if (dd == 2 || dd == 4 || dd == 3 || dd == 7) {
            count++;
        }
    }
    return count;
}

void printOutputs(vector<display> displays) {
    for (auto d : displays) {
        cout << d.out01 << " " << d.out02 << " " << d.out03 << " " << d.out04 << "\n"; 
    }
}

struct result {
    long long part1;
    long long part2;
};

int do_challenge(string sample_data, string actual_data, string challenge, result (solver)(string path)) {
    // TODO(milnor): insert Day #
    cout << BOLDYELLOW << "--- Day ##" << ": " << challenge << " ---\n" << RESET;  
    int ret = 0;
    // TODO(milnor): handle errors
    result sample = solver(sample_data);
    cout << MAGENTA << "\t[+] Sample Data: Part 1=" << sample.part1 << ", Part 2=" << sample.part2 << "\n" 
        << RESET;
    
    result actual = solver(actual_data);
    cout << CYAN << "\t[+] Actual Data: Part 1=" << actual.part1 << ", Part 2=" << actual.part2 << "\n"
        << RESET;
    
    return ret;
}

result day01(string data) {

    result answer = { INVALID, INVALID };
   
    // Format data for analysis 
    vector<string> raw = get_challenge_data(data);
    vector<int> depths;
    for (auto line : raw) {
        depths.push_back(stoi(line));
    }

    // Calculate simple increases
    int increases = 0;
    int previous = depths[0];
    for (auto measurement : depths) {
        if (measurement > previous) {
            increases++;
        } 
        previous = measurement;
    }
    answer.part1 = increases;

    // Calculate sliding window increases
    vector<int> windows;
    for (int i = 0; i < depths.size() - 2; i++) {
        windows.push_back(depths[i] + depths[i + 1] + depths[i + 2]);    
    }
    increases = 0;
    previous = windows[0];
    for (auto window : windows) {
        if (window > previous) {
            increases++;
        }
        previous = window;
    }
    answer.part2 = increases;

    return answer;
}

result day02(string data) {
    result answer = { INVALID, INVALID };

    vector<string> directions = get_challenge_data(data);
    int x = 0;
    int y = 0;
    for (auto command : directions) {
        int index = command.size() - 1;
        string number = string(1, command[index]);
        int magnitude = stoi(number);
        switch (command[0]) {
            case 'f':
                // forward => increase horizontal
                x += magnitude;         
                break;
            case 'd':
                // down => increase depth (vertical)
                y += magnitude;
                break;
            case 'u':
                // up => decrease depth (vertical)
                y -= magnitude;
                break;
            default:
                cerr << BOLDRED << "\t[-] Unknown command: " << command << "\n" << RESET;
        }
    }

    answer.part1 = x * y;

    int aim = 0;    
    x = 0;
    y = 0;
    for (auto command : directions) {
        int index = command.size() - 1;
        string number = string(1, command[index]);
        int magnitude = stoi(number);
        switch (command[0]) {
            case 'f':
                // forward => increase horizontal
                x += magnitude; 
                y += (aim * magnitude);        
                break;
            case 'd':
                // down => increase aim
                aim += magnitude;
                break;
            case 'u':
                // up => decrease aim
                aim -= magnitude;
                break;
            default:
                cerr << BOLDRED << "\t[-] Unknown command: " << command << "\n" << RESET;
        }
    }

    answer.part2 = x * y;

    return answer;
}

result day03(string data) {
    result answer = { INVALID, INVALID };
#if 0
    vector<string> day03 = get_challenge_data("./data/03binary.txt");
    string gamma = calculate_gamma(day03);
    string epsilon = gamma_to_epsilon(gamma);
    int power = stoi(gamma, 0, 2) * stoi(epsilon, 0, 2);
    
    cout << "Day 3:\n" << "\tgamma = " << gamma << "\n\tepsilon = " << epsilon << "\n\tpower = " << power << "\n";

    int oxygen_gen = calculate_oxygen(day03);
    cout << "Did we get halfway before seg fault?\n";
    int co2_scrub = calculate_co2(day03);

    int life_support = oxygen_gen * co2_scrub;

    cout << "\toxygen = " << oxygen_gen << "\n\tCO2 = " << co2_scrub << "\n\tlife support = " << life_support << "\n"; 
#endif

    return answer;
}

int main() {

    int failed = 0;

    failed |= do_challenge("./data/01sample.txt", "./data/01depth.txt", "Sonar Sweep", day01);

    failed |= do_challenge("./data/02sample.txt", "./data/02movement.txt", "Dive!", day02);

    failed |= do_challenge("./data/03.sample.txt", "./data/03binary.txt", "Binary Diagnostic", day03);


#if 0
    vector<string> bingo = get_challenge_data("./data/04bingo.txt");
    cout << "line 1: " << bingo[0] << "\nline 2: " << bingo[1] << "\nline 3: " << bingo[2] << "\nline 4:" << bingo[3] << "\n";

    cout << "+++Day 6+++\n";
    Lanternfish spooky = Lanternfish(get_challenge_data("./data/06fish.txt"));
    //spooky.showState();
    spooky.fastForward(256);
    uint64_t result = spooky.getCount();
    cout << "After 256 days there are " << result << " fish.\n"; 

    cout << "+++Day 7+++\n";
    vector<int> crabs = strVecToIntVec(get_challenge_data("./data/07crabs.txt"));
    cout << "There are " << crabs.size() << " crabs.\n";

    int fuel_cost = fuel_economy(crabs, false);
    int fuel_cost2 = fuel_economy(crabs, true);
    cout << "[+] best fuel cost is " << fuel_cost << " (cheaper fuel)\n";
    cout << "[+] best fuel cost is " << fuel_cost2 << " (expensive fuel)\n";
#endif
#if 0
    cout << "+++Day 8+++\n";
    vector<display> displays = parseDisplays(get_challenge_data("./data/08displays.txt"));
    cout << "items in displays = " << displays.size() << "\n";
    cout << "displays[0].out04 = " << displays[0].out04 << "\n";

    cout << "displays[0].in01 = " << displays[0].in01 << "\n";
    int part1_result = countEasyDigits(displays);
    cout << "==============\n";
    printOutputs(displays);
    cout << "Part 1 Sum = " << part1_result << "\n";
#endif

    return failed;
}

