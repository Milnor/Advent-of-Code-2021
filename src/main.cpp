#include <cstdio>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

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

    string gamma = "";

    for (int i = 0; i < bit_count; i++) {
        if (zeroes[i] > ones[i]) {
            gamma.append("0");
        } else {
            gamma.append("1");
        }
        //cout << "0s= " << zeroes[i] << ", 1s= " << ones[i] << "\n";
    }

    return gamma;
}

string gamma_to_epsilon(string gamma) {
    string epsilon = "";
    for (int i = 0; i < bit_count; i++) {
        if (gamma[i] == '1') {
            epsilon.append("0");
        } else {
            epsilon.append("1");
        }
    }  
    return epsilon;
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

int minority_is_zero(vector<string> data, int pos)
{
    int zeroes = 0;
    int ones = 0;
    int ret = 1;

    for (string s: data) {
        if (s[pos] == '0') {
            zeroes++;
        } else if (s[pos] == '1') {
            ones++;
        }
    }

    if (ones < zeroes) 
    {
        ret = 0;
    }

    return ret;
}

int majority_is_one(vector<string> data, int pos)
{
    int zeroes = 0;
    int ones = 0;
    int ret = 1;

    for(string s : data) {
        if (s[pos] == '0') {
            zeroes++;
        } else if (s[pos] == '1') {
            ones++;
        }
    }

    if (ones < zeroes)
    {
        // tie goes to 1's
        ret = 0;
    }
    
    return ret;
    
}

vector<string> keep_matches(vector<string> data, int bit_pos, int val) {
    vector<string> subvector;
    char match;
    if (val == 0) {
        match = '0';
    } else {
        match = '1';
    }
    for (string s: data) {
        if (s[bit_pos] == match) {
            subvector.push_back(s);
        } 
    }
    return subvector;
}

int calculate_oxygen(vector<string> data) {
    // majority, 1 for tie-breaker
    vector<string> subvector(data);
    int bit_pos = 0;
    do {
        if (majority_is_one(subvector, bit_pos)) {
            // strip appropriate values
            subvector = keep_matches(subvector, bit_pos, 1);
        } else {
            // strip the others
            subvector = keep_matches(subvector, bit_pos, 0);
        }
        bit_pos++;
    } while (subvector.size() > 1);

    return stoi(subvector[0], 0, 2);
}

int calculate_co2(vector<string> data) {
    // minority, 0 for tie-breaker
    vector<string> subvector(data);
    int bit_pos = 0;
    do {
        if (minority_is_zero(subvector, bit_pos)) {
            subvector = keep_matches(subvector, bit_pos, 0);
        } else {
            subvector = keep_matches(subvector, bit_pos, 1);
        }
        bit_pos++;
    } while (subvector.size() > 1);

    return stoi(subvector[0], 0, 2);
}

struct game_board {
    bool has_won;
    int board[5][5];
    bool state[5][5];
};

class VentMap {
    public:
        VentMap(int x, int y) {
            x_max = x - 1;
            y_max = y - 1;
            //vents = new int[x][y]();
            //vents = {};
            for (int i = 0; i <= x_max; i++) {
                for (int j = 0; j <= y_max; j++) {
                    vents[i][j] = 0;
                }
            }
            cout << "[+] Created VentMap.\n";
        }        
        int drawVents(vector<string> data, bool complex);        
        void printVents(void);
        int dangersCount(void);
    private:
        int x_max;
        int y_max;
        int vents[1000][1000];
        int incrementCoords(int x1, int y1, int x2, int y2); 
        int incrementDiagonals(int x1, int y1, int x2, int y2); 
};

// Member functions of VentMap
int VentMap::dangersCount(void) {
    int dangers = 0;
    for (int i = 0; i <= x_max; i++) {
        for (int j = 0; j <= y_max; j++) {
            if (vents[i][j] >= 2) {
                dangers++;
            }
        }
    }
    return dangers;
}

// TODO: fix wonky rotation
void VentMap::printVents(void) {
    for (int x = 0; x <= x_max; x++) {
        for (int y = 0; y <= y_max; y++) {
            cout << vents[x][y] << " ";
        }
        cout << "\n";
    }
}

int VentMap::incrementDiagonals(int x1, int y1, int x2, int y2) {
    // only does 45 degree diagonals
    //int low_x, low_y, hi_x, hi_y, length;
    //int length = 0;
    bool x_growing = true;
    bool y_growing = true;

    if (x2 < x1) {
        x_growing = false;
    }

    if (y2 < y1) {
        y_growing = false;
    }

    int x = x1;
    int y = y1;
    int length;
    if (x_growing) {
        length = x2 - x1;
    } else {
        length = x1 - x2;
    }

    for (int i = 0; i <= length; i++) {
        vents[x][y]++;
        if (x_growing) {
            x++;
        } else {
            x--;
        }
        if (y_growing) {
            y++;
        } else {
            y--;
        }

    }


#if 0
    if (x_growing) {
        // x is increasing
        for (int x = x1; x < x2; x++) {
            if (y_growing) {
                // and y is increasing
                for (int y = y1; y < y2; y++) {
                    vents[x][y]++;
                }
            } else {
                // and y is decreasing
                for (int y = y1; y > y2; y--) {
                    vents[x][y]++;
                }
            }
        }
    } else {
        // x is decreasing
        for (int x = x1; x > x2; x--) {
            if (y_growing) {
                // and y is increasing

                for (int y = y1; y < y2; y++) {
                    vents[x][y]++;
                }
            } else {
                // and y is decreasing

                for (int y = y1; y > y2; y--) {
                    vents[x][y]++;
                }
            }
        }
    }
#endif

#if 0
    if (x1 < x2) {
        low_x = x1;
        hi_x = x2;
    } else {
        low_x = x2;
        hi_x = x1;
    }
    if (y1 < y2) {
        low_y = y1;
        hi_y = y2;
    } else {
        low_y = y2;
        hi_y = y1;
    }
    
    length = hi_x - low_x;

    for (int i = 0; i < length; i++) {
        vents[low_x+i][low_y+i]++;
    }
#endif

    return 0;
}

int VentMap::incrementCoords(int x1, int y1, int x2, int y2) {

    if (x1 == x2) {
        // plot vertical line
        int lo_y, hi_y;
        if (y1 < y2) {
            lo_y = y1;
            hi_y = y2;
        } else {
            lo_y = y2;
            hi_y = y1;
        }
        for (int curr_y = lo_y; curr_y <= hi_y; curr_y++) {
            vents[x1][curr_y]++;
        } 
    } else if (y1 == y2) {
        // plot horizontal line
        int lo_x, hi_x;
        if (x1 < x2) {
            lo_x = x1;
            hi_x = x2;
        } else {
            lo_x = x2;
            hi_x = x1;
        }
        for (int curr_x = lo_x; curr_x <= hi_x; curr_x++) {
            vents[curr_x][y1]++;
        }

    }

    return 0;
}

int VentMap::drawVents(vector<string> data, bool complex) {
    /* Will regex save me from all the off-by-one and
        nested loop errors I made on Day 4? */
    unsigned int x1, y1, x2, y2;
    for (auto line : data) {
        // x1
        regex findx1("^([0-9]+),");
        smatch mx1;
        regex_search(line, mx1, findx1);
        
        // y1
        regex findy1(",([0-9]+) ->");
        smatch my1;
        regex_search(line, my1, findy1);
        
        // x2
        regex findx2("-> ([0-9]+),");
        smatch mx2;
        regex_search(line, mx2, findx2);
        
        // y2
        regex findy2(",([0-9]+)$");
        smatch my2;
        regex_search(line, my2, findy2);

        //cout << "{" << mx1[1] << "," << my1[1] << "} {" << mx2[1] << "," << my2[1] << "}\n"; 

        // convert to integers
        x1 = stoi(mx1[1], 0, 10);
        y1 = stoi(my1[1], 0, 10);
        x2 = stoi(mx2[1], 0, 10);
        y2 = stoi(my2[1], 0, 10);

        // filter out any diagonal lines
        if ((x1 == x2) || (y1 == y2)) {
            incrementCoords(x1, y1, x2, y2);
        } else if (complex) {
            incrementDiagonals(x1, y1, x2, y2);
        }

    }

    return 0;
}

class Bingo {
    public:
        Bingo(vector<string> raw_data) {
            cout << "[+] Game created!\n";
            numbers = parseNumbers(raw_data[0]);
            for (auto num : numbers)
            {
                cout << "num = " << num << "\n";
            }
            //cout << "nums = " << numbers << "\n";
            vector<string> subvector = {raw_data.begin() + 1, raw_data.end()};
            players = parsePlayers(subvector);

        }
        void startGame(void);
        int getNumbers(void);
        int getPlayers(void);
    private:
        vector<int> numbers;
        vector<game_board> players;  
        vector<int> parseNumbers(string data);
        vector<int> parseBoards(vector<string> data);
        vector<game_board> parsePlayers(vector<string> data);     
        bool checkWin(game_board board);
        void printBoard(game_board);
        int finalScore(game_board board, int pick);
};

// Member functions of Bingo
int Bingo::getNumbers(void) {
    return numbers.size();
}

int Bingo::getPlayers(void) {
    return players.size();
}

int Bingo::finalScore(game_board board, int pick) {

    int sum = 0;    // unmarked
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (board.state[r][c] == false) {
                sum += board.board[r][c];
            }
        }
    }
    //cout << "\nunmarked sum = " << sum << "\npick = " << pick << "\n";

    return (sum * pick);
}

