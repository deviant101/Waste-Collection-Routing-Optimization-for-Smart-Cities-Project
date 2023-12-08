#pragma once
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class Driver{
    public:
        string Name;
        string Truck_no;
        string ID;
        string Password;
        bool collection_status;
        int *BinLevels;
        vector<string> routeLocations;
        vector<int> routeIndexes;
        vector<int> routeTime;
        time_t starting_time;
        vector<time_t> collectionTimes;
        vector<string> collectedBins;


        Driver():collection_status(false) {}

        void checkCollectionStatus(){
            if(collection_status)
                cout<<"\nYour Truck is Selected by Controller to Collect Bins\n\n";
            else
                cout<<"\nHurray!! No Duty Alloted Yet\n\n";
        }

        void viewCollectionRoute(){

            if(!routeLocations.empty()){
                int i = 0;
                for(i; i<routeLocations.size()-1; ++i)
                    cout<<" ( "<<routeLocations[i]<<" ) "<<"->";
                cout<<" ( "<<routeLocations[i]<<" ) "<<endl;
            }
            else
                cout<<"\nNo Route Alloted\n"<<endl;
        }

        void startCollecting(){
            cout<<"\nStarted Bin Collection\n"<<endl;
            starting_time = time(nullptr);
        }

        void ViewLive() {
            time_t current_time = time(nullptr);
            time_t temp_starting_time = starting_time;

            while (!routeTime.empty()){
                if (temp_starting_time + routeTime[0] <= current_time){
                    collectionTimes.push_back(temp_starting_time + routeTime[0]);
                    collectedBins.push_back(routeLocations[0]);
                    routeTime.erase(routeTime.begin());
                    routeLocations.erase(routeLocations.begin());

                    starting_time = temp_starting_time + routeTime[0];

                }
                else
                    break;

                temp_starting_time += routeTime[0];  // Update temp_starting_time for the next iteration
            }

            for (size_t i = 0; i < collectionTimes.size(); ++i){        //collected
                struct tm* local_time = localtime(&collectionTimes[i]);
                cout << collectedBins[i] << " Bin Collected at " << local_time->tm_min << ":" << local_time->tm_sec << endl;
            }
            cout<<"\nRemaining Bins\n";
            for(int i=0; i<routeLocations.size(); ++i){         //remaining
                cout<<routeLocations[i]<<endl;
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