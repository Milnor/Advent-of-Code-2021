#include <Submarine.h>

using namespace std;

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
        cout << "[!] = " << line << "\n";
    }

    return parsed;
}

int main() {


#if 0
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
#endif
#if 0
    cout << "Day 1 Challenge 1=" << count << "\n";

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

    cout << "+++Day 8+++\n";
    vector<display> displays = parseDisplays(get_challenge_data("./data/08sample.txt"));

    return 0;
}

