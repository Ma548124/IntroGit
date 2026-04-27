//
//  main.cpp
//  Extending Data Structures
//
//  Created by Angel Munoz on 4/21/26.
//

#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>
#include <string>

using namespace std;
//have to out in a class first for the queue in order that would be implemented
template<typename T>
class Queue{
private:
    vector<T>data;
    stack<int> s1,s2;
public:
    
    void push(const T& item){
        data.push_back(item);
    }
    T pop_font(){
        if(data.empty()){
            throw runtime_error("the queue is not there");
        }
        T item = data.front();
        data.erase(data.begin());
        return item;
    }
    T pop_back(){
        if(data.empty()){
            throw runtime_error("the queue is not there");
        }
        T item = data.front();
        data.erase(data.begin());
        return item;
    }
    T& front(){
        if(data.empty()){
            throw runtime_error("the queue is being empty!");
        }
        return data.front();
    }
    bool empty() const{
        return data.empty();
    }
    size_t size() const{
        return size();
    }
};
template<typename T>
class Quack{
private:
    vector<T> data;
public:
     void push_front(const T& item){
        data.insert(data.begin(),item);
    }
    void push_back(const T& item){
        data.push_back(item);
    }
    T pop_front(){
        if(data.empty()){
            throw runtime_error("the Quack is not there");
        }
        T item = data.front();
        data.erase(data.begin());
        return item;
    }
    T pop_back(){
        if(data.empty()){
            throw runtime_error("the Quack is not there");
        }
        T item = data.back();
        data.erase(data.begin());
        return item;
    }
    const T& front(){
        if(data.empty()){
            throw runtime_error("the Quack is being empty!");
        }
        return data.front();
    }
    const T& back(){
        if(data.empty()){
            throw runtime_error("The Quack is empty");
        }
        return data.back();
    }
    bool empty() const{
        return data.empty();
    }
    size_t size() const{
        return size();
    }
};
int main(){
  //stacking the number elements into place that it will work out.
    Queue<int> queue;
    queue.push(15);
    queue.push(24);
    queue.push(65);
   //printing out the elements
    
    cout<<"Queue front pop:"<< queue.pop_font()<< endl;
    cout<<"Queue is pop back:"<<queue.pop_back()<<endl;
    
    Quack<string>quack;
    quack.push_front("front");
    quack.push_back("back");
    quack.push_front("first");
    quack.push_back("last");
    
    cout<<"The pop_front is working for quack:"<<quack.pop_front()<<endl;
    cout<<"The pop_back is working for quack:"<<quack.pop_back()<<endl;
    cout<<"The front is working for quack:"<<quack.front()<<endl;
    cout<<"The back is working for quack:"<<quack.back()<<endl;
    
   
    
    
}
