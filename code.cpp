#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <fstream>
const int SIZE = 40000;

using namespace std;

string vet[SIZE];
string vet2[SIZE];
void bubble(string *vet, int n){
    string aux;

    for(int i = 0; i < n; i++){ //repete o processo
        for(int  j = 0; j < n-1-i; j++){ //seleciona o valor para fazer as comparações
            if(vet[j+1] < vet[j]){ //verifica se o vetor a frente é maior que o atual e realiza a troca em caso positivo
                aux = vet[j]; 
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }
}

void selection(string *vet, int n){
    string aux;
    int menor;

    
    for(int i = 0; i < n-1; i++){ // faz n-1 varreduras no vetor
        menor = i;
        for(int j = (i+1); j < n; j++) // encontra o menor elemento em ordem alfabetica
            if(vet[j] < vet[menor])    menor = j;
        // troca o elemento encontrado no laco anterior pelo elemento da posicao i
        aux = vet[i];
        vet[i] = vet[menor];
        vet[menor] = aux;
    }
}

void insertion(string *vet, int n){
    int j;
    string aux;

    // laco que varre todos os elementos do vetor
    for(int i = 1; i < n; i++){
        aux = vet[i];
        // este laco percorre todo o vetor e desloca os elementos
        // ate achar a posicao do aux(vet[i])
        for(j = (i-1); (j >= 0 && vet[j] > aux); j--)
            vet[j+1] = vet[j];
        vet[j+1] = aux;
    }
}

void shell(string *vet, int n){
    int j;
    int h = n/2; //pega metade do tamanho do vetor
    string aux;

    while(h >= 1){ //realiza até 'h' ser igual a 1, então realiza a ultima vez
        for(int i = 1; i < n; i++){ //realiza o loop para passar por todo o vetor
            aux = vet[i];
            //passa por todos os elementos, e compara eles de acordo com o tamanho de 'h', e tambem realiza a mudança caso necessario  
            for(j = i - h; (j >= 0) && (vet[j] > aux); j = j - h) 
                vet[j + h] = vet[j];
            vet[j + h] = aux; 
        }
        h = h / 2; //divide 'h' por 2, para que assim uma hora seja possivel comparar com todo o vetor 
    }
}

void mergeIntercala(string *vet, string *aux, int ini, int meio, int fin){
    int atual, fimEsq, n;
    atual = ini;
    fimEsq = meio-1;
    n = fin - ini + 1;

    // esse laco intercala os elementos em "ini" ou "meio"
    // ate que uma das metades chegue ao fim

    while((ini <= fimEsq) && (meio <= fin)){
        if(vet[ini] <= vet[meio])
            aux[atual++] = vet[ini++];
        else
            aux[atual++] = vet[meio++];
    }

    // intercala o resto do vetor que sobrou

    while(ini <= fimEsq)
        aux[atual++] = vet[ini++];

    while(meio <= fin)
        aux[atual++] = vet[meio++];

    // passa os elementos do vetor aux para o principal

    for(int i = 0; i < n; i++){
        vet[fin] = aux[fin];
        fin--;
    }
}

void mergeDivide(string *vet, string *aux, int ini, int fin){
    int meio;

    // funcao recursiva responsavel por dividir o vetor em subvetores
    // e depois os intercala ordenando-os
    if(fin > ini){
        meio = (fin+ini)/2;
        mergeDivide(vet, aux, ini, meio);
        mergeDivide(vet, aux, meio+1, fin);
        mergeIntercala(vet, aux, ini, meio+1, fin);
    }
}

void merge(string *vet, int n){
    string aux[n];
    mergeDivide(vet, aux, 0, n-1);
}

int particiona(string *vet, int esq, int dir){
    int i, j;
    string pivo, aux;
    i = esq;
    j = dir;
    pivo = vet[esq];

    while(i < j){ //verifica até 'j' ser maior ou igual a 'i' 
        while((vet[i] <= pivo) && (i < dir)) //verifica até encontrar o 'i' correto
            i++;
        while((vet[j] >= pivo) && (j > esq)) //verifica até encontrar o 'j' correto
            j--;
        if(i < j){
            aux = vet[j];
            vet[j] = vet[i];
            vet[i] = aux;
        }
    }
    vet[esq] = vet[j];
    vet[j] = pivo;
    return j; //devolve o valor onde estará o pivo
}

void quick(string *vet, int esq, int dir){
    if(esq < dir){//quando 'esq' igual a 'dir' o vetor terminou de ser ordenado
        int pivo = particiona(vet, esq, dir);//encontra a posição do 'pivo'
        quick(vet, esq, pivo-1);
        quick(vet, pivo+1, dir);
    }
}

// --------------------------------------------------------------------------------------------------------------------------------------------------

void imprimeVetor(string *vet){
    cout << "[ ";
    for(int i = 0; i < SIZE; i++)
        cout << " " << vet[i] << ", ";
    cout << " ]\n";
}

void menu(){
    cout << "Escolha o algoritmo de ordenação: " << endl;
    cout << "1) Bubble Sort" << endl;
    cout << "2) Selection Sort" << endl;
    cout << "3) Insertion Sort" << endl;
    cout << "4) Shell Sort" << endl;
    cout << "5) Merge Sort" << endl;
    cout << "6) Quick Sort" << endl;
    cout << "7) SAIR..." << endl;
}

void geraVetor(string *vet){
    ifstream arquivo;
    string palavra;
    //arquivo.open("C:\\Users\\pedro\\OneDrive\\Área de Trabalho\\C++\\aurelio40000.txt");
    arquivo.open("aurelio40000.txt");
    if(arquivo.is_open()){
        for(unsigned int i = 0; i < SIZE; i++){
            getline(arquivo, palavra);
            vet[i] = palavra;
        }
    }else
        cout << "Não foi possivel abrir o arquivo...";

    arquivo.close();
}

void copiaVetor(string *vet, string *vet2){
    for(int i = 0; i < SIZE; i++)
        vet2[i] = vet[i];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------
int tempoBubbleSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    bubble(vet2 , SIZE);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
int tempoSelectionSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    selection(vet2 , SIZE);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
int tempoInsertionSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    insertion(vet2 , SIZE);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
int tempoShellSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    shell(vet2 , SIZE);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
int tempoMergeSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    merge(vet2 , SIZE);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
int tempoQuickSort(string *vet2){
    int tempo_inicio, tempo_fim;
    tempo_inicio = (int) clock();
    quick(vet2 , 0, SIZE-1);
    tempo_fim = (int) clock(); 
    return ((tempo_fim - tempo_inicio)*1000/CLOCKS_PER_SEC);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, const char *argv[]){
    int opt = 0;
    //string vet[SIZE];
    //string vet2[SIZE];
    menu();
    geraVetor(vet);
    cout << endl; 
    copiaVetor(vet, vet2);
    while(opt != 7){
        //imprimeVetor(vet);
        cout << "Selecione uma opcao do menu : ";
        cin >> opt;
        cout << endl;

        switch(opt){
            case 1:
                cout <<"\nDemorou "<< tempoBubbleSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 2:
                cout <<"\nDemorou "<< tempoSelectionSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 3:
                cout <<"\nDemorou "<< tempoInsertionSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 4:
                cout <<"\nDemorou "<< tempoShellSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 5:
            
                cout <<"\nDemorou "<< tempoMergeSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 6:
                cout <<"\nDemorou "<< tempoQuickSort(vet2) <<" milisegundos" << endl;
                //imprimeVetor(vet2);
                break;
            case 7:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Codigo invalido!" << endl;
        }
    }
    return 0;
}