//
//  main.cpp
//  Unique-corn Lab
//
//  Created by Angel Munoz on 2/24/26.
//

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Unicorn {
public:
    
    explicit Unicorn(const string& n) {
        if (usedNames.find(n) != usedNames.end()) {
            
            cerr << "Error: Unicorn name '" << n
                      << "' is already taken!\n";
            name.clear();
        } else {
            name = n;
            usedNames.insert(name);
        }
    }

    
    ~Unicorn() {
        if (!name.empty()) {
            usedNames.erase(name);
        }
    }

    // Optional: query the name
    string getName() const {
        return name.empty() ? "(unnamed)" : name;
    }

    Unicorn(const Unicorn&) = delete;
    Unicorn& operator=(const Unicorn&) = delete;

private:
    string name;
    static unordered_set<string> usedNames;
};


unordered_set<string> Unicorn::usedNames;



int main() {
    cout << "Creating the unicorns...\n";

    Unicorn u1("Glitter Rainbow");
    cout << "u1 name: " << u1.getName() << '\n';

    Unicorn u2("Glitter Sparkle");
    cout << "u2 name: " << u2.getName() << '\n';

    
    Unicorn u3("Color Rainbow");
    cout << "u3 name: " << u3.getName() << '\n';

    
    {
        Unicorn u4("Color Rainbow");
        cout << "u4 name: " << u4.getName() << '\n';
    }

    
    Unicorn u5("Color Rainbow");
    cout << "u5 name: " << u5.getName() << '\n';

    cout << "End of program.\n";
    return 0;
}
