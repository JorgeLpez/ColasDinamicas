#include <iostream>

class Constancia{
    private:
        std::string NombreAlm,NombreCarr;
        int MatAprob;
        float Prom;
    public:
        Constancia(){};

        friend std::ostream & operator<<(std::ostream &O, Constancia &x){
            O<<"\nNombre Alumno: "<<x.NombreAlm<<std::endl;
            O<<"Nombre de la Carrera: "<<x.NombreCarr<<std::endl;
            O<<"Total de materias aprobadas: "<<x.MatAprob<<std::endl;
            O<<"Promedio general: "<<x.Prom<<std::endl;
            return O;
        }

        friend std::istream & operator>>(std::istream &O, Constancia &x){
            std::cout<<"\nNombre Alumno: ";
            O>>x.NombreAlm;
            std::cout<<"Nombre de la Carrera: ";
            O>>x.NombreCarr;
            std::cout<<"Total de materias aprobadas: ";
            O>>x.MatAprob;
            std::cout<<"Promedio general: ";
            O>>x.Prom;
            return O;
        }

        bool operator==(Constancia& c)
        {
            if(c.NombreAlm==NombreAlm && c.NombreCarr==NombreCarr && c.MatAprob==MatAprob && c.Prom==Prom){
            return true;
            }
            return false;
        }

        bool operator!=(Constancia& c)
        {
            if(c.NombreAlm!=NombreAlm && c.NombreCarr!=NombreCarr && c.MatAprob!=MatAprob && c.Prom!=Prom){
            return true;
            }
            return false;

        }

};

template<class T>
class Cola;

template<class T>
class node{
private:
    T data;
    node<T>* sig;
public:
    node():sig(nullptr){};
    friend class Cola<T>;
};

template<class T>
class Cola{
private:
    node<T>* lista;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
public:
    int Buscar(T elem)const;
    Cola():lista(nullptr){};
    bool vacia()const;
    void imprimir()const;
    void Enqueue(T elem);
    void Dequeue();
    T Front();
};

template<class T>
int Cola<T>::Buscar(T elem)const{
    node<T>* aux=lista;
    int cont=0;
    while(aux!=nullptr && aux->data!=elem){
        aux = aux->sig;
        cont ++;
    }
    return cont;
}

template<class T>
T Cola<T>::Front(){
    if(!vacia()){
       return primero()->data;
    }
}

template<class T>
void Cola<T>::Dequeue(){
    eliminar(primero());
}

template<class T>
void Cola<T>::Enqueue(T elem){
    insertar(ultimo(),elem);
}

template<class T>
void Cola<T>::imprimir()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<aux->data<<"-> ";
        aux=aux->sig;
    }
}

template<class T>
bool Cola<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void Cola<T>::insertar(node<T>* pos, T elem){
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}

template<class T>
node<T>* Cola<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
node<T>* Cola<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* Cola<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
bool Cola<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

int main()
{
    int opc,cont;
    Cola<Constancia> Micola;
    Constancia x;
    do{
        system("cls");
        std::cout<<"\n\tCONSTANCIAS DE ESTUDIO"<<std::endl<<std::endl;
        std::cout<<"1. Generar solicitud para constancia."<<std::endl;
        std::cout<<"2. Recibir constancia."<<std::endl;
        std::cout<<"3. Buscar solicitud."<<std::endl;
        std::cout<<"4. Salir."<<std::endl<<std::endl;
        std::cout<<"Ingrese una opcion: ";
        std::cin>>opc;

        switch(opc){

            case 1: system("cls");
                    cont++;
                    std::cout<<"\n\tUsted tiene el turno #"<<cont<<" Ingrese sus datos: "<<std::endl;
                    std::cin>>x;
                    Micola.Enqueue(Constancia(x));
                    std::cout<<"Constancia agregada exitosamente!"<<std::endl<<std::endl;
                    system("pause");
                    break;

            case 2: system("cls");
                    if(Micola.vacia()){
                        std::cout<<"La cola esta vacia."<<std::endl;
                    }else{
                        std::cout<<"\n\tElaborando constancia: "<<std::endl;
                        x=Micola.Front();
                        std::cout<<x<<std::endl;
                        Micola.Dequeue();
                    }
                    system("pause");
                    break;

            case 3: system("cls");
                    if(Micola.vacia()){
                        std::cout<<"La cola esta vacia."<<std::endl;
                    }else{
                        std::cout<<"Ingresa los datos de la solicitud que deseas buscar: "<<std::endl;
                        std::cin>>x;
                            if(Micola.Buscar(x)==0){
                                 std::cout<<"\n\tsolicitud encontrada! No hay constancias antes de ti."<<std::endl<<std::endl;
                            }else if(Micola.Buscar(x)>=0){
                                std::cout<<"\n\tsolicitud encontrada!\nContancias restantes: #"<<Micola.Buscar(x)<<std::endl<<std::endl;
                            }else{
                                std::cout<<"\nConstancia no encontrada, favor de solicitar una."<<std::endl<<std::endl;
                            }
                    }
                    system("pause");
                    break;
        }
    }while(opc!=4);
}
