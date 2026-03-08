//
//  main.cpp
//  Until Lab
//
//  Created by Angel Munoz on 3/5/26.
//

#include <iostream>
#include <functional>


using namespace std;

int square(int x){
    return x * x;
}

void printi(int x){
    cout<<x<<endl;
}
int  add(int a, int b){
    return a+b;
}
int apply(int (*f)(int,int),int a,int b){
    return f(a,b);
}
int apply(function<int(int,int)> f,int a,int b){
    return f(a,b);
}
int until(int x, function<int(int)>f, function<bool(int)>g){
   
    while(!g(x)){
        x = f(x);
    }
    return x;
}
int increment(int x){
    return x +1;
}
bool is_eight_or_more(int x){
    return x >= 8;
}


int main(){
    
    int start_value = 1;
    
    int result = until(start_value,increment, is_eight_or_more);
    
    cout<<"the starting value is:"<<start_value<<endl;
    cout<<"The final value is (>= 8):"<< result<<endl;
    
    vector <int> v = { 1,2,4,8,16,32,64,128};
    
    for(int i = 0; i < 129; i++){
        v.push_back(i);
        cout<<i<<endl;
    }
    int start_value_2 = 8;
    int result_2 = until(start_value_2,
                         [](int x){return x * 2;},
                         [](int x){return x > 128;});
    cout<<"The starting value of two:"<<start_value_2<<endl;
    cout<<"The final value of (>128):"<<result_2<<endl;
    
    
}
