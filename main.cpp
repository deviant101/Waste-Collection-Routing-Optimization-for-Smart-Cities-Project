#include <iostream>
#include <string>
#include <fstream>
#include "Truck-Driver.cpp"
#include "Controller.cpp"
#include "Graph.cpp"
using namespace std;

void read_driver_data(fstream &file, Driver Drivers[5]);

int main(){
//----------------------------------------------------------------//Drivers Data
    Driver drivers[6];
    fstream driversFile;
    driversFile.open("Truck-Drivers-Data.csv",ios::in);
    read_driver_data(driversFile,drivers);
    driversFile.close();

//----------------------------------------------------------------//Graphs
    Graph graphs[6];
    graphs[1].make_graph("Area_1.csv");
    graphs[2].make_graph("Area_2.csv");
    graphs[3].make_graph("Area_3.csv");
    graphs[4].make_graph("Area_4.csv");
    graphs[5].make_graph("Area_5.csv");
    // graphs[0].findShortestPath(1,12);
    // graph[1].Display_Graph();

//----------------------------------------------------------------//Controller
    Controller controller(drivers,graphs);
//------------------Simulation----------------------//
    while(1){
        int choice;
        cout<<"\n--------------[SIMULATION MENU]--------------\n\n";
        cout<<"1 - Login as Controller"<<endl
            <<"2 - Login as Truck Driver"<<endl
            <<"3 - Exit"<<endl;
        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore();
        cout<<endl;
        if(choice==1){
            controller.Login();
        }
        else if(choice==2){
            controller.driverLogin();
        }
        else if(choice==3){
            break;
        }
        else{
            cout<<"\nInvalid! Try again."<<"\n\n";
        }
    }

    return 0;
}

void read_driver_data(fstream &file, Driver Drivers[5]){

    string line="";
    getline(file,line);

    for(int driver_no=1; driver_no<=5; driver_no++){
        line="";
        getline(file,line);
        // cout<<line<<endl;
        string sub_part="";
        int comma_count = 0;
        for(int i=0; i<line.length(); i++){
            if(line[i]!=',' && i!=line.length()-1)  //giving extra
                sub_part+=line[i];
            else{
                if(comma_count==0){
                    Drivers[driver_no].Name=sub_part;
                }
                else if(comma_count==1){
                    Drivers[driver_no].Truck_no=sub_part;
                }
                else if(comma_count==2){
                    Drivers[driver_no].ID=sub_part;
                }
                else if(comma_count==3){
                    Drivers[driver_no].Password=sub_part;
                }
                sub_part="";
                ++comma_count;
            }
        }
    }
}