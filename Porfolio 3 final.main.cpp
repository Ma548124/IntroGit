//
//  main.cpp
//  Portfolio 3 final
//
//  Created by Angel Munoz on 5/16/26.
//

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <utility>
#include <map>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include <fstream>

using namespace std;

enum class FloorType { Rocks, Lava, Spikes, Water, Fire };

struct Player {
    int x, y;
    int health = 100;
    int strength = 10;
    int defense = 5;
    int keys = 0;
};

struct Enemy {
    string subtype;
    int health;
    int strength;
    int defense;
};

struct Dungeon {
    string name;
    int rows, cols;
    vector<vector<char>> grid;
    vector<pair<pair<int, int>, pair<int, int>>> teleporters;
    Player player;
};

// File format:
// First line: ROWS COLS NAME
// Next ROWS lines: grid data (space-separated chars)
// Next lines: Teleporter pairs "T X1 Y1 X2 Y2"
// End with "END"

bool saveDungeonToFile(const Dungeon& dungeon, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot create file " << filename << endl;
        return false;
    }
    
    // Header: rows cols name
    file << dungeon.rows << " " << dungeon.cols << " " << dungeon.name << endl;
    
    // Grid
    for (int i = 0; i < dungeon.rows; i++) {
        for (int j = 0; j < dungeon.cols; j++) {
            file << dungeon.grid[i][j];
            if (j < dungeon.cols - 1) file << " ";
        }
        file << endl;
    }
    
    // Teleporters
    for (const auto& tp : dungeon.teleporters) {
        file << "T " << tp.first.first << " " << tp.first.second << " "
             << tp.second.first << " " << tp.second.second << endl;
    }
    
    file << "END" << endl;
    file.close();
    cout << "Saved to " << filename << endl;
    return true;
}

bool loadDungeonFromFile(Dungeon& dungeon, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: File '" << filename << "' not found!" << endl;
        return false;
    }
    
    string line;
    getline(file, line);
    stringstream header(line);
    
    int rows, cols;
    header >> rows >> cols;
    if (!header) {
        cout << "ERROR: Invalid file format - bad header!" << endl;
        file.close();
        return false;
    }
    
    getline(header, dungeon.name);  // Get remaining line as name
    if (dungeon.name.empty()) dungeon.name = "Loaded Dungeon";
    
    // Read grid
    dungeon.rows = rows;
    dungeon.cols = cols;
    dungeon.grid.assign(rows, vector<char>(cols, ' '));
    
    for (int i = 0; i < rows; i++) {
        getline(file, line);
        stringstream ss(line);
        for (int j = 0; j < cols; j++) {
            string cell;
            ss >> cell;
            if (!cell.empty()) {
                dungeon.grid[i][j] = cell[0];  // Take first char
            }
        }
    }
    
    // Read teleporters
    dungeon.teleporters.clear();
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        ss >> token;
        
        if (token == "END") break;
        if (token == "T") {
            int x1, y1, x2, y2;
            ss >> x1 >> y1 >> x2 >> y2;
            dungeon.teleporters.push_back({{x1, y1}, {x2, y2}});
        }
    }
    
    file.close();
    
    // Find player position
    bool foundPlayer = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dungeon.grid[i][j] == '@') {
                dungeon.player = {i, j};
                foundPlayer = true;
                break;
            }
        }
        if (foundPlayer) break;
    }
    
    cout << "Loaded " << filename << " (" << rows << "x" << cols << ")" << endl;
    return true;
}

string getDungeonFilename(const string& name) {
    string filename = name;
    // Add .dun if not present
    if (filename.size() < 4 || filename.substr(filename.size()-4) != ".dun") {
        filename += ".dun";
    }
    return filename;
}

void findAndFixPlayerPosition(vector<vector<char>>& grid, Player& player) {
    int playerCount = 0;
    pair<int, int> playerPos;
    
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == '@') {
                playerCount++;
                playerPos = {i, j};
                if (playerCount > 1) {
                    grid[i][j] = ' ';
                }
            }
        }
    }
    
    if (playerCount == 0) {
        cout << "Warning: No player! Placing at (1,1)" << endl;
        if (grid.size() > 1 && grid[0].size() > 1) {
            grid[1][1] = '@';
            playerPos = {1, 1};
        }
    }
    
    player.x = playerPos.first;
    player.y = playerPos.second;
}

