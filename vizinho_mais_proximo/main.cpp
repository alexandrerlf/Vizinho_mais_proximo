#include <iostream>                                     //biblioteca padrao
#include <fstream>                                      //biblioteca ler arquivo
#include <vector>                                       //biblioeca vector  
#include <sstream>                              
#include <math.h>                                       //biblioteca distancia euclidiana
#include <time.h>                                       //biblioteca calcular tempo

using namespace std;

int distaciaEuclidiana(double x1, double y1, double x2, double y2){

    int distancia;
    int hipotenusa;
    double x; 
    double y;
    x = x1 - x2;
    y = y1 - y2;     

    hipotenusa = hypot(x,y); 

    distancia = (int)round(hipotenusa);

    return distancia;
}

void vizinho_mais_proximo(int d, int cap, int v, int caso ){
    
    ifstream file;
    stringstream output; 

    if(caso == 1){
        file.open("P-n19-k2-d19-v2-c160.txt");
    }else if(caso == 2){
        file.open("P-n20-k2-d20-v2-c160.txt");
    }else if(caso == 3){
        file.open("P-n23-k8-d23-v8-c40.txt");
    }else if(caso == 4){
        file.open("P-n45-k5-d45-v5-c150.txt");
    }else if(caso == 5){
        file.open("P-n50-k10-d50-v10-c100.txt");
    }else if(caso == 6){
        file.open("P-n51-k10-d51-v10-c80.txt");
    }else if(caso == 7){
        file.open("P-n55-k7-d55-v7-c170.txt");
    }else if(caso == 8){
        file.open("P-n16-k8-d16-v8-c35.txt");
    }else if(caso == 9){
        file.open("cvrp1.txt");
    }else if(caso ==10){
        file.open("cvrp2.txt");
    }else{
        file.open("cvrp3.txt");
    }
    
    int acc, l, c;      //auxiliares 
    int min;
    int v_atual = 0;    //guarda o valor da cidade atual visitada
    int aux;
    int cont = 0;        
    int custo = 0;      //somatorio dos custos    
    int custoAcumulado = 0;
    int tempo = 0;
    bool flag = false;  //mecanismo de parada do for
    clock_t tempo_inicial, tempo_final; // calculo tenmpo de exercução
    int matrix[d][d];   //matrix de adjancencia ponderada
    vector<int> demanda;//cada indice refencia a demanda desta cidade  
    vector<int> coorX;  //armazena coordenada x
    vector<int> coorY;  //armazena coordenada y
    int veiculo[v];     //vetor de veiculo com capacidade
    bool atendido[d];   //cada posição indicada para cada cidade em ordem visitada 
    bool chegada [v];   //armazena a chegada do veiculo
    /*vector<int> rota;
    int v_swap = v;
    vector<int> rota_swap;
    int custo_swap = 0;
    int aux_swap;*/
    
    for( int k = 0; k < v; k++){
        veiculo[k] = cap;
        chegada[k] = false;
    }
    for(l = 0; l < d; l++){
        if(l == 0)
            atendido[l] = true;// sai do deposito   
        else
            atendido[l] = false;//cidades para visitar                  
    }   


    //calculo matriz adjacencia
    if( (caso==9) || (caso==10) || (caso==11) ){//copa
        min = 1001;
       while(!file.eof()){//adquirir os valores de demanda e pesos entre cidades

            for (l = 0; l < d; l++){
                file >> acc;
                demanda.push_back(acc);
            }
            for(l = 0; l < d; l++){
                file >> acc;
                coorX.push_back(acc);
                file >> acc;
                coorY.push_back(acc);
            }      
        }
        for (l = 0; l < d; l++){
            for (c = 0; c < d; c++){                   
            matrix[l][c] = distaciaEuclidiana(coorX[l], coorY[l], coorX[c], coorY[c]);
            }           
        }       
    }//fim calculo matriz adjancencia

    if( (caso!=9) && (caso!=10) && (caso!=11) ){//exclui copa

        min = 101;
        while(!file.eof()){//adquirir os valores de demanda e pesos entre cidades
            for (l = 0; l < d; l++){
                file >> acc;
                demanda.push_back(acc);
            }
            for (l = 0; l < d; l++){
                for (c = 0; c < d; c++){
                    file >> acc;                
                    matrix[l][c] = acc;
                }           
            }      
        }          
    }
    
   tempo_inicial = clock();
   //vizinho mais proximo
   while(v > 0){
        
        v--;//executa os veiculos do maior ao zero        
        
        if( (veiculo[v] != 0) ){//testa se há capacidade             
            
            for(v_atual; v_atual < d ; v_atual++){//for da cidade atual a proxima
                
                for (c = 0; c < d; c++){   
                                   
                    if( ((matrix[v_atual][c]) < min) && (atendido[c] == false) && ((matrix[v_atual][c]) != 0) ){//calcula menor arco entre cidades                        
                        min = matrix[v_atual][c];
                        aux = c;                                                                        
                    }
                }                
                
                veiculo[v] -= demanda[aux];//diminui a capacidade do veiculo pela demanda 
                
                if(veiculo[v] < 0){
                    veiculo[v] += demanda[aux];//devolve a demanda retirada, porque ficou negativa               
                    output << v_atual << ", " << 0 ; 
                    //rota.push_back(v_atual);
                   // rota.push_back(0);                                                  
                    chegada[v] = true;                    
                    custo = custo + matrix[v_atual][0];//soma o ultimo custo                                                       

                }else{//significa que a demanda foi atendida por nao estar negativo
                    demanda[aux] -= demanda[aux];
                    atendido[aux] = true;//marca a cidade como visitada                                     
                    output << v_atual << ", ";
                    //rota.push_back(v_atual);
                    custo +=min;//atualiza o custo                      
                }               
                                  
                v_atual = aux-1;//desconta o ++ do for para partir da cidade atual

                if( (caso==9) || (caso==10) || (caso==11) ){
                    min = 1001;
                }else{
                    min = 101;
                }

                for(int k = 0 ; k < d; k++){//verifica se todos foram atendidos
                    if(atendido[k] == true){
                        cont++;
                    }else
                        break;                 
                }
                if( cont == d){//e seta a flag de chegada ao desposito
                   chegada[v] = true; 
                   output << aux << ", " << 0 ;
                   //rota.push_back(aux);
                   //rota.push_back(0);
                   custo = custo + matrix[aux][0];//soma ultimo custo
                }

                cont = 0;
                for(int k = 0; k < d; k++ ){//verifica se todos foram visitador e para
                    if( (atendido[k] == true) || ( chegada[v] == true ) ){
                        cont++;
                    }else{
                        cont = 0;
                        break;                            
                    }                              
                }
                if(cont == d){ //flag para sair do for               
                    flag = true;             
                    break;
                }
                
            }            

            custoAcumulado += custo;
            flag = false;//re-init
            v_atual = 0;//re-init    
            cont = 0;//re-init
            custo = 0;                          
        } 
        output << "; ";  
        output << "\n";
    }//fim vizinho mais proximo
    tempo_final = clock();

    file.close();
    output << "Instancia " << caso << ":" << endl;
    output << "\t" << "Aplicando o Alg vizinho mais proximo." << endl;
    output << "\t" << "Custo " << ": " << custoAcumulado  << endl;
    output << "\t" << "Tempo de exercucao " << ": " << (tempo_final - tempo_inicial) / (double)CLOCKS_PER_SEC << " seg" << endl;


    /*cout << "Rota antes swap " << endl;
    for(int i = 0; i < rota.size(); i++){
        cout << rota[i] << ", ";
    }
    cout << "CUsto: " << custoAcumulado;
    //tenho rota em rota
    //tenho matriz em matriz[l][c]
    //tenho custo do vizinho em custo acumulado
    rota_swap = rota;

    //SWAP
    for(l = 1; l < d; l++){ // começa em 1 para excluir deposito

        rota_swap = rota;

       if(rota_swap[l] == 0)//filtra a sequencia dupla de zeros da rota
            l++;

        for(c = (l+1); c < d; c++){ // swap com o proximo cidade
            if(rota_swap[c] == 0)//filtra a sequecnia dupla de zeros da rota
                break;

            aux_swap = rota_swap[l];
            rota_swap[l] = rota_swap[c];
            rota_swap[c] = aux_swap;          


           for(int i = 0; i < rota.size(); i++){//calculo do custo               
                    //custo_swap += matrix[ rota_swap[i] ][ rota_swap[i+1] ];
                    cout << " ERRO " << custo_swap+1 << ", ";               
            }

            if( custo_swap < custoAcumulado){
                custoAcumulado = custo_swap;
                rota = rota_swap;
                break;
            }

        }
    }

    cout << "\n";
    cout << "Rota apos swap " << endl;
    for(int i = 0; i < rota.size(); i++){
        cout << rota[i] << ", ";
    }
    cout << "Custo: " << custo_swap;*/

    //SALVA OUTPUT NO .TXT
    ofstream saida("saida.txt", ofstream::out);
    saida << output.str();   

    #if defined(_WIN32)
    //ABRE O .TXT SAIDA NO WIN
    system("start notepad saida.txt");
    #endif
    custoAcumulado = 0;    
}

