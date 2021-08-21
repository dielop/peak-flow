#include <stdio.h>
#include <string.h>
#define V 6
#define true 1
#define false 0
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

//Algortimo Ford-Fulkerson implementado por Diego Lopez y Gabriel Martin Pognante

//Prototipos
int fordFulkerson(int red[V][V],int s, int t);
void encola(int x);
int desencola();
int bfs(int s, int t);


//Variables globales
int grafo[V][V]; //matriz de adyacencia, grafo principal
int capacidad[V][V]; //capacidad (aux)
int flujo[V][V]; //flujo
int semicamino[V]; //semicaminos de s a T. Nodos son indice
int visitado[V]; //estado si hemos visitado o no para no pasar de nuevo 0 no visitado 1 visitado 2 terminado

//Variables de cola (globales)
int cola, cabeza;
int q[V]; 

//COMIENZO CODIGO

int main() {
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      grafo[i][j] = 0;
    }
  }
  //arriba inicializacion de matriz, abajo le damos valores de nuestra matriz
  grafo[0][1] = 4;
  grafo[0][2] = 6;
  grafo[1][3] = 3;
  grafo[1][4] = 5;
  grafo[2][4] = 6;
  grafo[3][2] = 9;
  grafo[3][5] = 5;
  grafo[4][5] = 4;

   
 
   //printeo de matriz de adyacencia
    printf ("\nMATRIZ\n\n");
   for (int i = 0; i < V; i++) {
       
       for (int j = 0; j < V; j++){
       printf  ("%d\t", grafo[i][j]);
       }
    printf ("\n");
   }
    printf ("\nDEBUGGING\n");
    int s = 0, t = 5;
    printf("\n\nFlujo maximo: %d\n\n", fordFulkerson(grafo,s, t));
    
}


int bfs(int s, int t){
  int u, v;
  for (u = 0; u < V; u++) {
       visitado[u] = false;  //inicializamos en no visitado
  }

  cabeza = cola = 0;
  
  encola(s);
  semicamino[s] = -1;
  while (cabeza != cola) {
    u = desencola();
    for (v = 0; v < V; v++) {
      if (visitado[v] == false && capacidad[u][v] - flujo[u][v] > 0) {  //verificamos que las condiciones se cumplan
        encola(v);
        semicamino[v] = u;
      }
    }
  }
  return visitado[t] == true; //true indica que fue visitado y no es necesario volver a encolar. en otras palabras lo ignora
}






//Algoritmo de fordFulkerson
int fordFulkerson(int red[V][V],int s, int t){
  memcpy(capacidad,red, V*V*sizeof(int)); //copio el grafo a la capacidad (hara de auxiliar)
  int a,b,u;
  int flujo_maximo = 0; //Iniciamos sin flujo
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      flujo[i][j] = 0; //init 0 flujos
    }
  }

  
   while (bfs(s, t)) {
    int fuente = 10;                 // flujo al que se le dara al grafo. Le damos un numero grande para simular una fuente "infinita"
    for (u = V - 1; semicamino[u] >= 0; u = semicamino[u]) {
      fuente = min(fuente, capacidad[semicamino[u]][u] - flujo[semicamino[u]][u]);
      printf("\nsemicamino %d = %d", u, semicamino[u]); //debug
    }
    for (u = V - 1; semicamino[u] >= 0; u = semicamino[u]) {
      flujo[semicamino[u]][u] += fuente;  //flujo positivo (al sumidero)
                                       printf("\nFlux+:%d scamino: %d",flujo[semicamino[u]][u],semicamino[u]); //debug
      flujo[u][semicamino[u]] -= fuente; //flujo negativo (en contra, volveria a la fuente)
                                       printf("\nFlux-:%d scamino: %d",flujo[u][semicamino[u]],semicamino[u]); //debug
    }
    // en el loop anterior damos los flujos correspondientes a cada camino
    flujo_maximo += fuente;
  }
  return flujo_maximo;
}

//Encola y marca el vertice visitado
void encola(int x){
  q[cola] = x;
  cola++;
  visitado[x] = true;
}

//Desencola
int desencola(){
    int x = q[cabeza];
    cabeza++;
    visitado[x] = true; //true indica que fue visitado y no es necesario volver a encolar. en otras palabras lo ignora
    return x; 
}
