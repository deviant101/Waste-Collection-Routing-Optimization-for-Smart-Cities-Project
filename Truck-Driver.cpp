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
        vector<int> routeIndexes;
        vector<int> routeTime;


        Driver():collection_status(false) {}

        void checkCollectionStatus(){
            if(collection_status)
                cout<<"\nYour Truck is Selected by Controller to Collect Bins\n\n";
            else
                cout<<"\nHurray!! No Duty Alloted Yet\n\n";
        }

        void viewCollectionRoute(){

            int i = 0;
            for(i; i<routeLocations.size()-1; ++i)
                cout<<" ( "<<routeLocations[i]<<" ) "<<"->";
            cout<<" ( "<<routeLocations[i]<<" ) "<<endl;

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