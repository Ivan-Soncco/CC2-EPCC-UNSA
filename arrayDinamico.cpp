#include <iostream>

class ArrayDinamico{
    private:
        int *a;
        int size=0;
    public:
    ArrayDinamico(){a= new int[size];};
    ArrayDinamico(int cantidad);
    void push_back(int numero);
    void mostrar();
    //func de 
};
ArrayDinamico::ArrayDinamico(int cantidad){
    size=cantidad;
    if(size==0){
        a=new int[1];
        *a=0;
    }else if (size<0)
    {
        std::cout<<"ERROR";
    }else{
        int valor;
        a=new int[size];
        for(int i=0;i<size;i++){
            std::cout<<"Digite un valor: ";
            std::cin>>valor;
            *(a+i)=valor;
        }
    }
};
void ArrayDinamico::mostrar(){
    if(size==0){
        std::cout<<0<<std::endl;
    }else{
        for(int i=0;i<size;i++){
        std::cout<<*(a+i)<<"\t";
        }
        std::cout<<std::endl;
    }
    
}
void ArrayDinamico::push_back(int numero){
    int *aux= new int[size+1];
    for(int i=0;i<size;i++){
        *(aux+i)=*(a+i);
    }
    *(aux+size)=numero;
    delete[] a;
    a=aux;
    size++;
}

int main(){
    ArrayDinamico a;
    a.mostrar();
    ArrayDinamico *b= new ArrayDinamico(4);
    b->mostrar();
    b->push_back(76);
    b->mostrar();
    delete b;
    return 0;
}