void Bingo::printBoard(game_board board) {
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++) {
            cout << "\t" << board.board[row][col];
        }
        cout << "\n";
    }
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++) {
            cout << "\t" << board.state[row][col];
        }
        cout << "\n";
    }
    cout << "------------\n\n";
}

bool Bingo::checkWin(game_board board) {

    // check horizontal
    for (int row = 0; row < 5; row++) {
        int sum = 0;
        for (int col = 0; col < 5; col++) {
            if (board.state[row][col]) {
                sum++;
            }
        }
        if (sum == 5) {
            return true;
        }
    }

    // check vertical
    for (int col = 0; col < 5; col++) {
        int sum = 0;
        for (int row = 0; row < 5; row++) {
            if (board.state[row][col]) {
                sum++;
            }
        }
        if (sum == 5) {
            return true;
        }
    }

    return false;
}

void Bingo::startGame(void) {
    //bool won = false;
    //int first_win = -1;
    //int last_win = -1;
    
    for (int round = 0; round < numbers.size(); round++) {
        int pick = numbers[round];
        cout << "==Round #" << round << "== (" << pick << " selected)\n";
        for (auto &current : players) {
            //printBoard(current);
            if (!current.has_won) {
                cout << "player is checking board\n";
                for (int row = 0; row < 5; row++) {
                    for (int col = 0; col < 5; col++) {
                        if (current.board[row][col] == pick) {
                            cout << "\tsomeone has " << pick << "!\n";
                            current.state[row][col] = true;
                            cout << "state " << row << "," << col << "=" << current.state[row][col] << "\n"; 
                            printBoard(current);
                            if (checkWin(current)) {
                                cout << "\t\tBINGO!! Final Score=" << finalScore(current, pick) << "\n";
                                current.has_won = true;
                                //return;
                            }
                        }
                    }
                }
            }
        }
    }
}

