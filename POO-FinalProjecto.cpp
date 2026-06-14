#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Personal{
    protected:
    int ID;
    string name;
    string work;
    
    public:
    Personal(int id_, string n, string pt) : ID(id_), name(n), work(pt){
        cout << "Personal Creado" << endl;
    }

    Personal() : ID(0), name("####"), work("####"){
        cout << "Personal Creado" << endl;
    }

    virtual ~Personal(){
        cout << "Personal Destruido" << endl;
    }

    virtual void tratar_paciente() const = 0;
};

class Doctor: public Personal{
    private:
    string specific;
    public:

    Doctor(int id_, string n, string pt, string sp) : Personal(id_, n, pt), specific(sp){
        cout << "Doctor construido" << endl;
    }

    Doctor() : specific("General doctor"){
        cout << "Doctor construido" << endl;
    }

    ~Doctor(){
        cout << "Doctor destruido" << endl;
    }
    
};