void test1(){           //P-n19-k2-d19-v2-c160
    
    const int d = 19;   //numero de cidades
    const int cap = 160;//capacidade cada veiculo
    int v = 3;          //numero de veiculos, modificar para 3
    int caso = 1;       
    
    cout << endl << endl;   
    vizinho_mais_proximo(d, cap, v, caso);      
}

void test2(){           //P-n20-k2-d20-v2-c160 
    
    const int d = 20;   //numero de cidades
    const int cap = 160;//capacidade cada veiculo
    int v = 3;          //numero de veiculos, modificador
    int caso = 2;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);  
}

void test3(){           //P-n23-k8-d23-v8-c40
    
    const int d = 23;   //numero de cidades
    const int cap = 40; //capacidade cada veiculo 
    int v = 10;         //numero de veiculos, modificado 
    int caso = 3;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

void test4(){           //P-n45-k5-d45-v5-c150 
    
    const int d = 45;   //numero de cidades
    const int cap = 150;//capacidade cada veiculo 
    int v = 5;          //numero de veiculos 
    int caso = 4;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);  
}
void test5(){           //P-n50-k10-d50-v10-c100
    
    const int d = 50;   //numero de cidades
    const int cap = 100;//capacidade cada veiculo 
    int v = 11;         //numero de veiculos 
    int caso = 5;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);  
}
void test6(){           //P-n51-k10-d51-v10-c80
    
    const int d = 51;   //numero de cidades
    const int cap = 80; //capacidade cada veiculo 
    int v = 12;         //numero de veiculos 
    int caso = 6;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}
