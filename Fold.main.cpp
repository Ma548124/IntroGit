//
//  main.cpp
//  Fold Lab
//
//  Created by Angel Munoz on 3/3/26.
//

#include <iostream>
#include <functional>
#include <vector>


using namespace std;

int add(int a, int b){
    return a + b;
}
int multipy(int a, int b){
    return a * b;
}
void print(string s){
    cout<<s<<endl;
}
void printi(int x){
    cout<<x<<endl;
}
int apply(int(*f)(int,int), int a, int b){
    return f(a,b);
}
int fold (vector<int>& v, function<int(int,int)>f, size_t index = 0){
    if(index == v.size() - 1){
        return v[index];
    }
    return f(v[index], fold(v,f,index + 1));
}
int max_val(int a, int b){return max(a,b);}
void ref_inc(int& x){
    x++;
}
int increment(int x){
    return x + 1;
    
}
void transform(function<int(int)>f, vector<int>& v){
    for(int& i : v){
        i = f(i);
    }
}
void for_each(function<void(int&)> f, vector<int>& v){
    for(int& i:v ){
        f(i);
    }
}
int main(){
    
    vector <int> v = {1,6,9,10,20};
   
    for(int i = 0; i<20;i++){
        v.push_back(i);
    }
    int result = multipy(6,9);
    cout<<"The result is:"<<result<<endl;
    
    cout<<endl;
    void(*p)(string) = print;
    int(*f)(int,int) = add;
    
    
    cout<<f(5,12)<<endl;
    
    transform(increment, v);
    for_each(printi,v);
    cout<<endl;
    
    cout<<"All of the folds the test has been passed!"<<endl;
}
