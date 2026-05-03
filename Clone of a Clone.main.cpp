//
//  main.cpp
//  Clone of a Clone
//
//  Created by Angel Munoz on 5/3/26.
//

#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <memory>

using namespace std;

class Person {
private:
    string name;
    double height;  //use this in meters
    int age;
    int copyDepth;
    
   
    static mt19937 rng;
    static uniform_real_distribution<double> dist;

public:
   
    Person(const string& n, double h, int a)
        : name(n), height(h), age(a), copyDepth(0) {}

  
    Person(const Person& other)
        : name(other.name), height(other.height), age(other.age), copyDepth(other.copyDepth + 1) {
        mutateIfDeformed();
    }

   
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            height = other.height;
            age = other.age;
            copyDepth = other.copyDepth + 1;
            mutateIfDeformed();
        }
        return *this;
    }

    // Getters
    string getName() const { return name; }
    double getHeight() const { return height; }
    int getAge() const { return age; }
    int getCopyDepth() const { return copyDepth; }

    // Display person info
    void display() const {
        std::cout << "Name: " << name
                  << ", Height: " << height << "m"
                  << ", Age: " << age
                  << ", Copy Depth: " << copyDepth << std::endl;
    }

private:
    void mutateIfDeformed() {
        
        double deformityChance = 0.10 * copyDepth;
        
        if (dist(rng) < deformityChance) {
            mutateName();
            mutateHeight();
            mutateAge();
        }
    }

    void mutateName() {
        string vowels = "aeiouAEIOU";
        string consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
        
        
        for (char& c : name) {
            if (vowels.find(c) != string::npos) {
                // Vowel -> similar vowel or repeat
                c = vowels[dist(rng) * vowels.length()];
            } else if (consonants.find(c) != std::string::npos) {
                // Consonant -> similar or stutter
                if (dist(rng) < 0.3) {
                    c = c; // stutter effect - keep same
                } else {
                    c = consonants[(consonants.find(c) + (dist(rng) > 0.5 ? 1 : -1)) % consonants.length()];
                }
            }
        }
        
        
        if (dist(rng) < 0.4) {
            name = "Mutant-" + name;
        } else if (dist(rng) < 0.4) {
            name += "-clone";
        }
    }

    void mutateHeight() {
       
        double mutationFactor = 0.8 + dist(rng) * 0.4; // 0.8 to 1.2
        height *= mutationFactor;
        
        
        if (height < 0.5) height = 0.5;
        if (height > 2.5) height = 2.5;
    }

    void mutateAge() {
        // Age mutation: ±30% or random jump, reasonable bounds (0-150)
        if (dist(rng) < 0.5) {
            age = static_cast<int>(age * (0.7 + dist(rng) * 0.6)); // 70-130%
        } else {
            age += static_cast<int>((dist(rng) - 0.5) * 60); // ±30 years
        }
        
        if (age < 0) age = 0;
        if (age > 150) age = 150;
    }
};


mt19937 Person::rng(random_device{}());
uniform_real_distribution<double> Person::dist(0.0, 1.0);

int main() {
    std::cout << "=== Cloning Experiment ===" << std::endl;
    
    // Original person
    Person original("Jesus", 3.25, 15);
    cout << "Original: ";
    original.display();
    
    cout << "\n=== Cloning generations ===" << endl;
    
    Person clone1 = original;
    cout << "Clone 1: ";
    clone1.display();
    
    Person clone2 = clone1;
    cout << "Clone 2: ";
    clone2.display();
    
    Person clone3 = clone2;
    cout << "Clone 3: ";
    clone3.display();
    
    Person clone4 = clone3;
   cout << "Clone 4: ";
    clone4.display();
    
    Person clone5 = clone4;
    cout << "Clone 5: ";
    clone5.display();
    
    cout << "\n=== Assignment test ===" << endl;
    
   
    
    return 0;
}
