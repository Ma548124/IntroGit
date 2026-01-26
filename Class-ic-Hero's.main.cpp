//
//  main.cpp
//  Class-ic Hero's Journey
//
//  Created by Angel Munoz on 1/22/26.
//

#include <iostream>
#include<string>
#include<ctime>
#include<cstdlib>

using namespace std;
// Hero class and making it into a private and public
class Hero {
private:
    string strength;
    string courage;
    string name;

public:
   
    Hero(const string& heroName) : name(heroName) {
        
        int strengthRand = rand() % 3;
        if (strengthRand == 0) strength = "weak";
        else if (strengthRand == 1) strength = "average";
        else strength = "strong";

       
        int courageRand = rand() % 3;
        if (courageRand == 0) courage = "cowardly";
        else if (courageRand == 1) courage = "normal";
        else courage = "brave";
    }

    
    string getStrength() const {
        return strength;
    }

   
    string getCourage() const {
        return courage;
    }
    void setCourage(const string& newCourage) {
        courage = newCourage;
    }

    // Getter for name (no setter)
    string getName() const {
        return name;
    }

   
    void attendTraining(float time) {
        
        if (strength == "weak") strength = "average";
        else if (strength == "average") strength = "strong";
        
    }

   
    void attendTherapy() {
        // Randomly upgrade courage
        int upgrade = rand() % 2;
        if (upgrade == 1) {
            if (courage == "cowardly") courage = "normal";
            else if (courage == "normal") courage = "brave";
            // "brave" is max, stays the same
        }
    }
};


void sendOnQuest(Hero& hero) {
    
    int successChance;
    if (hero.getStrength() == "weak") successChance = 20;
    else if (hero.getStrength() == "average") successChance = 50;
    else successChance = 80;

    int roll = rand() % 100 + 1;
    string result;
    string newCourage;
    if (roll <= successChance) {
        if (roll <= successChance / 2) {
            result = "success";
            
            if (hero.getCourage() == "brave") newCourage = "normal";
            else if (hero.getCourage() == "normal") newCourage = "cowardly";
            else newCourage = "cowardly";  // Already cowardly
        } else {
            result = "neutral";
            // Medium loss
            if (hero.getCourage() == "brave") newCourage = "cowardly";
            else newCourage = "cowardly";
        }
    } else {
        result = "failng";
        newCourage = "cowardly";
    }

    // Set new courage
    hero.setCourage(newCourage);

    // Print result
    cout << hero.getName() << " they went on the quest and these are the results " << result << "!" << endl;
}

int main() {
    // Seed the random number generator for different runs
    srand(static_cast<unsigned int>(time(0)));

    // Create several heroes
    Hero hero1("Max");
    Hero hero2("Larry");
    Hero hero3("Jared");

    // Test their functions
    cout << "Initial stats:" << endl;
    cout << hero1.getName() << " - Strength: " << hero1.getStrength() << ", Courage: " << hero1.getCourage() << endl;
    cout << hero2.getName() << " - Strength: " << hero2.getStrength() << ", Courage: " << hero2.getCourage() << endl;
    cout << hero3.getName() << " - Strength: " << hero3.getStrength() << ", Courage: " << hero3.getCourage() << endl;

   
    hero1.attendTraining(5.0f);
    hero1.attendTherapy();
    hero2.attendTraining(10.0f);
    hero2.attendTherapy();
    hero3.attendTraining(2.0f);
    hero3.attendTherapy();

   cout << "\nAfter the training and the therapy:" << endl;
    cout << hero1.getName() << " - Strength: " << hero1.getStrength() << ", Courage: " << hero1.getCourage() << endl;
    cout << hero2.getName() << " - Strength: " << hero2.getStrength() << ", Courage: " << hero2.getCourage() << endl;
    cout << hero3.getName() << " - Strength: " << hero3.getStrength() << ", Courage: " << hero3.getCourage() << endl;

    // Send them on quests
    cout << "\nQuest results:" << endl;
    sendOnQuest(hero1);
    sendOnQuest(hero2);
    sendOnQuest(hero3);

    // More actions for testing
    hero1.attendTherapy();
    sendOnQuest(hero1);
    hero2.attendTraining(3.0f);
    sendOnQuest(hero2);

    cout << "\nFinal stats:" << endl;
    cout << hero1.getName() << " - Strength: " << hero1.getStrength() << ", Courage: " << hero1.getCourage() << endl;
    cout << hero2.getName() << " - Strength: " << hero2.getStrength() << ", Courage: " << hero2.getCourage() << endl;
    cout << hero3.getName() << " - Strength: " << hero3.getStrength() << ", Courage: " << hero3.getCourage() << endl;

    return 0;
}
