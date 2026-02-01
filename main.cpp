//
//  main.cpp
//  pointers lab
//
//  Created by Angel Munoz on 1/27/26.
//

#include <iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;


int main() {
    
    int a , b;
    cout<<"Please use or type two integers:";
    cin>>a>>b;
    
    int* ptr_a = &a;
    int* ptr_b = &b;
    
   
    
    cout<<"Dereferenced ptr_a:"<<endl;
    cout<<"Dereferenced ptr_b:"<<endl;
    
    //using the second program fidng the max array in pointer
    srand(time(0));
    int arr[10];
    for(int i = 0 ; i < 10; i++){
        arr[i] = rand() % 100;
    }
    int* max_ptr = arr;
    for (int* ptr = arr + 1; ptr < arr + 10; ptr++) {
        if(*ptr > *max_ptr){
            max_ptr = ptr;
        }
    }
    cout<<"The maximum value in the array is: "<<*max_ptr<<endl;
    
    char str[] = "Hello World!";
    char* ptr = str;
    int length = 0;
    while(*ptr !=  '\0'){
        length++;
        ptr++;
    }
    cout<<" The length of the string is:"<< length<<endl;
    
    char str2[] = "Hello";
    char* ptr2 = str2;
    while(ptr2 >= str2){
        cout<< *ptr2;
        ptr2--;
        
    }
    cout<<endl;
    
    vector<int> v = {1,2,3,4,5,6};
    auto start = v.begin();
    auto end = v.end() - 1;
    while(start<end){
        start++;
        end--;
    }
    if(start == end){
        cout<<"The midpoint value is:"<<*start<<endl;
    }else{
        cout<<"The midpoint value of the (smaller index) is:"<<*(end+1)<<endl;
    }
    return 0;
}
