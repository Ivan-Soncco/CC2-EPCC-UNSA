#include <iostream>
#include <string>

class Personaje{
    private:
       Personaje *lista;
       std::string nombre;
       int edad;
       float altura;
       char sexo; 
       int size;
    public:
        Personaje();
        Personaje(std::string, int, float, char);
        ~Personaje();
        void push_back(std::string, int, float, char);
        void mostrar();
};

Personaje::Personaje(){
    lista=nullptr;
    size=0;
}

Personaje::~Personaje(){
    delete[] lista;
}
Personaje::Personaje(std::string _nombre,int _edad,float _altura,char _sexo){
    size=1;
    lista=new Personaje[1];
    
    lista[0].nombre=_nombre;
    lista[0].edad=_edad;
    lista[0].altura=_altura;
    lista[0].sexo=_sexo;
}
void Personaje::push_back(std::string _nombre,int _edad,float _altura,char _sexo){
    Personaje *aux=new Personaje[size+1];
    for(int i=0;i<size;i++){
        aux[i]=lista[i];
    }
    aux[size].nombre=_nombre;
    aux[size].edad=_edad;
    aux[size].altura=_altura;
    aux[size].sexo=_sexo;
    delete[] lista;
    lista=aux;
    size++;
}

void Personaje::mostrar(){
    for(int i=0;i<size;i++){
        std::cout<<"Personaje: "<<lista[i].nombre<<"\t"
             <<"Edad: "<<lista[i].edad<<"\t"
             <<"Altura: "<<lista[i].altura<<"\t"
             <<"Sexo: "<<lista[i].sexo<<"\t\n";

    }
    
}

int main(){
    Personaje p1;
    p1.mostrar();
    Personaje p2("Mario", 24, 1.55,'M');
    p2.mostrar();
    p2.push_back("Peach", 32,1.80,'F');
    p2.mostrar();
    return 0;
}