vector<int> Bingo::parseNumbers(string data) {
    vector<int> game_data;
    string number = "";
    for (auto digit : data) {
        if (isdigit(digit)) {
            cout << digit << " is a digit\n";
            number.push_back(digit);
        } else {
            cout << "pushing " << number << "\n";
            game_data.push_back(stoi(number, nullptr, 10));
            number.clear();

        }

    }

    if (number.size() > 0) {
        game_data.push_back(stoi(number, 0, 10));
        cout << "pushing " << number << "\n";
    }

    return game_data;
}

vector<int> Bingo::parseBoards(vector<string> data) {
    cout << "\n\n==parseBoards====\n\n";
    vector<int> num_list;
    string number = "";
    for (auto line : data) {
        //string number = "";
        for (auto digit : line) {
            if (isdigit(digit)) {
                cout << digit << " is also a digit\n";
                number.push_back(digit);
            } else {
                if (number.size() > 0) {
                    cout << "\talso pushing " << number << "\n";
                    num_list.push_back(stoi(number, 0, 10));
                    number.clear();
                }
            }

        }

        if (number.size() > 0) {
            cout << "\talso pushing " << number << " EOL\n";
            num_list.push_back(stoi(number, 0, 10));
            number.clear();
        }
    }
        if (number.size() > 0) {
            cout << "\talso pushing " << number << "\n";
            num_list.push_back(stoi(number, 0, 10));
        }

    cout << "numbers going into boards = " << num_list.size() << "\n";

    return num_list; 
} 

vector<game_board> Bingo::parsePlayers(vector<string> data) {
    vector<int> all_boards = parseBoards(data);
    if ((all_boards.size() % 25) != 0)
    {
        cerr << "[!]" << all_boards.size() << "won't fit 5x5 boards evenly!\n";
    }

    vector<game_board> boards;

    int count = 0;
    do {
        game_board player;

        for (int row = 0; row < 5; row++) {

            for (int col = 0; col < 5; col++) {
                player.board[row][col] = all_boards[count];
                player.state[row][col] = false; 
                player.has_won = false;
                count++;
            }

        }    
        boards.push_back(player);
    } while (count < all_boards.size());

    return boards;
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
#if 0
    Bingo game = Bingo(bingo);
    cout << "players = " << game.getPlayers() << "\n";
    cout << "numbers = " << game.getNumbers() << "\n";
    game.startGame();
#endif

    cout << "+++Day 5+++\n";
    VentMap hydrothermal = VentMap(1000, 1000);
    vector<string> day05 = get_challenge_data("./data/05vents.txt");
    hydrothermal.printVents();
    hydrothermal.drawVents(day05, false);
    hydrothermal.printVents();
    cout << "Day 5 Part I = " << hydrothermal.dangersCount() << "\n";

    VentMap hydro2 = VentMap(1000, 1000);
    hydro2.printVents();
    hydro2.drawVents(day05, true);
    hydro2.printVents();
    cout << "Day 5 Part II = " << hydro2.dangersCount() << "\n";
    cout << "(23024 and 23238 were both too high).\n";
    Submarine yellow{};   // obvious Beatles pun
    //yellow.x = 0;       // move to constructor (after I learn how)!
    //yellow.y = 0;
    //yellow.aim = 0;

    cout << "x=" << yellow.x << "\n";
    cout << "y=" << yellow.y << "\n";


    return 0;
}
