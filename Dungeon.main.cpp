//
//  main.cpp
//  Magic Tower Portfolio 1
//
//  Created by Angel Munoz on 2/9/26.
//

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

// Player struct
struct Player {
    int x, y; // position
    int health;
    int strength;
    int defense;
    int keys;
};

// Enemy struct (for battles)
struct Enemy {
    int health;
    int strength;
    int defense;
};

// Dungeon struct
struct Dungeon {
    string name;
    int rows, cols;
    vector<vector<char>> grid;
    vector<pair<pair<int, int>, pair<int, int>>> teleporters;
};

// Function to display the dungeon
void displayDungeon(const vector<vector<char>>& dungeon) {
    for (const auto& row : dungeon) {
        for (char cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

// Function to display player stats
void displayStats(const Player& player) {
    cout << "Health: " << player.health << endl;
    cout << "Strength: " << player.strength << endl;
    cout << "Defense: " << player.defense << endl;
    cout << "Keys: " << player.keys << endl;
}

// Function to handle battle
bool battle(Player& player, Enemy enemy) {
    cout << "A battle begins!" << endl;
    while (player.health > 0 && enemy.health > 0) {
        // Player attacks
        int damage = player.strength - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            cout << "You deal " << damage << " damage to the enemy. Enemy health: " << enemy.health << endl;
        } else {
            cout << "Your attack does no damage." << endl;
        }
        if (enemy.health <= 0) {
            cout << "You defeated the enemy!" << endl;
            return true; // player wins
        }
        // Enemy attacks
        damage = enemy.strength - player.defense;
        if (damage > 0) {
            player.health -= damage;
            cout << "Enemy deals " << damage << " damage to you. Your health: " << player.health << endl;
        } else {
            cout << "Enemy's attack does no damage." << endl;
        }
        if (player.health <= 0) {
            cout << "You were defeated! Game Over." << endl;
            return false; // player loses
        }
    }
    return false; // shouldn't reach here
}

// Function to process move
bool processMove(vector<vector<char>>& dungeon, Player& player, int dx, int dy, const vector<pair<pair<int, int>, pair<int, int>>>& teleporters) {
    int newX = player.x + dx;
    int newY = player.y + dy;
    int rows = dungeon.size();
    int cols = dungeon[0].size();
    
    if (newX < 0 || newX >= rows || newY < 0 || newY >= cols) {
        cout << "You can't move there (out of bounds)." << endl;
        return true; // continue game
    }
    
    char target = dungeon[newX][newY];
    if (target == '#') {
        cout << "You can't move into a wall." << endl;
        return true;
    }
    
    // Move player
    dungeon[player.x][player.y] = ' '; // clear old position
    player.x = newX;
    player.y = newY;
    
    // Handle teleport if stepped on teleporter
    if (target == 'T') {
        for (const auto& tp : teleporters) {
            if (tp.first.first == player.x && tp.first.second == player.y) {
                player.x = tp.second.first;
                player.y = tp.second.second;
                break;
            } else if (tp.second.first == player.x && tp.second.second == player.y) {
                player.x = tp.first.first;
                player.y = tp.first.second;
                break;
            }
        }
        cout << "You teleported!" << endl;
    }
    
    // Handle other interactions
    if (target == ' ') {
        cout << "You move into an empty space." << endl;
    } else if (target == 'K') {
        player.keys++;
        cout << "You picked up a key! Keys: " << player.keys << endl;
    } else if (target == 'D') {
        if (player.keys > 0) {
            player.keys--;
            cout << "You unlocked the door with a key! Keys: " << player.keys << endl;
        } else {
            cout << "The door is locked. You need a key." << endl;
            // Move back
            dungeon[player.x][player.y] = 'D';
            player.x -= dx;
            player.y -= dy;
            dungeon[player.x][player.y] = '@';
            return true;
        }
    } else if (target == 'H') {
        player.health += 5;
        cout << "You drank a health potion! Health: " << player.health << endl;
    } else if (target == 'S') {
        player.strength += 5;
        cout << "You drank a strength potion! Strength: " << player.strength << endl;
    } else if (target == 'F') {
        player.defense += 5;
        cout << "You drank a defense potion! Defense: " << player.defense << endl;
    } else if (target == 'E') {
        Enemy enemy = {50, 8, 3}; // standard enemy stats
        if (!battle(player, enemy)) {
            return false; // game over
        }
    } else if (target == 'G') {
        cout << "You reached the goal! Victory!" << endl;
        return false; // end game
    } else if (target == 'T') {
        // Teleport already handled above
    }
    
    dungeon[player.x][player.y] = '@'; // place player
    return true;
}

// Function to display editor grid
void displayEditorGrid(const vector<vector<char>>& grid, int rows, int cols) {
    cout << "  ";
    for (int c = 1; c <= cols; ++c) {
        cout << c << " ";
    }
    cout << endl;
    for (int r = 0; r < rows; ++r) {
        cout << (r + 1) << " ";
        for (int c = 0; c < cols; ++c) {
            cout << grid[r][c] << " ";
        }
        cout << endl;
    }
}

// Function to get object symbol
char getObjectSymbol(int choice) {
    switch (choice) {
        case 1: return ' ';
        case 2: return '#';
        case 3: return '@';
        case 4: return 'G';
        case 5: return 'W';
        case 6: return 'J';
        case 7: return 'E';
        case 8: return 'H';
        case 9: return 'P';
        case 10: return 'F';
        case 11: return 'T';
        default: return ' ';
    }
}

// Function to find player position
void findPlayerPosition(const vector<vector<char>>& grid, Player& player) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == '@') {
                player.x = i;
                player.y = j;
                return;
            }
        }
    }
}

