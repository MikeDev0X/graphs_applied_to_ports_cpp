#include "Grafo.h"
#include <algorithm>

void graph(Grafo &graf){
  
  int portsNo=0;
  while(true){//valida el número de entradas
    cout<<"Enter the number of ports in the network: "; cin>>portsNo; cout<<endl;
    if(portsNo<=30 && portsNo>=0){break;}
    else{cout<<"The number of ports must be greater than 0 and lower than 30, try again "<<endl;}
  }

  string port=""; int nodesCounter=0;
  while (nodesCounter<portsNo){//inserción de puertos (nodos)
    cout<<"port: "; cin>>port; 

    for_each(port.begin(),port.end(),[](char &c){//cambia los arcos a mayúsculas
      c=::std::toupper(c);
    });

    graf.insertaOrden(port);

    nodesCounter++;
    port="";
  }
  cout<<endl;

  string bowsNo="";
  int bowsN=0;

  while(true){//valida el número de arcos
    cout<<"Enter the number of connections (Bows): "; cin>>bowsNo;
    bowsN=stoi(bowsNo);
    if(bowsN<=30 && bowsN>=0){break;}
    else{cout<<"the number of connections must be less than 30 and more than 0, try again"<<endl;}
  }


  cout<<"\nEnter the conections. Example: (initialPort secondPort)"<<endl;
  string portA="",portB="";
  vector<string> ports;

  for(int i=0; i<bowsN;i++){//inserción de arcos para grafo de dos direcciones
    cout<<"Bow: ";cin>>portA>>portB;

    for_each(portA.begin(),portA.end(),[](char &c){//cambia los arcos a mayúsculas
      c=::std::toupper(c);
    });
    for_each(portB.begin(),portB.end(),[](char &c){//cambia los arcos a mayúsculas
      c=::std::toupper(c);
    });

    ports.push_back(portA);
    ports.push_back(portB);

    ports.push_back(portB);
    ports.push_back(portA);

    portA=""; portB="";
  }
  cout<<endl;

  graf.insertaArcos(ports);
  
}

void mnpCases(Grafo& graf, int& casesCounter){//función para probar distintos MNPs
string mnpFun="";
  cout<<"____________________________________________"<<endl;
  cout<<"\nEnter the Maximum Number of Ports (MNP): "; cin>>mnpFun;

  int mnpFunInt=0;
  mnpFunInt=stoi(mnpFun);

  string initialNode="";
  vector<bool> visit={};
  int nonVisited=0;

  while(true){//ciclo para comprobar la existencia del nodo inicial
    cout<<"Enter the Initial port: ", cin>>initialNode; cout<<endl;

    for_each(initialNode.begin(),initialNode.end(),[](char &c){//cambia los arcos a mayúsculas
      c=::std::toupper(c);
    });

    if(graf.nodeExists(initialNode)){
      //dfsAdapted;

      for(int h=0; h<graf.graphLength();h++){
        visit.push_back(false);
      }
      graf.dfsAdapted(graf.getNodeFromIndex(initialNode),visit,mnpFunInt);//se recorre el grafo restando al MNP hasta que este llegue a 0

      break;
    }
    else{
      cout<<"That port doesn't exist, try again"<<endl;
      }
    }
        for( int x=0;x<visit.size();x++){//se hace un contador con los nodos falsos en el vetor de visitas
          if(visit[x]==false){
            nonVisited++;
          }
  }

  cout<<"Case "<< casesCounter+1<<":  "<<nonVisited<<" ports not reachable from port "<< initialNode <<" with MNP = "<<mnpFunInt<<"."<<endl;
  casesCounter++;
  cout<<"____________________________________________"<<endl;
  cout<<endl;

  //graf.insertaArcos(ports);
  //cout<<"Inserción hecha"<<endl;


}