#include <iostream>                                     //biblioteca padrao
#include <fstream>                                      //biblioteca ler arquivo
#include <vector>                                       //biblioeca vector                              

using namespace std;

void vizinho_mais_proximo(int d, int cap, int v, int caso ){
	
	ifstream file;
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
	}else{
		file.open("P-n16-k8-d16-v8-c35.txt");
	}
	
	int acc, l, c;
	
	bool flag = false;
    int min = cap;
    int v_atual = 0;//guarda o valor da cidade atual visitada
    int aux;
    int cont = 0;
    int erro = 0;//estouro da capacidade	
    int custo = 0;//somatorio dos custos	
	
	int matrix[d][d];
	vector<int> demanda;//cada indice refencia a demanda desta cidade	
	bool atendido[d];//cada posição indicada para cada cidade em ordem visitada	
	bool chegada [v];//armazena a chegada do veiculo
	int veiculo[v];
	
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
	
	//vizinho mais proximo
    while(v > 0){

        v--;//executa os veiculos do maior ao zero        
        
        if( (veiculo[v] != 0) ){//testa se há capacidade   

            cout << "veiculo " << v << " partiu" << endl << endl;      
            cout << "Rota veiculo " << v << ":" << endl ;
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
                    cout << "\t" <<  v_atual << " para " << 0 << endl;//veiculo nao pode atender, volta para deposito                                                      
                    chegada[v] = true;                    
                    custo = custo + matrix[v_atual][0];//soma o ultimo custo                                                       

                }else{//significa que a demanda foi atendida por nao estar negativo
                    demanda[aux] -= demanda[aux];
                    atendido[aux] = true;//marca a cidade como visitada                   
                    cout << "\t" <<  v_atual << " para " << aux << endl;
                    custo +=min;//atualiza o custo                      
                }               
                                  
                v_atual = aux-1;//desconta o ++ do for para partir da cidade atual
                min = cap;

                for(int k = 0 ; k < d; k++){//verifica se todos foram atendidos
                    if(atendido[k] == true){
                        cont++;
                    }else
                        break;                 
                }
                if( cont == d){//e seta a flag de chegada ao desposito
                   chegada[v] = true; 
                   cout << "\t" <<  aux << " para " << 0 << endl;//aux armazena ultima cidade 
                   custo = custo + matrix[aux][0];//soma ultimo custo
                }

                cont = 0;
                for(int k = 0; k < d; k++ ){//verifica se todos foram visitador e para
                    if( (atendido[k] == true) || ( chegada[v] == true ) ){
                        cont++;
                    }else{
                        cont = 0;//talvez pode dar problema verificar dps
                        break;                            
                    }                              
                }
                if(cont == d){                    
                    flag = true;             
                    break;
                }

            }
            cout << endl;
            cout << "veiculo " << v << " chegou ao deposito " << "com " << veiculo[v] <<  " itens" << endl << endl;
            cout << "custo de tranporte veiculo " << v << " : " << custo << endl; //calcula ultimo custo ao deposito
            cout << "he a solucao inicial deste veiculo a partir do vizinho mais proximo" << endl ;
            cout << "\n" << endl;
            flag = false;//re-init
            v_atual = 0;//re-init    
            cont = 0;//re-init
            custo = 0;                          
        }     
    }
    file.close();
}

void test1(){//P-n19-k2-d19-v2-c160
	
    const int d = 19;//numero de cidades
    const int cap = 160;//capacidade cada veiculo
    int v = 3;//numero de veiculos, modificar para 3
    int caso = 1;       
  	
    cout << endl << endl;   
    vizinho_mais_proximo(d, cap, v, caso);   	
}

void test2(){//P-n20-k2-d20-v2-c160	
	
    const int d = 20;//numero de cidades
    const int cap = 160;//capacidade cada veiculo
    int v = 3;//numero de veiculos, modificador
    int caso = 2;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);	
}

void test3(){//P-n23-k8-d23-v8-c40
	
    const int d = 23;//numero de cidades
    const int cap = 40;//capacidade cada veiculo 
    int v = 10;//numero de veiculos, modificado 
    int caso = 3;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

void test4(){//P-n45-k5-d45-v5-c150	
	
    const int d = 45;//numero de cidades
    const int cap = 150;//capacidade cada veiculo 
    int v = 5;//numero de veiculos 
    int caso = 4;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);	
}
void test5(){//P-n50-k10-d50-v10-c100
	
    const int d = 50;//numero de cidades
    const int cap = 100;//capacidade cada veiculo 
    int v = 11;//numero de veiculos 
    int caso = 5;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);	
}
void test6(){//P-n51-k10-d51-v10-c80
	
    const int d = 51;//numero de cidades
    const int cap = 80;//capacidade cada veiculo 
    int v = 12;//numero de veiculos 
    int caso = 6;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}
void test7(){//P-n55-k7-d55-v7-c170
	
    const int d = 55;//numero de cidades
    const int cap = 170;//capacidade cada veiculo 
    int v = 7;//numero de veiculos 
    int caso = 7;       
  	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

void test8(){//P-n16-k8-d16-v8-c35
	
    const int d = 16;//numero de cidades
    const int cap = 35;//capacidade cada veiculo
    int v = 9;//numero de veiculos
    int caso = 8;
	
    cout << endl << endl;      
    vizinho_mais_proximo(d, cap, v, caso);
}

int main(){  
    
    int opcao = 0;
    bool sair = true;    
    
    while( sair ){       
        
        cout << "\n";
        cout << "**         MENU       **" << endl << endl;
        cout << "1 - P-n19-k2-d19-v2-c160" << endl;
        cout << "2 - P-n20-k2-d20-v2-c160" << endl;
        cout << "3 - P-n23-k8-d23-v8-c40" << endl;
        cout << "4 - P-n45-k5-d45-v5-c150" << endl;
        cout << "5 - P-n50-k10-d50-v10-c100" << endl;
        cout << "6 - P-n51-k10-d51-v10-c80" << endl;
        cout << "7 - P-n55-k7-d55-v7-c170" << endl;
		cout << "8 - P-n16-k8-d16-v8-c35" << endl;	
        cout << "9 - Sair" << endl;
        
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao){
            case 9:
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
        
            default:
                break;
        }
    
    }      
    return 0;
} 