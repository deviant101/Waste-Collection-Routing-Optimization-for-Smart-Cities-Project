#include <iostream>
using namespace std;

class Driver{
    public:
        string Name;
        string Truck_no;
        string ID;
        string Password;
        bool collection_status;

    void Profile(){
        cout<<"\n--------------[Driver Profile]--------------\n";
        cout<<"NAME: "<<Name<<endl
            <<"Truck_no: "<<Truck_no<<endl
            <<"ID: "<<ID<<endl
            <<"Password: "<<Password<<endl;
        cout<<"--------------------------------------------\n";
    }
};