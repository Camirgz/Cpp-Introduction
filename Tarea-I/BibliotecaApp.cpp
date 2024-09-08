#include <iostream>
#include <ctime>
#include <stdlib.h>
#define MAX_REGISTROS 100

using namespace std;

/*************** Modelo ***************/
class Libro{
  public:
    int codigo;
    string titulo;
    string autor;
    int anyo;
    
    Libro(){}
    Libro(int codigo, string titulo, string autor, int anyo);
};

Libro::Libro(int codigo, string titulo, string autor, int anyo){
    this->codigo = codigo;
    this->titulo = titulo;
    this->autor = autor;
    this->anyo = anyo;
}

class Estudiante{
  public:
    int carnet;
    string nombre;
    string apellidos;
    string correo;
    
    Estudiante(){}
    Estudiante(int carnet, string nombre, string apellidos, string correo);
};

Estudiante::Estudiante(int carnet, string nombre, string apellidos, string correo){
    this->carnet = carnet;
    this->nombre = nombre;
    this->apellidos = apellidos;
    this->correo = correo;
}

class Prestamo{
  public:
    int codLibro;
    int carnetEst;
    string fechaPrestamo;
    string estadoPrestamo;
    
    Prestamo(){}
    Prestamo(int codLibro, int carnetEst, string fechaPrestamo, string estadoPrestamo);
};

Prestamo::Prestamo(int codLibro, int carnetEst, string fechaPrestamo, string estadoPrestamo){
    this->codLibro = codLibro;
    this->carnetEst = carnetEst;
    this->fechaPrestamo = fechaPrestamo;
    this->estadoPrestamo = estadoPrestamo;
}

/*************** Controlador ***************/
class Controlador{
  public:
    static Libro libros[MAX_REGISTROS];
    static Estudiante estudiantes[MAX_REGISTROS];
    static Prestamo prestamos[MAX_REGISTROS];
    
    static int indiceLibros; // indice para la "tabla" de libros
    static int indiceEstudiantes; // indice para estudiantes
    static int indicePrestamos; // indice para prestamos
    
    static bool IngresarLibro(string titulo, string autor, int anyo);
    static bool IngresarEstudiante(string nombre, string apellidos, string correo);
    
    static bool RegistrarPrestamo(int codLibro, int carnetEst);
    
    static Libro LibroMasPrestado();
    static Estudiante EstudianteMasFiel();
};

Libro Controlador::libros[MAX_REGISTROS];
Estudiante Controlador::estudiantes[MAX_REGISTROS];
Prestamo Controlador::prestamos[MAX_REGISTROS];

int Controlador::indiceLibros = 0;
int Controlador::indiceEstudiantes = 0;
int Controlador::indicePrestamos = 0;

bool Controlador::IngresarLibro(string titulo, string autor, int anyo){
    if(Controlador::indiceLibros == MAX_REGISTROS){
        return false;
    }
    
    int nuevoCodigo = Controlador::indiceLibros + 1;
    Libro nuevoLibro = Libro(nuevoCodigo, titulo, autor, anyo);
    Controlador::libros[Controlador::indiceLibros] = nuevoLibro;
    Controlador::indiceLibros++;
    return true;
}

bool Controlador::IngresarEstudiante(string nombre, string apellidos, string correo){
    if(indiceEstudiantes == MAX_REGISTROS){
        return false;
    }
    
    int nuevoCarnet = indiceEstudiantes + 1;
    Estudiante nuevoEstudiante = Estudiante(nuevoCarnet, nombre, apellidos, correo);
    estudiantes[Controlador::indiceEstudiantes] = nuevoEstudiante;
    indiceEstudiantes++;
    return true;
}

bool Controlador::RegistrarPrestamo(int codLibro, int carnetEst){
    if(indicePrestamos == MAX_REGISTROS){
        return false;
    }
    
    // al menos validar que existan los datos
    bool existeLibro = false, existeEstudiante = false;
    
    for(int i = 0; i < indiceLibros; i++){
        if(libros[i].codigo == codLibro){
            existeLibro = true;
            break;
        }
    }
    if(!existeLibro){
        return false;
    }
    
    for(int i = 0; i < indiceEstudiantes; i++){
        if(estudiantes[i].carnet == carnetEst){
            existeEstudiante = true;
            break;
        }
    }   
    if(!existeEstudiante){
        return false;
    }
    
    //int nuevoCodigo = indicePrestamos + 1;
    time_t timestamp = time(&timestamp);
    struct tm* datetime = &(*localtime(&timestamp));
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", datetime);
    string fechaPrestamo(buffer);
    string estadoPrestamo = "Recien ingresado";
    
    Prestamo nuevoPrestamo = Prestamo(codLibro, carnetEst, fechaPrestamo, estadoPrestamo);
    prestamos[indicePrestamos] = nuevoPrestamo;
    indicePrestamos++;
    return true;
}