void test7(){           //P-n55-k7-d55-v7-c170
    
    const int d = 55;   //numero de cidades
    const int cap = 170;//capacidade cada veiculo 
    int v = 7;          //numero de veiculos 
    int caso = 7;       
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

void test8(){           //P-n16-k8-d16-v8-c35
    
    const int d = 16;   //numero de cidades
    const int cap = 35; //capacidade cada veiculo
    int v = 9;          //numero de veiculos
    int caso = 8;
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}
void test9(){           //cvrp1
    
    const int d = 450;  //numero de cidades
    const int cap = 52; //capacidade cada veiculo
    int v = 71;         //numero de veiculos 
    int caso = 9;
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}
void test10(){          //cvrp2
    
    const int d = 500 ;   //numero de cidades
    const int cap = 28 ; //capacidade cada veiculo
    int v = 154 ;         //numero de veiculos
    int caso = 10;
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}
void test11(){          //cvrp3
    
    const int d = 550;  //numero de cidades
    const int cap = 74; //capacidade cada veiculo
    int v = 43;          //numero de veiculos
    int caso = 11;
    
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

int main(){  
    
    int opcao = 0;
    bool sair = true;    
    
    while( sair ){       
        
        cout << "\n";
        cout << "**            MENU         **" << endl << endl;
        cout << " 1 - P-n19-k2-d19-v2-c160" << endl;
        cout << " 2 - P-n20-k2-d20-v2-c160" << endl;
        cout << " 3 - P-n23-k8-d23-v8-c40" << endl;
        cout << " 4 - P-n45-k5-d45-v5-c150" << endl;
        cout << " 5 - P-n50-k10-d50-v10-c100" << endl;
        cout << " 6 - P-n51-k10-d51-v10-c80" << endl;
        cout << " 7 - P-n55-k7-d55-v7-c170" << endl;
        cout << " 8 - P-n16-k8-d16-v8-c35" << endl;  
        cout << " 9 - cvrp1" << endl;
        cout << "10 - cvrp2" << endl;
        cout << "11 - cvrp3" << endl;
        cout << "12 - Sair" << endl;
        
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao){
            case 12:
                sair = false;
                break;

            case 1:
                system("cls");                
                test1();                
                break;

            case 2:
                system("cls");
                test2();
                break;

            case 3:
                system("cls");
                test3();
                break;

            case 4:
                system("cls");
                test4();
                break;

            case 5:
                system("cls");
                test5();
                break;

            case 6:
                system("cls");
                test6();
                break;

            case 7:
                system("cls");
                test7();
                break;
            
            case 8:
                system("cls");
                test8();
                break;

            case 9:
                system("cls");
                test9();
                break;

            case 10:
                system("cls");
                test10();
                break;

            case 11:
                system("cls");
                test11();
                break;
        
            default:
                break;
        }
    
    }      
    return 0;
} 