void displayDungeon(const vector<vector<char>>& dungeon) {
    for (const auto& row : dungeon) {
        for (char cell : row) cout << cell;
        cout << endl;
    }
}

void displayStats(const Player& player) {
    cout << "HP:" << player.health << " STR:" << player.strength
         << " DEF:" << player.defense << " Keys:" << player.keys << endl;
}

bool processMove(vector<vector<char>>& dungeon, Player& player, int dx, int dy,
                const vector<pair<pair<int, int>, pair<int, int>>>& teleporters) {
    int newX = player.x + dx;
    int newY = player.y + dy;
    
    if (newX < 0 || newX >= dungeon[0].size() || newY < 0 || newY >= dungeon.size()) {
        cout << "Wall!" << endl; return true;
    }
    
    char target = dungeon[newY][newX];
    if (target == '#') {
        cout << "Solid wall!" << endl; return true;
    }
    
    dungeon[player.y][player.x] = ' ';
    player.x = newX; player.y = newY;
    
    if (target == 'T') {
        for (const auto& tp : teleporters) {
            if (tp.first.first == player.x && tp.first.second == player.y) {
                player.x = tp.second.first; player.y = tp.second.second;
                cout << "Teleported!" << endl; break;
            } else if (tp.second.first == player.x && tp.second.second == player.y) {
                player.x = tp.first.first; player.y = tp.first.second;
                cout << "Teleported!" << endl; break;
            }
        }
        target = dungeon[player.y][player.x];
    }
    
    switch (target) {
        case ' ': cout << "Empty space." << endl; break;
        case 'K': player.keys++; cout << "Key! (" << player.keys << ")" << endl; break;
        case 'D':
            if (player.keys > 0) { player.keys--; cout << "Door opened!" << endl; }
            else { cout << "Locked!"; player.x -= dx; player.y -= dy; dungeon[player.y][player.x] = '@'; return true; }
            break;
        case 'H': player.health += 20; cout << "Health +20!" << endl; break;
        case 'S': player.strength += 5; cout << "STR +5!" << endl; break;
        case 'F': player.defense += 5; cout << "DEF +5!" << endl; break;
        case 'E': {
            Enemy e = {"goblin", 30, 6, 2};
            cout << "Enemy battle!"; /* Simplified battle */
            break;
        }
        case 'G': cout << "VICTORY!" << endl; return false;
        case 'L': player.health = max(0, player.health-5); cout << "Lava! -5HP" << endl; break;
        case 'P': player.health = max(0, player.health-3); cout << "Spikes! -3HP" << endl; break;
        case 'R': player.health = max(0, player.health-2); cout << "Rocks! -2HP" << endl; break;
    }
    
    dungeon[player.y][player.x] = '@';
    return true;
}

void inspectLocation(const vector<vector<char>>& dungeon, const Player& player) {
    cout << "At (" << player.x << "," << player.y << "): '" << dungeon[player.y][player.x] << "'" << endl;
}

