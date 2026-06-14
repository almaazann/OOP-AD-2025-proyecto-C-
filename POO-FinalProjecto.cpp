#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Medicamento{
    private:
    string tipo;
    string estilo;
    public:
    string nombre;

    Medicamento(string nombre_, string tipo_, string estilo_): nombre(nombre_), tipo(tipo_), estilo(estilo_){}

    Medicamento(): nombre("paracetamol"), tipo("para: NADA"), estilo("no sabemos"){}

    ~Medicamento(){
        cout << "TRATAMIENTO TERMINADO" << endl;
    }

    void tratamiento() const{
        cout << "TRATAMIENTO EMPEZADO" << endl;
        cout << "Medicamento usado: " << nombre << "\nRecomendado " << tipo << "\nDel tipo" << estilo << endl;
    }
};

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

    Doctor() : Personal(), specific("General"){
        cout << "Doctor construido" << endl;
    }

    ~Doctor() override{
        cout << "Doctor destruido" << endl;
    }
    void info_doctor() const{
        cout << name << endl;
        cout << work << endl;
        cout << specific << endl;
    }

    void tratar_paciente() const override{
        if(specific  == "cirujano"){
            cout << "Te operaré" << endl;
        }
        else if(specific == "cardiologo"){
            cout << "Te atenderé" << endl;
        }
        else if(specific == "pediatra"){
            cout << "Te curaré" << endl;
        }
        else if(specific == "General"){
            cout << "Te trataré" << endl;
        }
        else{cout << "No te podemos atender"<< endl; }
    }    

    void medicar(const Medicamento& m){
        cout << "Te trataré con: "<< endl;
        m.tratamiento();
    }
};

class Recepcionista: public Personal{
    private:
    string turno;
    public:

    Recepcionista(int id_, string n, string pt, string t) : Personal(id_, n, pt), turno(t){
        cout << "Recepcionista creado" << endl;
    }
    Recepcionista() : Personal(), turno("No disponible"){
        cout << "Recepcionista creado " << endl ;
    }

    ~Recepcionista() override{
        cout << "Recepcionista destruido" << endl;
    }
    
    void tratar_paciente() const override{
        cout <<"Enseguida se le asignará una cita" << endl;
    }
};

class Cita{
    public:
    string fecha;
    Doctor* miDoc;
    //Paciente* miPac;

    Cita(string f, Doctor* d) : fecha(f), miDoc(d){
        cout << "Cita creada" << endl;
    }

    Cita() : fecha("sin fecha"), miDoc(nullptr){
        cout << "Cita creada" << endl;
    }

    ~Cita(){
        cout << "Cita terminada" << endl;
    }
};

ostream& operator<<(ostream& os, const Cita& c){
        os << "Cita programada para: " <<  c.fecha <<"\nCon el doctor: " <<endl;
        c.miDoc->info_doctor();
        return os;
    }

