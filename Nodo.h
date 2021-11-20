#include <string>
#include <vector>
#include <iostream>
using namespace std;
#pragma once

class Nodo{
  private:
    //atributos
    string dato;
    Nodo *sig;
    vector<string> arcos;
    int conections;
    bool visited;
  public:
    //cconstructores
    Nodo(string);
    ~Nodo();
    //getters
    Nodo* getSig();
    string getDato();
    vector<string> getStrings();
    int getLengthStrings();
    bool getVisited();
    //int getMNP();
    //setters
    void setSig(Nodo*);
    void setDato(string);
    void addToVector(string);
    void setConections(int);
    void setArcos(vector<string>);
    void setVisited(bool);
    string getBowWithIndex(int);
    //void setMNP(int);
};

Nodo::Nodo(string dato){//constructor por omisión
  conections=0;
  this->dato=dato;
}

Nodo::~Nodo(){}//destructor

//getters
Nodo* Nodo::getSig(){//Obtener dirección de nodo izquierdo
  return sig;
}

string Nodo::getDato(){//obtener dato del nodo
  return dato;
}

bool Nodo::getVisited(){return visited;}
/*int Nodo::getMNP(){
  return MNP;
}*/

//setters
void Nodo::setSig(Nodo* sig){//cambiar el nodo izquierdo
  this->sig=sig;
}

void Nodo::setDato(string dato){//cambiar el dato del nodo
  this->dato=dato;
}

void Nodo::addToVector(string arco){//agrega un string al vector arcos
  arcos.push_back(arco);
}

vector<string> Nodo::getStrings(){//regresa el vector arcos
  return arcos;
}

int Nodo::getLengthStrings(){//regresa el largo del vector arcos
  return arcos.size();
}

void Nodo::setConections(int size){//setea el número de arcos dentro del nodo
  conections=size;
}

void Nodo::setArcos(vector<string> arc){//setea el vector arcos
  arcos=arc;
}

void Nodo::setVisited(bool visited){this->visited=visited;}

string Nodo::getBowWithIndex(int index){//regresa el arco en el índice otorgado
  return arcos[index];
}