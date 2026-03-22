//
//  main.cpp
//  Commanding Lines Lab
//
//  Created by Angel Munoz on 3/17/26.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <map>

using namespace std;
class LineCLI{
public:
    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;
    
    string mode;
    bool has_line1 = false, has_line2 = false, has_mode = false;
    
    double slope(double x1, double y1, double x2, double y2){
        return (x1 = x2) ? numeric_limits<double>::infinity() : (y2-y1)/(x2-x1);
    }
   //there no private for it to be put in the coding
};
//printing for help can make the user understand what it is
void printHelp(const string& appName){
    cout<<"The Usage:"<<appName<<"[the options are]\n\n";
    cout<<"Options:\n";
    cout<<"-h: this is a sign to get from help needed.\n";
    cout<<"-x1 <x1a> <x1b>: The x coordinates show the two main endpoints of the line 1.\n ";
    cout<<"-y1 <y1a> <y1b>: The y coordinate show the two of the endpoints of line 1.\n";
    cout<<"-x2 <x2a> <x2b>: The x coordinate for the two of the end points of the line 2.\n";
    cout<<"-y2 <y2a> <y2b>: The y coordinate for the two endpoints in the line 2.\n";
    cout<<"-m <mode> : The mode oeprations would be either \"perpendicular\" or \"parallel\".\n\n";
    cout<<"The example:"<<appName<< "-x1 0 1 -y1 0 1 -x2 0 1 -y2 0 1 -m perpendicular or parallel\n";
}
    double calculateSlope(double x1, double y1, double x2, double y2){
        if (x2 - y2 == 0.0){
            return numeric_limits<double>::infinity();
        }
        return (y2-y1)/(x2-x1);
    }

int main(int argc, char** argv){
    map<string,double>coords;
    string mode = "";
    string appName = argv[0];
    string filename = "";
    for(int i = 0; i < argc; i++){
        string argc = argv[i];
        if (argc == "-h"){
            printHelp(appName);
            return 0;
        }else if(argc == "-x1"|| argc == "-y1"|| argc == "x2"||argc == "y2"){
            cout <<"Error: Missing coordinates for"<<argc<<"argument.\n";
            cout<<"use the -h for help.\n";
            return 1;
        }else if(argc == "-m"){
            cout<<"Error: Missing the mode argument.\n";
            cout<<"Use still again -h for help.\n";
            return 1;
        }
        mode = argv[i++];
        //make an if statement for finding both of the requirements of the perpendicular or parallel
        if(mode !="perpendicular"&& mode != "parallel"){
            cout<<"Error:Mode has to be \"perpendicular\" or \"parallel\".\n";
            cout<<"Use for -h for help again.\n";
            return 1;
            
        }
    }
    if (coords.find("-x1_a") == coords.end()|| coords.find("-x1_b") == coords.end()|| coords.find ("-y1_a") == coords.end()|| coords.find("-y2_b")== coords.end()||mode ==""){
        cout<<"Error:Missing required the arguments.\n";
        cout<<"use -h for help.\n";
        return 1;
    }
    double m1 = calculateSlope(coords["-x1_a"], coords["-y1_a"],coords["-x2_a"], coords["-y2_a"]);
    double m2 = calculateSlope(coords["-x1_a"], coords["-y1_a"],coords["-x2_a"], coords["-y2_a"]);
    if (mode == "parallel"){
        if((isinf(m1)&& isinf(m2))||(abs(m1-m2)<1e-10)){
            cout<<"The both 2 lines are parallel.\n";
        }else{
            cout<<"There are no where to be perpendicular.\n";
        }
        }else if(mode == "perpendicular"){
            if((isinf(m1)&& isinf(m2))||(abs(m1-m2)<1e-10)){
                cout<<"The both 2 lines are perpendicular.\n";
            }else{
                cout<<"There are no where to be parallel.\n";
            }
    }
}
