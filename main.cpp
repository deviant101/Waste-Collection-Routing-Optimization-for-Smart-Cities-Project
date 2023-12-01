#include <iostream>
#include <string>
#include <fstream>
#include "Truck-Driver.cpp"
using namespace std;

void read_driver_data(fstream &file, Driver Drivers[5]);

int main(){

    Driver drivers[5];
    fstream driversFile;
    driversFile.open("Truck-Drivers-Data.csv",ios::in);
    read_driver_data(driversFile,drivers);
    driversFile.close();

    

    for(int i=0; i<5; ++i)
        drivers[i].Display();

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
