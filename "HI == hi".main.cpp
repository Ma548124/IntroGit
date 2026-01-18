//
//  main.cpp
//  Hi == hi
//
//  Created by Angel Munoz on 1/15/26.
//

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

// string_1 < string_2 returns something less than zero
// string_1 == string_2 returns something equal to zero
// string_1 > string_2 returns something greater than zero

int strcmp_case_insensitive(const string & s1, const string & s2){
    size_t i = 0;
    while (i <s1.length() && i< s2.length()){
        char c1 = tolower(static_cast<unsigned char>(s1[i]));
        char c2 = tolower(static_cast<unsigned>(s2[i]));
        if (c1 != c2){
            return c1 - c2;
        }
        i++;
    }
    
    if (i < s1.length()){
        return tolower(static_cast<unsigned char>(s1[i]));
    }else if (i< s2.length()){
        return -tolower(static_cast<unsigned char>(s2[i]));
    }
    return 0;
}
    
int main(){
    
    assert(strcmp_case_insensitive("hi", "HI") == 0);
    assert(strcmp_case_insensitive("xyz", "XYZ") == 0);
    
    assert(strcmp_case_insensitive("", "") == 0);
    
    assert(strcmp_case_insensitive("college", "COLLEGE") >= 0);
    assert(strcmp_case_insensitive("", "") <= 0);
    
    assert(strcmp_case_insensitive("orange", "ORANGE") <= 0);
    assert(strcmp_case_insensitive("red", "RED") >= 0);
    
    assert(strcmp_case_insensitive("345", "678") <= 0);
    assert(strcmp_case_insensitive("897", "234") >= 0);
    
    assert(strcmp_case_insensitive("hello", "HELLO") >= 0);
    assert(strcmp_case_insensitive("apple", "APPLE") == 0);
    assert(strcmp_case_insensitive("blue", "BLUE") <= 0);
    
    cout<<"All of the strings test have been passed!"<<endl;
    
    return 0;
    
    
    
    
    
}
