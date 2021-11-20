#pragma once
#include <stdlib.h>
#include <algorithm>
#include <list>
#include "Nodo.h"

class Grafo{
  private:  
    //atributos
    Nodo * head;
  public:
    //constructores
    Grafo();
    virtual ~Grafo();
    //getters
    Nodo* getHead();
    Nodo* getNodeFromIndex(string);
    string getElementByIndex(int);
    int getNonReachable();
    //funciones void
    void insertaOrden(string);
    void insertaArcos(vector<string> arcos);
    void resetGraph(vector<string> newe);
    void DFS(Nodo*,vector<bool>&);
    void dfsAdapted(Nodo*, vector<bool>&, int);
    void trip(Nodo*,int);
    void WARSHALL();
    //funciones int
    int searchNode(string);
    int graphLength();
    //funciones bool
    bool isValid(Nodo*,string);
    bool nodeExists(string);
    bool foundInBows(Nodo*,string);
    //función vector bidimensional
    vector<vector<int>> buildAdjacencyMatrix();
    //sobrecarga de operador
    friend std :: ostream& operator<<(std :: ostream&, Grafo&);

};

Grafo::Grafo(){//constructor
  head=NULL;
}

Grafo::~Grafo(){}//destructor

Nodo* Grafo::getHead(){return head;}

void Grafo::insertaOrden(string n){//inserta un nodo en orden en el grafo
  Nodo* nuevo = new Nodo(n) ;
  if (head==NULL){//caso de que sea un grafo vacío
    head=nuevo;
  }
  else{
    Nodo* antes=head;
    Nodo* aux=head;
    while(aux!=NULL && aux->getDato()<n){//coloca el apuntador
      antes=aux;
      aux=aux->getSig();
    }
    if (antes==aux){ //caso insertar al inicio
      nuevo->setSig(head);
      head=nuevo;
    }
    else if (aux==NULL){//caso insertar al final
      antes->setSig(nuevo);
    }
    else{//se inserta entre dos
      antes->setSig(nuevo);
      nuevo->setSig(aux);
    }
  }
}

void Grafo::insertaArcos(vector<string> arcos){
  Nodo* aux=head;

  while(aux!=NULL){// se recorre el grafo
    for(int x=0;x<arcos.size();x+=2){//ciclo para agregar strings al vector de arcos de un nodo
      string s="",s1="";
      
      s=arcos[x];//even
      s1=arcos[x+1];//odd

      if (s==aux->getDato() && isValid(aux,s1) && s1!=s){//valida que no se repitan las letras
        aux->addToVector(s1);//se agrega la letra de la derecha
        aux->setConections(aux->getLengthStrings()+1);//aumenta el atributo conexions (largo del vector del nodo)
      }
      //cout<<"here?"<<endl;

    }

    aux=aux->getSig();
  }
}

///////////////////////////////////////////////
void Grafo::resetGraph(vector<string> newe){//función que reinicia el vector de los nodos
  Nodo* aux=head;

  while(aux!=NULL){
    aux->setArcos(newe);
    aux=aux->getSig();
  }
}
///////////////////////////////////////////////

bool Grafo::nodeExists(string exist){//función que valida si un nodo existe en el grafo
  Nodo* aux=head;
  string decoy="";

  while(aux!=NULL){
    decoy=aux->getDato();
    if (decoy==exist){
      return true;
    }
    aux=aux->getSig();
  }

  return false;

}

int Grafo::graphLength(){//regresa el largo del grafo (número de nodos)
  Nodo* aux=head;
  int counter=0;
  while(aux!=NULL){
    aux=aux->getSig();
    counter++;
  }
  return counter;
}

bool Grafo::isValid(Nodo* currentNode, string s){//se valida que un string no se encuentre en el vector de arcos de un nodo
  vector<string> nodeVector=currentNode->getStrings();

  for (int u=0; u<currentNode->getLengthStrings();u++){
    if (s==nodeVector[u]){
      return false;
    }
  }

  return true;//no se encontró, y se puede insertar
}

int Grafo::searchNode(string word){//función que regresa el índice de un nodo en la lista ligada
  Nodo* aux=head;
  int counter=0;

  if(aux==NULL){return -1;}
  else{
    while(aux!=NULL && aux->getDato()!=word){
      counter++;
      aux=aux->getSig();
    }

    if(aux==NULL){return -1;}
  }
  return counter;
}


Nodo* Grafo::getNodeFromIndex(string index){//función que devuelve un nodo a partir del dato que se encuentra en el
  string counter="";
  Nodo* aux=head;

  while(aux!=NULL && aux->getDato()!=index){
    aux=aux->getSig();
  }

  return aux;
}

bool Grafo::foundInBows(Nodo* current, string element){//función que devuelve true si un string se encuentra en el vector de un nodo
  string s ="";
  for (int t=0; t<current->getLengthStrings();t++){
    //char x=current->getStrings()[t];
    //s.push_back(x);
    s=current->getStrings()[t];
    if(element==s){return true;}
  }
  return false;
}