Libro Controlador::LibroMasPrestado(){
    int contador[MAX_REGISTROS];

    //recorrer la tabla de libros
    for(int i=0; i < indiceLibros; i++){
        contador[i] = 0;
    }

    //por cada prestamo, buscar el codigo en el arreglo de libros
    for(int i = 0; i < indicePrestamos; i++){
        Prestamo p = prestamos[i];

        for(int j = 0; j < indiceLibros; j++){

            if(p.codLibro == libros[j].codigo){
                //sumar al contador por cada libro cuando aparezca el codigo 
                contador[j]++;
                break;
            }
        }
    }

// averiguar el indice del maximo contador
    int maximo = 0;
    Libro libro;
    libro.codigo = -1;

    for(int i = 0; i < indiceLibros; i++){
    
        if(contador[i] > maximo){
            maximo = contador[i];
            libro = libros[i];
        }
    }

    return libro;
    
}

Estudiante Controlador::EstudianteMasFiel(){

    // inicializar contadores
    int contadores[MAX_REGISTROS];
    
    for(int i = 0; i < indiceEstudiantes; i++){
        contadores[i] = 0;
    }

    // recorrer la tabla de prestamos
    for(int i = 0; i < indicePrestamos; i++){
    
        Prestamo p = prestamos[i];
        
        // por cada prestamo, buscar el carnet en el arreglo de estudiantes
        for(int j = 0; j < indiceEstudiantes; j++){

            if(p.carnetEst == estudiantes[j].carnet){
                /* una vez que encontramos el carnet, aumentamos su contador y acabamos la busqueda actual */
                contadores[j]++;
                break;
            }
        }
    }

    // averiguar el indice del maximo contador
    int maximo = 0;
    Estudiante estudiante;
    estudiante.carnet = -1;

    for(int i = 0; i < indiceEstudiantes; i++){
    
        if(contadores[i] > maximo){
            maximo = contadores[i];
            estudiante = estudiantes[i];
        }
    }

    return estudiante;

}

/*************** Vista ***************/
class GUI{
    public:
      static void MenuPrincipal();
      
      static void MenuLibros();
      static void IngresarLibro();
      static void MostrarLibros();
      
      static void MenuEstudiantes();
      static void IngresarEstudiante();
      static void MostrarEstudiantes();
      
      static void MenuPrestamos();
      static void RegistrarPrestamo();
      static void MostrarPrestamos();
      
      static void MenuReportes();
      static void LibroMasPrestado();
      static void EstudianteMasFiel();
};

void GUI::MenuPrincipal(){
    while(true){
        system("cls"); // clear en Unix
        cout<<"Sistema de Prestamo"<<endl;
        cout<<"1. Libros"<<endl;
        cout<<"2. Estudiantes"<<endl;
        cout<<"3. Prestamos"<<endl;
        cout<<"4. Reportes"<<endl;
        cout<<"5. Salir"<<endl;
        
        int opcion = 0;
        cin>>opcion;
        cin.ignore(); // cuando leemos int, "borremos" la entrada
        
        if(opcion == 1){
            GUI::MenuLibros();
        }
        else if(opcion == 2){
            GUI::MenuEstudiantes();
        }
        else if(opcion == 3){
            GUI::MenuPrestamos();
        }
        else if(opcion == 4){
            GUI::MenuReportes();
        }
        else if(opcion == 5){
            break;
        }
    
    }   
}

void GUI::MenuLibros(){
    while(true){
        system("cls");
        cout<<"Sistema de Prestamo - Libros"<<endl;
        cout<<"1. Ingresar Libro"<<endl;
        cout<<"2. Mostrar Libros"<<endl;
        cout<<"3. Regresar"<<endl;
            
        int opcion = 0;
        cin>>opcion;
        cin.ignore();
        
        if(opcion == 1){
            GUI::IngresarLibro();
        }
        else if(opcion == 2){
            GUI::MostrarLibros();
        }
        else if(opcion == 3){
            break;
        }
    }
}

void GUI::IngresarLibro(){
    cout<<"Digite el titulo del libro"<<endl;
    string titulo;
    getline(cin, titulo, '\n');
    cout<<"Digite el autor del libro"<<endl;
    string autor;
    getline(cin, autor, '\n');
    cout<<"Digite el anyo del libro"<<endl;
    int anyo;
    cin>>anyo;
    cin.ignore();
    
    bool respuesta = Controlador::IngresarLibro(titulo, autor, anyo);
    
    cout<<"Resultado del ingreso: "<<respuesta<<endl;
    system("pause");
}

void GUI::MostrarLibros(){
    system("cls");
    for(int i = 0; i < Controlador::indiceLibros; i++){
        Libro c = Controlador::libros[i];
        cout<<"Codigo: "<<c.codigo;
        cout<<", titulo: "<<c.titulo;
        cout<<", autor: "<<c.autor;
        cout<<", anyo: "<<c.anyo<<endl;
    }
    system("pause");
}

