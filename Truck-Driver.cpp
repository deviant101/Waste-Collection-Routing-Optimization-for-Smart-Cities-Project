#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Driver{
    public:
        string Name;
        string Truck_no;
        string ID;
        string Password;
        bool collection_status;
        vector<string> routeLocations;

        Driver():collection_status(false) {}

        void checkCollectionStatus(){
            if(collection_status)
                cout<<"\nYour Truck is Selected by Controller to Collect Bins\n\n";
            else
                cout<<"\nHurray!! No Duty Alloted Yet\n\n";
        }

        void viewCollectionRoute(){

            for(int i=0; i<routeLocations.size(); ++i){
                
            }

        }

        void Profile(){
            cout<<"\n--------------[Driver Profile]--------------\n";
            cout<<"NAME: "<<Name<<endl
                <<"Truck_no: "<<Truck_no<<endl
                <<"ID: "<<ID<<endl
                <<"Password: "<<Password<<endl;
            cout<<"--------------------------------------------\n";
        }
};