string Grafo::getElementByIndex(int idx){//función que regresa el dato de la lista ligada en un índice
  Nodo* aux=head; int counter=0;

  while(counter!=idx){//ciclo para mover apuntador
    if(counter==idx){break;}
    aux=aux->getSig();
    counter++;
  }

  return aux->getDato();
}


vector<vector<int>> Grafo::buildAdjacencyMatrix(){//algoritmo que construye una matriz de adyacencia para el algoritmo de warshall
  vector<vector<int>> matrix;
  vector<int> row;
  Nodo* aux=head;

  for(int x=0; x<graphLength();x++){//row
    row={};

    for(int y=0; y<graphLength();y++){//column
      if(foundInBows(aux,getElementByIndex(y))){//si se encuentra en el vector, se agrega un 1, si no, se agrega 0
        row.push_back(1);
        //matrix[x][y]=1;
      }
      else{row.push_back(0);}
    }
    matrix.push_back(row);
    aux=aux->getSig();
  }
  return matrix;//se regresa la matriz construída
}



void Grafo::DFS(Nodo* vis,vector<bool> &visited){
  //Algoritmo recuperado de: https://gist.github.com/MagallanesFito/92ac8dd3badbb2518d653f6a9ba1b573
  //El algoritmo fue adaptado a este grafo
  string arrow="";
  visited[searchNode(vis->getDato())] = true; //cambia el valor del vector a true, para indicar que ya fue visitado
  cout << vis->getDato() << arrow;//se imprime nodo por nodo conforme avanza

  for(int i=0; i<vis->getLengthStrings();i++){ //nodos adyacentes
  
    if(visited[searchNode(vis->getBowWithIndex(i))]==false){//si no ha sido visitado, se aplica recursión
        DFS(getNodeFromIndex(vis->getBowWithIndex(i)),visited);
    }
  }
}

void Grafo::dfsAdapted(Nodo* vis, vector<bool>&visited,int MNP){
  //Algoritmo adaptado de DFS, con el cuál se recorrerá todo el grafo y sus ramas hasta que MNP sea 0
  visited[searchNode(vis->getDato())] = true;//se marca el valor correspondiente al nodo en el vector a true si este fue visitado

  if(MNP>0){
   for(int g=0;g<vis->getLengthStrings();g++){//se aplica un ciclo para recorrer los elementos en el vector de arcos del nodo inicial

      dfsAdapted(getNodeFromIndex(vis->getBowWithIndex(g)),visited, MNP-1);
    }
  }
}

void Grafo::trip(Nodo* vis, int MNP){
  vis->setVisited(true);

  if (MNP>0){
  for(int g=0;g<vis->getLengthStrings();g++){//se aplica un ciclo para recorrer los elementos en el vector de arcos del nodo inicial

    trip(getNodeFromIndex(vis->getBowWithIndex(g)),MNP-1);
    }
  }

}

int Grafo::getNonReachable(){
  Nodo* aux=head;
  int counter=0;

  while(aux!=NULL){
    if (aux->getVisited()==false){counter++;}
    aux=aux->getSig();  
  }
  return counter;
}


void Grafo::WARSHALL(){//algoritmo de warshall
  vector<vector<int>> warshall=buildAdjacencyMatrix();//matriz de adyacencia

  cout<<"\n___________________________"<<endl;
  cout<<"Warshall Adjacency Matrix: "<<endl;
  cout<<"___________________________"<<endl;

  for(int a=0; a<warshall.size();a++){//se imprime la matriz de adyacencia
    for (int m=0; m<warshall.size();m++){
      cout<<warshall[a][m]<<" ";
    }
    cout<<endl;
  }

  //creación de matriz de cerradura transitiva
  for(int z=0; z<graphLength();z++){//frame
    for(int x=0; x<graphLength();x++){//rows
      for (int y=0;y<graphLength();y++){//columns
        if(warshall[z][y]==1 && warshall[x][z]==1){//si hay 1 en la fila y la columna, se agrega un 1 en la intersección diagonal
          warshall[x][y]=1;
        }
      }
    }
  }

  cout<<"\n___________________________"<<endl;
  cout<<"Transitive Lock Matrix: "<<endl;
  cout<<"___________________________\n"<<endl;

  for(int a=0; a<warshall.size();a++){//se imprime la matriz de cerradura transitiva
    for (int m=0; m<warshall.size();m++){
      cout<<warshall[a][m]<<" ";
    }
  cout<<endl;
  }

}

std :: ostream& operator<<(std :: ostream& salida, Grafo& graf){//sobrecarga de operador <<

  Nodo* aux=graf.getHead();
  cout<<"____ GRAPH ____"<<endl;
  while(aux!=NULL){
    int conexions=aux->getLengthStrings();
    vector<string> conect=aux->getStrings();
    string st="";

    for (int y=0; y<conexions;y++){//se imprime el nodo y luego su respectivo vector
      st+=conect[y]+" ";
    }
    salida<<"["<<aux->getDato()<<"] --->  "<<"["<<st<<"]"<<endl;
    aux=aux->getSig();
  }

  return salida;
}