int main() {
    srand(time(0));
        vector<Dungeon> dungeons = {
            {"Tutorial", 8, 10, {
                {'#','#','#','#','#','#','#','#','#','#'},{'#',' ',' ',' ','L',' ',' ',' ',' ','#'},
                {'#',' ','E',' ','#',' ','K',' ',' ','#'},{'#',' ',' ','S',' ',' ',' ',' ',' ','#'},
                {'#',' ','#','#',' ','#','D',' ',' ','#'},{'#','K',' ',' ',' ',' ',' ','G',' ','#'},
                {'#',' ',' ',' ','@',' ',' ',' ',' ','#'},{'#','#','#','#','#','#','#','#','#','#'}
            }, {}}
        };
        
        bool running = true;
        while (running) {
            cout << "\n=== Dungeon Game ===\n";
            cout << "1) Play Dungeon\n2) Editor\n3) Quit\nChoice: ";
            int choice; cin >> choice; cin.ignore();
            
            if (choice == 1) {
                cout << "\nDungeons:\n0) Load from file\n";
                for (size_t i = 0; i < dungeons.size(); i++) {
                    cout << (i+1) << ") " << dungeons[i].name << endl;
                }
                cout << "Select: ";
                string input;
                getline(cin, input);
                
                Dungeon current;
                bool loaded = false;
                
                if (input == "0") {
                    cout << "Filename (Level1 or Level1.dun): ";
                    string fname;
                    getline(cin, fname);
                    string filename = getDungeonFilename(fname);
                    loaded = loadDungeonFromFile(current, filename);
                } else {
                    int idx = stoi(input) - 1;
                    if (idx >= 0 && idx < (int)dungeons.size()) {
                        current = dungeons[idx];
                        loaded = true;
                    }
                }
                
                if (loaded) {
                    Player player = current.player;
                    findAndFixPlayerPosition(current.grid, player);
                    
                    cout << "\n=== " << current.name << " ===\nCommands: L/R/U/D, I=inspect, Q=quit\n";
                    bool playing = true;
                    while (playing) {
                        cout << "\n" << string(40, '-') << "\n";
                        displayDungeon(current.grid);
                        displayStats(player);
                        cout << "Command: ";
                        string cmd; getline(cin, cmd);
                        
                        if (cmd == "Q" || cmd == "q") { cout << "Quit dungeon.\n"; break; }
                        if (cmd == "I" || cmd == "i") { inspectLocation(current.grid, player); continue; }
                        
                        int dx = 0, dy = 0;
                        if (cmd == "L" || cmd == "Left") dy = -1;
                        else if (cmd == "R" || cmd == "Right") dy = 1;
                        else if (cmd == "U" || cmd == "Up") dx = -1;
                        else if (cmd == "D" || cmd == "Down") dx = 1;
                        else continue;
                        
                        playing = processMove(current.grid, player, dx, dy, current.teleporters);
                    }
                } else {
                    cout << "Try again.\n";
                }
            }
            else if (choice == 2){
                cout << "Editor - Rows cols (max 20x30): ";
                int rows, cols; cin >> rows >> cols; cin.ignore();
                
                vector<vector<char>> grid(rows, vector<char>(cols, ' '));
                
                for (int i = 0; i < rows; i++) grid[i][0] = grid[i][cols-1] = '#';
                for (int j = 0; j < cols; j++) grid[0][j] = grid[rows-1][j] = '#';
                grid[1][1] = '@';
                
                string dname = "NewDungeon";
                vector<pair<pair<int,int>,pair<int,int>>> teleporters;
                
                bool editing = true;
                while (editing) {
                    cout << "\n=== Editor ===\n";
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) cout << grid[i][j];
                        cout << endl;
                    }
                    cout << "\n1=Space 2=Wall 3=@ 4=G 5=K 6=D 7=E 8=H 9=S 10=F 11=T 12=Lava\n";
                    cout << "S=Save Q=Quit: ";
                    string action; getline(cin, action);
                    
                    if (action == "Q" || action == "q") { editing = false; continue; }
                    if (action == "S" || action == "s") {
                        cout << "Save as (or ENTER for " << dname << "): ";
                        string name; getline(cin, name);
                        if (!name.empty()) dname = name;
                        
                        cout << "Save to file? (y/n): ";
                        string savefile; getline(cin, savefile);
                        Dungeon toSave = {dname, rows, cols, grid, teleporters};
                        toSave.player.x = 1; toSave.player.y = 1;
                        
                        if (savefile == "y" || savefile == "Y") {
                            string filename = getDungeonFilename(dname);
                            if (!saveDungeonToFile(toSave, filename)) {
                                cout << "Save failed!\n";
                            }
                        }
                        cout << "Dungeon '" << dname << "' saved to memory!\n";
                        dungeons.push_back(toSave);
                        break;
                    }
                    
                    
                    int choice = stoi(action);
                    cout << "Row col (1-based): ";
                    int r, c; cin >> r >> c; cin.ignore();
                    if (r > 0 && r <= rows && c > 0 && c <= cols) {
                        char sym = ' ';
                        if (choice == 1) sym = ' ';
                        else if (choice == 2) sym = '#';
                        else if (choice == 3) sym = '@';
                        else if (choice == 4) sym = 'G';
                        else if (choice == 5) sym = 'K';
                        else if (choice == 6) sym = 'D';
                        else if (choice == 7) sym = 'E';
                        else if (choice == 8) sym = 'H';
                        else if (choice == 9) sym = 'S';
                        else if (choice == 10) sym = 'F';
                        else if (choice == 11) sym = 'T';
                        else if (choice == 12) sym = 'L';
                        grid[r-1][c-1] = sym;
                    }
                }
            }
            else if (choice == 3) {
                running = false;
            }
        }
        cout << "Thank you for playing the Dungeon Game Goodbye!\n";
        return 0;
    }
