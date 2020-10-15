#include <iostream>

using namespace std;

struct sudoku{ //Estructura que me hace la matrizg
    int **matriz;
    int restantes;

    sudoku();
    ~sudoku();
    bool jugar(int fila, int columna, int numero);
    int getRestantes();
    void imprimir();
};

int main() //Aqui esta el programa principalg
{
    sudoku *sdk = new sudoku();
    int fila, columna, numero;
    while(sdk->getRestantes() > 0){
        sdk->imprimir();
        cout << "Ingrese jugada(Fila[0-9] columna[0-9] numero[0-9]): ";
        cin >> fila >> columna >> numero;
        if(fila>=1 && fila <= 9 && columna >=1 && columna <= 9){
            if(!sdk->jugar(fila-1, columna-1, numero)){
                cout << "----------------Juagada Incorrecta--------------"<<endl;
            }
        }
        else if(fila == 0 && columna == 0 && numero == 0){
            break;
        }
        else{
            cout << "----------------Juagada Illegal--------------"<<endl;
        }
    }
    delete sdk;
    return 0;
}

sudoku::sudoku(){
    matriz = new int*[9];
    for(int i=0; i < 9; i++){
        matriz[i] = new int[9];
        for(int j=0;j<9;j++){
            *(*(matriz+i)+j) = 0;
            //matriz[i][j] = 0;
        }
    }
    restantes = 9*9;
}

sudoku::~sudoku(){
    for(int i=0; i < 9; i++){
        delete [] matriz[i];
    }
    delete [] matriz;
    cout << "MEMORIA LIBERADA";
}


bool sudoku::jugar(int fila, int columna, int numero){
    char opt;
    //Borrar un numero
    if(numero == 0){
        if(matriz[fila][columna] != 0) restantes++;
        *(*(matriz+fila)+columna) = numero;
        return true;
    }
    //Verifica si el espacio esta ocupado
    if(matriz[fila][columna] != 0){
        cout << "Seguro que quiere reemplazarlo? (0 - NO, Otra tecla - SI ): ";
        cin >> opt;
        if(opt == '0') return false;
    }
    //verificar si existe en la fila o en la columna
    for(int i=0;i<9;i++){
        if(numero == matriz[fila][i]) return false;
        if(numero == matriz[i][columna]) return false;
    }
    //verificar el cuadrante
    int filacuadrante = (fila/3)*3;
    int columnacuadrante = (columna/3)*3;
    for(int i=filacuadrante;i<filacuadrante+3;i++){
        for(int j=columnacuadrante; j<columnacuadrante+3;j++){
            if(numero == matriz[i][j]) return false;
        }
    }

    *(*(matriz+fila)+columna) = numero;
    restantes--;
    return true;
}

void sudoku::imprimir(){
    for(int i = 0; i < 9; i++){
        if(i%3==0){
            for(int j=0;j<9;j++){
                if(j%3==0){
                    cout << "+";
                }
                cout << "--";
            }
            cout << "+\n";
        }
        for(int j=0;j<9;j++){
            if(j%3==0){
                cout << "|";
            }
            if(matriz[i][j]==0){
                cout << ".";
            }else{
                cout << matriz[i][j];
            }
            cout << " ";
        }
        cout << "|\n";
    }
    for(int j=0;j<9;j++){
        if(j%3==0){
            cout << "+";
        }
        cout << "--";
    }
    cout <<"+\n";

}


int sudoku::getRestantes(){
    return restantes;
}




























