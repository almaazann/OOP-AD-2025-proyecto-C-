#include <iostream>
#include <string>
#include <vector>
#include<memory>
#include <cstring>
#include <stdexcept>
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

    virtual void mostrar_info() const = 0;
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
        cout << "Nombre: " << name << endl;
        cout << "Area: " << work << endl;
        cout << "Especialidad: " << specific << endl;
    }

    void mostrar_info () const override{
        cout << "DOCTOR: " << endl; 
        info_doctor();
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
    
    //Getter

    string getEspecialidad() const{
        return specific;
    }
};

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

    Expediente(const char* h, string es, Doctor* d) : Estado_salud(es), miDoc(d){
        allocCopy(h, strlen(h));
        cout << "Expediente incializado" << endl;
    }

    Expediente() : Estado_salud("Estable"), miDoc(nullptr){
        allocCopy("Sin historial", strlen("Sin historial"));
        cout << "Expediente inicizializado" << endl;
    }

    void show_info(){
        cout << "Su estado de salud es: " << Estado_salud << endl;
        if(miDoc) miDoc->info_doctor();
        cout << "Con un historial de: " << historial << endl;
    }
    
    //Non-default destructor
    ~Expediente(){
        cout << "Expediente terminado" << endl;
        delete[] historial;
    }

    //Copy constructor
    Expediente(const Expediente& other){
        Estado_salud = other.Estado_salud;
        miDoc = other.miDoc;
        allocCopy(other.historial, other.len);
    }

    //Copy assignment
    Expediente& operator=(const Expediente& rhs){
        if(this== &rhs) return *this;
        delete[] historial;
        allocCopy(rhs.historial, rhs.len);
        Estado_salud = rhs.Estado_salud;
        miDoc = rhs.miDoc;
        return *this;
    }

    void show_info() const{
        cout<<"Estado de salud: "<<Estado_salud<<endl;
        if(miDoc){
            cout<<"Doctor asignado:"<<endl;
            miDoc->info_doctor();
        }
        cout<<"Historial: "<<historial<<endl;
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

    void mostrar_info() const{
        cout << "Paciente de nombre: " << nombre << endl;
        cout << "Con edad de: " << edad << " años" << endl;
        cout << "ID de: " << id << endl;
        miExpediente.show_info();
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

    void mostrar_info() const override{
        cout<<"\nRecepcionista: "<<endl;
        cout<<"Nombre: "<<name<<endl;
        cout<<"Area: "<<work<<endl;
        cout<<"Turno: "<<turno<<endl;
    }
    
    void registrar_paciente(const Paciente& p){
        cout << "Paciente: " << endl;
        p.mostrar_info();
        cout << "Registrado";
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
        os << "Cita programada para: " <<  c.fecha <<endl; //It can break, in case miDoc == nullptr, so we use an If
        if(c.miDoc) c.miDoc->info_doctor();
        return os;
    }

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
            p->mostrar_info();
            cout << endl;
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

    auto doc1 = make_unique<Doctor>(101,"Juan Perez","Medicina","cardiologo");
    auto doc2 = make_unique<Doctor>(102,"Pedro Ramirez","Cirugia","cirujano");
    auto doc3 = make_unique<Doctor>(103,"Luis Garcia","Consulta","General");
    auto rec1 = make_unique<Recepcionista>(201,"Maria Lopez","Recepcion","Matutino");

    Doctor* cardio = doc1.get();
    Doctor* cirujano = doc2.get();
    Doctor* general = doc3.get();
    Recepcionista* recepcion = rec1.get();

    miClinica.agregarPersonal(move(doc1));
    miClinica.agregarPersonal(move(doc2));
    miClinica.agregarPersonal(move(doc3));
    miClinica.agregarPersonal(move(rec1));

    Medicamento medGeneral("Paracetamol","para dolor","Analgesico");

    Medicamento medCardio("Aspirina","para el corazon","Cardiologico");

    Medicamento medCirugia("Antibiotico","postoperatorio","Quirurgico");

    cout << "===================================" << endl;
    cout << "BIENVENIDO A LA CLINICA" << endl;
    cout << "===================================" << endl;

    string nombre;
    int edad;
    int gravedad;

    cout << "Ingrese su nombre: ";
    getline(cin,nombre);
    while(true){
        try{
            cout << "Ingrese su edad: ";
            cin >> edad;
            if(edad < 0){
                throw invalid_argument("La edad no puede ser negativa");
            }
            break;
        }
        catch(const invalid_argument& e){
            cout << "\nERROR: "
                 << e.what()
                 << endl;
        }
    }
    while(true){
        try{
            cout << "\nNivel de gravedad:" << endl;
            cout << "1. Leve" << endl;
            cout << "2. Moderado" << endl;
            cout << "3. Grave" << endl;
            cout << "Seleccione: ";
            cin >> gravedad;
            if(gravedad < 1 || gravedad > 3){
                throw invalid_argument("Debe ingresar 1, 2 o 3");
            }
            break;
        }
        catch(const invalid_argument& e){
            cout << "\nERROR: "
                 << e.what()
                 << endl;
        }
    }

    Doctor* doctorAsignado;

    if(gravedad == 1){
        doctorAsignado = general;
    }
    else if(gravedad == 2){
        doctorAsignado = cardio;
    }
    else{
        doctorAsignado = cirujano;
    }

    Expediente exp("Sin historial previo","Estable",doctorAsignado);

    Paciente paciente(edad,5001,nombre,exp);
    
    recepcion->registrar_paciente(paciente);
    miClinica.agregarPaciente(paciente);

    bool continuar = true;

    while(continuar){

        int opcion;

        cout << "\n===================================" << endl;
        cout << "MENU DEL PACIENTE" << endl;
        cout << "===================================" << endl;
        cout << "1. Ver mi informacion" << endl;
        cout << "2. Saber quien es mi doctor" << endl;
        cout << "3. Ver personal de la clinica" << endl;
        cout << "4. Agendar una cita" << endl;
        cout << "5. Iniciar tratamiento" << endl;
        cout << "6. Ver informacion del medicamento" << endl;
        cout << "7. Ver pacientes registrados" << endl;
        cout << "8. Ver citas programadas" << endl;
        cout << "9. Darme de alta" << endl;
        cout << "10. Salir" << endl;
        cout << "\nSeleccione: ";

        if(!(cin >> opcion)){

            cin.clear();
            cin.ignore(10000,'\n');
            cout << "\nIngrese un numero valido.\n";
            continue;
        }
        try{
            switch(opcion){
                case 1:
                    paciente.mostrar_info();
                    break;
                case 2:
                    cout << "\nSu doctor asignado es:\n" << endl;
                    doctorAsignado->info_doctor();
                    break;
                case 3:
                    miClinica.mostrarPersonal();
                    break;
                case 4:{
                    string fecha;
                    cin.ignore();
                    cout << "Ingrese fecha de la cita: ";
                    getline(cin,fecha);
                    Cita nuevaCita(fecha,doctorAsignado);
                    miClinica.agregarCita(nuevaCita);
                    cout << "\nCita registrada correctamente\n" << endl;
                    break;
                }
                case 5:
                    doctorAsignado->tratar_paciente();
                    if(gravedad == 1){
                        doctorAsignado->medicar(medGeneral);
                    }
                    else if(gravedad == 2){
                        doctorAsignado->medicar(medCardio);
                    }
                    else{
                        doctorAsignado->medicar(medCirugia);
                    }
                    break;
                case 6:
                    cout << "\nMedicamento asignado:\n" << endl;
                    if(gravedad == 1){
                        medGeneral.tratamiento();
                    }
                    else if(gravedad == 2){
                        medCardio.tratamiento();
                    }
                    else{
                        medCirugia.tratamiento();
                    }
                    break;
                case 7:
                    miClinica.mostrarPacientes();
                    break;
                case 8:
                    miClinica.mostrarCitas();
                    break;
                case 9:
                    cout << "\nPaciente dado de alta.\n" << endl;
                    continuar = false;
                    break;
                case 10:
                    continuar = false;
                    break;
                default:
                    throw invalid_argument("Opcion no disponible");
            }
        }
        catch(const invalid_argument& e){
            cout << "\nERROR: "
                 << e.what()
                 << endl;
        }
    }
    cout << "\nGracias por atenderse en la clinica.\n" << endl;

    return 0;
}