//
//  main.cpp
//  Template Lab
//
//  Created by Angel Munoz on 3/14/26.
//

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

//make a template to fill the element and then use a for loop
template <typename T>
vector<T> vec_fill(T elem){
    vector<T> vec(10);
    for (size_t i = 0; i<10;i++){
        vec[i] = elem + static_cast<T>(i);
    }
    return vec;
}
//this goes into the template with the function in a boolean and put in the current
template <typename T>
T until(T elem, function<T(T)>func,function<bool(T)>predicate){
    T current = elem;
    while (!predicate(current)){
        current = func(current);
    }
    return current;
}
//use for swapping the letters
template <typename T,typename U,typename V>
void order(T& a, U& b, V& c){
    if (b > a) swap(a,b);
    if  (c>a) swap(a,c);
    if (c > b) swap(b,c);
}
int main(){
    //use vector and find them
    auto v1 = vec_fill(5);
    for (int x : v1){
        cout<<x<<endl;
    }
    cout<<endl;
    
    //print out the results for all
    auto result =  until<int>(1,[](int x){return x * 2;},[](int x){return x >= 16;});
    cout<<"until the result are:"<<result<<endl;
    
    //print them in order x,y,z
    int x = 3, y = 1, z = 4;
    order(x,y,z);
    cout<<"All in ordered!:"<<x<<y<<z<<endl;
    
}
