#include <iostream>
#include <string>
#include <vector>
#include<memory>
#include <cstring>
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

class Expediente{
    public: 
    char* historial;
    size_t len;
    string Estado_salud;
    Doctor* miDoc;

    void allocCopy(const char* h, size_t n){
        historial = new char[n + 1];
        memcpy(historial, h, n + 1);
        len = n;
    }

    Expediente(char* h, string es, Doctor* d) : Estado_salud(es), miDoc(d){
        allocCopy(h, strlen(h));
        cout << "Expediente incializado" << endl;
    }

    Expediente() : Estado_salud("Estable"), miDoc(nullptr){
        allocCopy("N", strlen("N"));
        cout << "Expediente inicizializado" << endl;
    }

    void show_info(){
        cout << "Su estado de salud es: " << Estado_salud << endl;
        miDoc->info_doctor();
        cout << "Con un historial de: " << historial << endl;
    }

    ~Expediente(){
        cout << "Expediente terminado" << endl;
        delete[] historial;
    }

    Expediente(const Expediente& other){
        Estado_salud = other.Estado_salud;
        miDoc = other.miDoc;
        allocCopy(other.historial, other.len);
    }

    Expediente& operator=(const Expediente& rhs){
        if(this== &rhs) return *this;
        delete[] historial;
        allocCopy(rhs.historial, rhs.len);
        Estado_salud = rhs.Estado_salud;
        miDoc = rhs.miDoc;
        return *this;
    }
};

class Paciente{
    private:
    int edad;
    int id;
    string nombre;
    Expediente miExpediente;

    public:

    Paciente(int e, int i, string n, const Expediente& miex) : edad(e), id(i), nombre(n), miExpediente(miex){
        cout << "Paciente registrado" << endl;
    }

    Paciente() : edad(0), id(1234), nombre("Regular dude"), miExpediente(){
        cout << "Paciente registrado" << endl;
    }

    ~Paciente(){
        cout << "Paciente dado de alta" << endl;
    }

    void mostrar_info(){
        cout << "Paciente de nombre: " << nombre << endl;
        cout << "Con edad de: " << edad << " años" << endl;
        cout << "ID de: " << id << endl;
        miExpediente.show_info();
    }

};

class Clinica{
private:
    vector<unique_ptr<Personal>> personal;
    vector<Paciente> pacientes;
    vector<Cita> citas;

public:

    Clinica(){
        cout << "Clinica abierta" << endl;
    }

    ~Clinica(){
        cout << "Clinica cerrada" << endl;
    }

    void agregarPersonal(unique_ptr<Personal> p){
        personal.push_back(move(p));
    }

    void agregarPaciente(const Paciente& p){
        pacientes.push_back(p);
    }

    void agregarCita(const Cita& c){
        citas.push_back(c);
    }

    void mostrarPersonal() const{
        cout << "\nEl personal es: \n";

        for(const auto& p : personal){
            p->tratar_paciente();
        }
    }

    void mostrarCitas() const{
        cout << "\nLas citas son: \n";

        for(const auto& c : citas){
            cout << c << endl;
        }
    }

    void mostrarPacientes(){
        cout << "\nActualmente los pacientes son: \n";

        for(auto& p : pacientes){
            p.mostrar_info();
            cout << endl;
        }
    }
};

int main(){

    Clinica miClinica;

    auto doc1 = make_unique<Doctor>(
        101,
        "Juan Perez",
        "Medicina",
        "cardiologo"
    );

    auto rec1 = make_unique<Recepcionista>(
        201,
        "Maria Lopez",
        "Recepcion",
        "Matutino"
    );

    Doctor* ptrDoc = doc1.get();

    miClinica.agregarPersonal(move(doc1));
    miClinica.agregarPersonal(move(rec1));


    Expediente exp1(
        (char*)"Hipertension",
        "Estable",
        ptrDoc
    );

    Paciente pac1(
        45,
        5001,
        "Carlos Ruiz",
        exp1
    );

    miClinica.agregarPaciente(pac1);

    Cita cita1(
        "20/06/2026 10:00",
        ptrDoc
    );

    miClinica.agregarCita(cita1);

    cout << "\n=========================\n";

    ptrDoc->tratar_paciente();

    cout << "\n=========================\n";

    miClinica.mostrarPacientes();

    cout << "\n=========================\n";

    miClinica.mostrarCitas();

    cout << "\n=========================\n";

    miClinica.mostrarPersonal();

    return 0;
}