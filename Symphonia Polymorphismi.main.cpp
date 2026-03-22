//
//  main.cpp
//  Symphonia Polymorphismi Lab
//
//  Created by Angel Munoz on 3/22/26.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class instrument{
private:
    string name;
    string sound;
public:
    string sounds;
    instrument(const string&n, const string&s): name(n),sound(s){}
    virtual ~instrument() = default;
    
    virtual void play() const{
        cout<<name<<"The instrument make a"<<sound<<"The sounds."<<endl;
    }
};
class trumpet:public instrument{
public:
    trumpet() :instrument("Trumpet", "doot doot"){}
    void play() const override{
        for (int i = 0; i < 6;i++){
            cout<<sounds<<endl;;
        }
        cout<<endl;
    }
};
class violin:public instrument{
public:
    violin() :instrument("Violin", "Wawa wawa"){}
    void play() const override{
        for (int i = 0; i < 4;i++){
            cout<<sounds<<endl;;
        }
        cout<<endl;
    }
};
class flute:public instrument{
public:
    flute() :instrument("Flute", "toot toot"){}
    void play() const override{
        for (int i = 0; i < 10;i++){
            cout<<sounds<<endl;;
        }
        cout<<endl;
    }
};
class piano:public instrument{
public:
    piano() :instrument("Piano", "click click"){}
    void play() const override{
        for (int i = 0; i < 8;i++){
            cout<<sounds<<endl;;
        }
        cout<<endl;
    }
};
class vocals:public instrument{
public:
    vocals() :instrument("Singing", "hey hey"){}
    void play() const override{
        for (int i = 0; i < 12;i++){
            cout<<sounds<<endl;;
        }
        cout<<endl;
    }
};
class Orchestra{
private:
    vector<unique_ptr<instrument>>instruments;
    
public:
   
    void add_the_instrument(unique_ptr<instrument>instrument){
        instruments.push_back(std::move(instrument));
    }
    void play()const{
        cout<<"The orchestra have been playing or plays:"<<endl;
        for(const auto& instrument_ptr: instruments){
            instrument_ptr->play();
        }
        cout<<"========="<<endl;
        cout<<"trumpet:"<<"doot doot"<<endl;
        cout<<"violin:"<<"Wawa Wawa"<<endl;
        cout<<"flute:"<<"toot toot"<<endl;
        cout<<"piano:"<<"click click"<<endl;
        cout<<"vocals:"<<"hey hey"<<endl;
        cout<<"The performance has been completed!"<<endl;
    }
    size_t size() const{return instruments.size();}
    
};
int main(){
    Orchestra orchestra{};
    
    Orchestra().add_the_instrument(make_unique<trumpet>());
    Orchestra().add_the_instrument(make_unique<violin>());
    Orchestra().add_the_instrument(make_unique<piano>());
    Orchestra().add_the_instrument(make_unique<vocals>());
    
    cout<<"The orchestra has:"<<orchestra.size()<<" 5 instruments."<<endl;
    cout<<endl;
    
    Orchestra().play();
}
