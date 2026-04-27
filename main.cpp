//
//  main.cpp
//  Priority Queue Lab
//
//  Created by Angel Munoz on 4/25/26.
//

#include <iostream>
#include<vector>
#include<functional>
#include<algorithm>


using namespace std;
template<typename T>
//make queue priority class in order that it work
class priorityQueue{
private:
    vector<T> elements;
    function<double(const T&)> priorityFunc;
public:
    priorityQueue(function<double(const T&)>priority): priorityFunc(priority){}
//void the push function that the element that will go in the code
    void push(const T& element){
        elements.push_back(element);
        sort(elements.begin(),elements.end(),[this](const T& a, T& b){
            return priorityFunc(a) > priorityFunc(b);
        });
    }
   
        T pop(){
            if (elements.empty()){
                throw runtime_error("The priority of the queue is empty");
            }
            T topElements = move(elements[0]);
            elements.erase(elements.begin());
            return topElements;
        
        }
    
    bool empty() const{
        return elements.empty();
    }
    size_t size() const{
        return elements.size();
    }
    const T& top() const{
        if(elements.empty()){
            throw runtime_error("The priority is empty");
            
        }
        return elements.front();
    }
   

    
};



int main(){
    auto priorioty= [](int x){return x;};
    
    priorityQueue<int> pq(priorioty);
    
    pq.push(8);
    pq.push(23);
    pq.push(2);
    pq.push(12);
    
    cout<<"Size:"<<pq.size()<<endl;
    
    while(!pq.empty()){
        cout<<pq.pop()<<"";
    }
    cout<<endl;
    
}