void GUI::MenuEstudiantes(){
    while(true){
        system("cls");
        cout<<"Sistema de Prestamo - Estudiantes"<<endl;
        cout<<"1. Ingresar Estudiante"<<endl;
        cout<<"2. Mostrar Estudiantes"<<endl;
        cout<<"3. Regresar"<<endl;
            
        int opcion = 0;
        cin>>opcion;
        cin.ignore();
        
        if(opcion == 1){
            GUI::IngresarEstudiante();
        }
        else if(opcion == 2){
            GUI::MostrarEstudiantes();
        }
        else if(opcion == 3){
            break;
        }
    }
}

void GUI::IngresarEstudiante(){
    cout<<"Digite el nombre del Estudiante"<<endl;
    string nombre;
    getline(cin, nombre, '\n');
    cout<<"Digite los apellidos del Estudiante"<<endl;
    string apellidos;
    getline(cin, apellidos, '\n');
    cout<<"Digite el correo del Estudiante"<<endl;
    string correo;
    getline(cin, correo, '\n');
    
    bool respuesta = Controlador::IngresarEstudiante(nombre, apellidos, correo);
    
    cout<<"Resultado del ingreso: "<<respuesta<<endl;
    system("pause");
}

void GUI::MostrarEstudiantes(){
    system("cls");
    for(int i = 0; i < Controlador::indiceEstudiantes; i++){
        Estudiante e = Controlador::estudiantes[i];
        cout<<"Carnet: "<<e.carnet;
        cout<<", nombre: "<<e.nombre;
        cout<<", apellidos: "<<e.apellidos;
        cout<<", correo: "<<e.correo<<endl;
    }
    system("pause");
}

void GUI::MenuPrestamos(){
    while(true){
        system("cls");
        cout<<"Sistema de Prestamo - Prestamos"<<endl;
        cout<<"1. Registrar Prestamo"<<endl;
        cout<<"2. Mostrar Prestamos"<<endl;
        cout<<"3. Regresar"<<endl;
            
        int opcion = 0;
        cin>>opcion;
        cin.ignore();
        
        if(opcion == 1){
            GUI::RegistrarPrestamo();
        }
        else if(opcion == 2){
            GUI::MostrarPrestamos();
        }
        else if(opcion == 3){
            break;
        }
    }
}

void GUI::RegistrarPrestamo(){
    cout<<"Digite el codigo del Libro"<<endl;
    int codLibro;
    cin>>codLibro;
    cin.ignore();
    cout<<"Digite el carnet del Estudiante"<<endl;
    int carnetEst;
    cin>>carnetEst;
    cin.ignore();
    
    bool respuesta = Controlador::RegistrarPrestamo(codLibro, carnetEst);
    
    cout<<"Resultado del registro: "<<respuesta<<endl;
    system("pause");
}

void GUI::MostrarPrestamos(){
    system("cls");
    for(int i = 0; i < Controlador::indicePrestamos; i++){
        Prestamo p = Controlador::prestamos[i];
        cout<<"Codigo Libro: "<<p.codLibro;
        cout<<", Carnet Estudiante: "<<p.carnetEst;
        cout<<", fecha prestamo: "<<p.fechaPrestamo;
        cout<<", estado prestamo: "<<p.estadoPrestamo<<endl;
    }
    system("pause");
}

void GUI::MenuReportes(){
    while(true){
        system("cls");
        cout<<"Sistema de Prestamo - Reportes"<<endl;
        cout<<"1. Estudiante mas fiel"<<endl;
        cout<<"2. Libro mas prestado"<<endl;
        cout<<"3. Regresar"<<endl;
            
        int opcion = 0;
        cin>>opcion;
        cin.ignore();
        
        if(opcion == 1){
            GUI::EstudianteMasFiel();
        }
        else if(opcion == 2){
            GUI::LibroMasPrestado();
        }
        else if(opcion == 3){
            break;
        }
    }
}

void GUI::EstudianteMasFiel(){
    system("cls");
    Estudiante e = Controlador::EstudianteMasFiel();
    
    cout<<"Carnet: "<<e.carnet;
    cout<<", nombre: "<<e.nombre;
    cout<<", apellidos: "<<e.apellidos;
    cout<<", correo: "<<e.correo<<endl;
        
    system("pause");
}

void GUI::LibroMasPrestado(){
    system("cls");
    Libro l = Controlador::LibroMasPrestado();

    cout<<"Codigo: "<<l.codigo;
    cout<<", Titulo: "<<l.titulo;
    cout<<", Autor: "<<l.autor;
    cout<<", Año: "<<l.anyo;

    system("pause");
}

int main(){ 
    GUI::MenuPrincipal();   
    return 0;   
}



