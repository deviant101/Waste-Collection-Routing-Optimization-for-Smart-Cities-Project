#include <iostream>
#include <string>
using namespace std;

class Controller{
    public:
        string Name;
        string ID;
        string Password;
    
    Controller(string name="Dennis", string id="CRL-1094", string password="cont_41siml"):Name(name), ID(id), Password(password) {}

    void Profile(){
        cout<<"\n--------------[Controller Profile]--------------\n";
        cout<<"NAME: "<<Name<<endl
            <<"ID: "<<ID<<endl
            <<"Password: "<<Password<<endl;
        cout<<"------------------------------------------------\n";
    }

};