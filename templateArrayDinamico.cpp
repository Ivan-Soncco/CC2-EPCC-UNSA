#include <iostream>

template <typename T>
class ArrayDinamico{
    private:
        T *a;
        int size=0;
    public:
    ArrayDinamico(){a= new int[size];};
    ArrayDinamico(int cantidad);
    void push_back(T valor);
    void mostrar();
    void ingresar(T valor, int posicion);
    void eliminar(int posicion);
    //func de 
};
template <typename T>
ArrayDinamico<T>::ArrayDinamico(int cantidad){
    size=cantidad;
    if(size==0){
        a=new T[1];
        *a=0;
    }else if (size<0)
    {
        std::cout<<"ERROR";
    }else{
        T valor;
        a=new T[size];
        for(int i=0;i<size;i++){
            std::cout<<"Digite un valor: ";
            std::cin>>valor;
            *(a+i)=valor;
        }
    }
};
template <typename T>
void ArrayDinamico<T>::mostrar(){
    if(size==0){
        std::cout<<0<<std::endl;
    }else{
        for(int i=0;i<size;i++){
        std::cout<<*(a+i)<<"\t";
        }
        std::cout<<std::endl;
    }
    
}
template <typename T>
void ArrayDinamico<T>::push_back(T valor){
    T *aux= new T[size+1];
    for(int i=0;i<size;i++){
        *(aux+i)=*(a+i);
    }
    *(aux+size)=valor;
    delete[] a;
    a=aux;
    size++;
}

template <typename T>
void ArrayDinamico<T>::ingresar(T valor, int posicion){
    T *aux= new T[size+1];
    for(int i=0;i<size+1;i++){
        if(i>=posicion){
            if(i==posicion){
                *(aux+i)=valor;
                i++;
            }
            *(aux+i)=*(a+i-1);
        }else{
            *(aux+i)=*(a+i);
        }   
    }
    delete[] a;
    a=aux;
    size++;
}
template <typename T>
void ArrayDinamico<T>::eliminar(int posicion){
    T *aux= new T[size-1];
    for(int i=0;i<size-1;i++){
        if(i>=posicion){
            if(i==posicion){
                i++;
            }
            *(aux+i-1)=*(a+i);
        }else{
            *(aux+i)=*(a+i);
        }   
    }
    delete[] a;
    a=aux;
    size--;
}

int main(){
    ArrayDinamico<int> a;
    a.mostrar();
    ArrayDinamico<char> *b= new ArrayDinamico<char>(4);
    b->mostrar();
    std::cout<<"Push_back('A')"<<std::endl;
    b->push_back('A');
    b->mostrar();
    std::cout<<"Ingresar en pos 3"<<std::endl;
    b->ingresar('e', 3);
    b->mostrar();
    std::cout<<"Eliminar pos 3"<<std::endl;
    b->eliminar(3);
    b->mostrar();
    delete b;
    return 0;
}
