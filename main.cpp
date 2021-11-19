#include <iostream>
#include "Grafo.h"
#include "functions.cc"
#include <vector>

int main() {
  Grafo graf;
  graph(graf);
  string mnpC="";
  int mnpCs=0;

  cout<<graf<<endl;

  while(true){//ciclo para probar los casos requeridos por el usuario, cambiando la variable MNP
    cout<<"____________________________________________"<<endl;
    cout<<"\nEnter the number of cases you want to try for the MNPs: "; cin>>mnpC; cout<<endl;
    cout<<"____________________________________________"<<endl;

    mnpCs=stoi(mnpC);
    if(mnpCs>0 && mnpCs<20){break;}//validación de MNP
    else if(mnpCs<=0){cout<<"That is a small number!! :/, try something higher (but lower than 20) :)"<<endl; continue;}
    else{
      cout<<"That is a huge number!! :O, try something lower (but higher than 0) :)"<<endl;
    }
  }

  int casesCounter=0;
  for (int y=0; y<mnpCs;y++){//ciclo que se repite las veces establecidas previamente
    mnpCases(graf,casesCounter);//se llama a la función que prueba los casos de MNP e imprime el número de puertos no visitados
    cout<<endl;
  }

} 