int main() {
    // Pre-loaded dungeons
    vector<Dungeon> dungeons;
    
    // Tutorial dungeon
    Dungeon tutorial;
    tutorial.name = "Tutorial";
    tutorial.rows = 6;
    tutorial.cols = 7;
    tutorial.grid = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', ' ', '#', '#', '#'},
        {'#', ' ', 'E', '#', ' ', 'J', '#'},
        {'#', ' ', ' ', '#', '#', 'U', '#'},
        {'#', 'K', ' ', '@', '#', 'W', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
    };
    tutorial.teleporters = {}; // no teleporters
    dungeons.push_back(tutorial);
    
    // Level 1 dungeon
    Dungeon level1;
    level1.name = "Level 1";
    level1.rows = 5;
    level1.cols = 5;
    level1.grid = {
        {'#', '#', '#', '#', '#','C'},
        {'#', '@', ' ', 'K', '#','E'},
        {'#', ' ', '#', ' ', '#','P'},
        {'#', 'O', ' ', 'A', '#','#'},
        {'#', '#', '#', '#', '#','#'}
    };
    level1.teleporters = {}; // no teleporters
    dungeons.push_back(level1);
    
    // Main menu loop
    bool running = true;
    while (running) {
        cout << "Welcome to Magic Tower of Sorcerer: Revenge of the Warlock Part VII" << endl;
        cout << "1) Enter a dungeon" << endl;
        cout << "2) Design a dungeon" << endl;
        cout << "3) Exit" << endl;
        cout << "Select an option: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (choice == 1) {
            // Enter a dungeon
            cout << "Available Dungeons:" << endl;
            for (size_t i = 0; i < dungeons.size(); ++i) {
                cout << (i + 1) << ") " << dungeons[i].name << endl;
            }
            cout << "Select a dungeon number: ";
            int dungeonChoice;
            cin >> dungeonChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (dungeonChoice < 1 || dungeonChoice > (int)dungeons.size()) {
                cout << "Invalid choice." << endl;
                continue;
            }
            Dungeon selectedDungeon = dungeons[dungeonChoice - 1];
            Player player = {0, 0, 100, 10, 5, 0}; // reset stats
            findPlayerPosition(selectedDungeon.grid, player);
            
            // Game loop
            bool gameRunning = true;
            while (gameRunning) {
                cout << endl;
                displayDungeon(selectedDungeon.grid);
                cout << endl;
                displayStats(player);
                cout << endl;
                cout << "Enter move (L/Left, R/Right, U/Up, D/Down): ";
                string input;
                cin >> input;
                
                int dx = 0, dy = 0;
                if (input == "L" || input == "Left") {
                    dy = -1;
                } else if (input == "R" || input == "Right") {
                    dy = 1;
                } else if (input == "U" || input == "Up") {
                    dx = -1;
                } else if (input == "D" || input == "Down") {
                    dx = 1;
                } else {
                    cout << "Invalid input. Try again." << endl;
                    continue;
                }
                
                gameRunning = processMove(selectedDungeon.grid, player, dx, dy, selectedDungeon.teleporters);
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else if (choice == 2) {
            // Design a dungeon
            cout << "Enter number of rows: ";
            int rows;
            cin >> rows;
            cout << "Enter number of columns: ";
            int cols;
            cin >> cols;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            vector<vector<char>> grid(rows, vector<char>(cols, ' '));
            vector<pair<pair<int, int>, pair<int, int>>> teleporters;
            
            bool editing = true;
            while (editing) {
                cout << endl;
                displayEditorGrid(grid, rows, cols);
                cout << endl;
                cout << "Actions:" << endl;
                cout << "1) Add object" << endl;
                cout << "2) Save dungeon" << endl;
                cout << "Select action: ";
                int action;
                cin >> action;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (action == 1) {
                    cout << "Objects:" << endl;
                    cout << "1) Empty Space" << endl;
                    cout << "2) Wall" << endl;
                    cout << "3) Player" << endl;
                    cout << "4) Goal" << endl;
                    cout << "5) Key" << endl;
                    cout << "6) Locked Door" << endl;
                    cout << "7) Enemy" << endl;
                    cout << "8) Health Potion" << endl;
                    cout << "9) Strength Potion" << endl;
                    cout << "10) Defense Potion" << endl;
                    cout << "11) Teleporter" << endl;
                    cout << "Select object by number or name: ";
                    string objInput;
                    getline(cin, objInput);
                    
                    int objChoice = 0;
                    if (objInput == "1" || objInput == "Empty Space") objChoice = 1;
                    else if (objInput == "2" || objInput == "Wall") objChoice = 2;
                    else if (objInput == "3" || objInput == "Player") objChoice = 3;
                    else if (objInput == "4" || objInput == "Goal") objChoice = 4;
                    else if (objInput == "5" || objInput == "Key") objChoice = 5;
                    else if (objInput == "6" || objInput == "Locked Door") objChoice = 6;
                    else if (objInput == "7" || objInput == "Enemy") objChoice = 7;
                    else if (objInput == "8" || objInput == "Health Potion") objChoice = 8;
                    else if (objInput == "9" || objInput == "Strength Potion") objChoice = 9;
                    else if (objInput == "10" || objInput == "Defense Potion") objChoice = 10;
                    else if (objInput == "11" || objInput == "Teleporter") objChoice = 11;
                    else {
                        cout << "Invalid object." << endl;
                        continue;
                    }
                    
                    if (objChoice == 11) {
                        // Place first teleporter
                        cout << "Enter row and column for first teleporter (1-based): ";
                        int r1, c1;
                        cin >> r1 >> c1;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (r1 < 1 || r1 > rows || c1 < 1 || c1 > cols) {
                            cout << "Invalid coordinates." << endl;
                            continue;
                        }
                        grid[r1 - 1][c1 - 1] = 'T';
                        
                        // Place second teleporter
                        cout << "Enter row and column for second teleporter (1-based): ";
                        int r2, c2;
                        cin >> r2 >> c2;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (r2 < 1 || r2 > rows || c2 < 1 || c2 > cols) {
                            cout << "Invalid coordinates." << endl;
                            // Remove first if invalid
                            grid[r1 - 1][c1 - 1] = ' ';
                            continue;
                        }
                        grid[r2 - 1][c2 - 1] = 'T';
                        teleporters.push_back({{r1 - 1, c1 - 1}, {r2 - 1, c2 - 1}});
                    } else {
                        cout << "Enter row and column (1-based): ";
                        int r, c;
                        cin >> r >> c;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (r < 1 || r > rows || c < 1 || c > cols) {
                            cout << "Invalid coordinates." << endl;
                            continue;
                        }
                        grid[r - 1][c - 1] = getObjectSymbol(objChoice);
                    }
                } else if (action == 2) {
                    cout << "Enter dungeon name: ";
                    string name;
                    getline(cin, name);
                    Dungeon newDungeon = {name, rows, cols, grid, teleporters};
                    dungeons.push_back(newDungeon);
                    cout << "Dungeon saved!" << endl;
                    editing = false;
                } else {
                    cout << "Invalid action." << endl;
                }
            }
        } else if (choice == 3) {
            running = false;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    
    return 0;
}
