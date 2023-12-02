#include <iostream>
#include <string>
#include <fstream>
#include "Truck-Driver.cpp"
#include "Controller.cpp"
#include "Graph.cpp"
using namespace std;

void read_driver_data(fstream &file, Driver Drivers[5]);
void read_bin_data(fstream &binFile,int binsHourlyData[72]);

int main(){
//----------------------------------------------------------------//Drivers Data
    Driver drivers[5];
    fstream driversFile;
    driversFile.open("Truck-Drivers-Data.csv",ios::in);
    read_driver_data(driversFile,drivers);
    driversFile.close();

    for(int i=0; i<5; ++i)
        drivers[i].Profile();
//----------------------------------------------------------------//Bin Fill Levels Data
    int binsHourlyData[72];
    fstream binFile;
    binFile.open("Bin-Data.csv",ios::in);
    read_bin_data(binFile,binsHourlyData);
    binFile.close();

    for(int i=0; i<72; ++i)
        cout<<i<<" - "<<binsHourlyData[i]<<endl;
//----------------------------------------------------------------//Controller
    Controller controller;
    controller.Profile();
//----------------------------------------------------------------Locations(Vertices)
    
    Graph graph1;
    graph1.make_graph("Vertices.csv");
    graph1.Display_Graph();
    

    return 0;
}

void read_driver_data(fstream &file, Driver Drivers[5]){

    string line="";
    getline(file,line);

    for(int driver_no=0; driver_no<5; driver_no++){
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

void read_bin_data(fstream &file,int binsData[72]){

    for(int i=0; i<72; i++){
        
        string percent;
        getline(file,percent);
        binsData[i]=stoi(percent);
    }
}
