#include <stdio.h>
#include <string.h>

unsigned int randaux()
{
  static long seed=1;
  return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

void iniciarjogo(){
    printf("    [1] [2] [3] [4] [5] [6] [7] [8]\n");

    for(int i=0; i<=7; i++){
        printf("[%d] ", i+1);

        for(int j=0; j<=7;j++){
            printf("### ");
        }

        if(i!=7)
            printf("\n");
    }
}

//Resolução presente no enunciado
void Baralhar(int v[], int n){

    int i, j, aux;
    for (i=0; i<n-1; i++){
        j=i+randaux()%(n-i);
        aux=v[i];
        v[i]=v[j];
        v[j]=aux;
    }
}

void criar(char *nb[8][8], char *b[], int v[], int n){
    int k=0, l;

    for(int i=0; i<=7; i++){
        for(int j=0; j<=7;j++){
            l=v[k];
            nb[j][i] = b[l];
            k++;
        }
    }


}
//eliminar as cartas do baralho
void remover(char *cartas[4], char *nb[8][8]){
    for(int i=0; i<=7; i++){
        for(int j=0; j<=7;j++){
            for(int k=0; k<4; k++){
                if(cartas[k]==nb[i][j]){
                    nb[i][j]="   ";
                }
            }
        }
    }
}


//verifica a jogada e verifica se e para eliminar as cartas do baralho
void verificar(char *cartasjogadas[4], char *nb[8][8]){
    int nr=0, v=1;
    char ch;
    for(int i=0; i<4; i++){
        if(cartasjogadas[i] !=  NULL){
            nr++;
        }
    }
    if(nr==1){
        remover(cartasjogadas, nb);
    }else if(nr>1){
        for(int i=0; i<3; i++, v=1){
            ch=cartasjogadas[0][i];
            for(int j=1; j<nr; j++){
                if(ch != cartasjogadas[j][i]){
                    j=4;
                    v=0;
                }
            }
            if(v==1){
                remover(cartasjogadas, nb);
                i=4;
            }
        }
    }
}

 void mostrar(char *nb[8][8], int n[], int *ci){
    int v, m=0;
    char *cartasjogadas[4] = {};
    //print do baralho no formato 8x8 com apenas as posições que o jogador deu à mostra
    if(*ci<5){
        printf("\n    [1] [2] [3] [4] [5] [6] [7] [8]\n");
    }
    for(int i=0; i<=7; i++){
        if(*ci<5){
            printf("[%d] ", i+1);
        }
        for(int j=0; j<=7;j++){
            v=0;
            for(int p=0; p<4; p++){
                int col, linha;
                col=(n[p]/10)-1;
                linha=(n[p]%10)-1;
                if((col>=0 && col<8) && (linha>=0 && linha<8)){
                    if(col==j && linha==i){
                        if(*ci<5){
                            printf("%s ", nb[i][j]);
                        }
                        cartasjogadas[m]=nb[i][j];
                        v=1;
                        m++;
                    }
                }else{
                    p=5;
                }
            }
            if(v==0){
                if(nb[i][j] == "   "){
                    if(*ci<5){
                            printf("%s ", nb[i][j]);
                    }
                }else{
                    if(*ci<5){
                        printf("### ");
                    }
                }
            }
        }
        if(i!=7)
            if(*ci<5){
                printf("\n");
            }
    }
     (*ci)++;
     verificar(cartasjogadas, nb); //verificar se o operador, numero ou naipe são iguais nas cartas jogadas
}

//verifica se a jogada é valida
int validajogada(char *nb[8][8], int n[4]){
    for(int i=0; i<4; i++){
        int col, linha;
        col=(n[i]/10)-1;
        linha=(n[i]%10)-1;
        if((col>=0 && col<8) && (linha>=0 && linha<8)){
            if(nb[linha][col] == "   "){
                return 1;
            }
        }
    }
    return 0;
}

//verifica se o baralho esta vazio
int baralhovazio(char *nb[8][8], int *conta){
    for(int i=0; i<=7; i++){
        for(int j=0; j<=7;j++){
            if(nb[i][j] != "   "){
                return 0;
            }
        }
    }
    *conta-=1;
    return 1;
}

int posicoesinvalidas(int n[4]){
    int contador = 0;
    for(int i=0; i<=3;i++){
        int col, linha;
        col=(n[i]/10)-1;
        linha=(n[i]%10)-1;
        if((col>=0 && col<8) && (linha>=0 && linha<8)){
            return 0;
        }else{
            contador++;
        }
    }
    if(contador == 4){
        return 1;
    }
}
int jogadamaquina(char *nb[8][8]){
    int m;

    for(int i=0; i<8; i++){
        for(int j=0; j<8;j++){
            if(nb[i][j] != "   "){
                m=(j+1)*10;
                m+=(i+1);
                return m;
            }
        }
    }

}
int jogada(char *nb[8][8], int *conta){
    int n[4]={}, fim=0, ci=1, maq=0;
    char s[12];
    do
    {
        for(int r=0; r<4; r++){
            n[r]=0;
        }
        if(maq==0){
            memset(s, 0, sizeof(s));
            //s[0]='\0';
            //pedir a jogada ao jogador
            fflush(stdin);
            fgets(s, sizeof(s), stdin);
            //converter a string da jogada em inteiros
            for(int i=0, j=0; i<=10; i=i+3, j++){
                if(s[i]!=' '){
                    sscanf(s+i,"%d", &n[j]);
                }
            }
        }else{
            n[0]=jogadamaquina(nb);
        }
        (*conta)++;
        fim=validajogada(nb, n);
        if(maq==0){
            maq = posicoesinvalidas(n);
        }
        if(fim == 0){
            mostrar(nb, n, &ci);
            fim = baralhovazio(nb, conta);
        }
    }while(fim==0);

}

int imprimefinal(char *nb[8][8]){
    int restantes=0;
    printf("\n    [1] [2] [3] [4] [5] [6] [7] [8]\n");
    for(int i=0; i<=7; i++){
        printf("[%d] ", i+1);
        for(int j=0; j<=7;j++){
            if(nb[i][j] == "   "){
                printf("    ");
            }else{
                printf("### ");
                restantes++;
            }
        }
        if(i!=7)
            printf("\n");
    }
    return restantes;
}

void fimjogo(int *conta, char *nb[8][8]){
    int cartasrestantes=0;
    cartasrestantes=imprimefinal(nb);
    printf("\nJogo com %d jogadas. Restam %d cartas.", *conta, cartasrestantes);
}

void main()
{
    int desperdicio, i, codmax, vetordecods[63], conta;
    char *novobaralho[8][8];

    char *baralho[] = {
        "+1A",
        "+1B",
        "+1C",
        "+1D",
        "+2A",
        "+2B",
        "+2C",
        "+2D",
        "+3A",
        "+3B",
        "+3C",
        "+3D",
        "+4A",
        "+4B",
        "+4C",
        "+4D",
        "-1A",
        "-1B",
        "-1C",
        "-1D",
        "-2A",
        "-2B",
        "-2C",
        "-2D",
        "-3A",
        "-3B",
        "-3C",
        "-3D",
        "-4A",
        "-4B",
        "-4C",
        "-4D",
        "*1A",
        "*1B",
        "*1C",
        "*1D",
        "*2A",
        "*2B",
        "*2C",
        "*2D",
        "*3A",
        "*3B",
        "*3C",
        "*3D",
        "*4A",
        "*4B",
        "*4C",
        "*4D",
        "/1A",
        "/1B",
        "/1C",
        "/1D",
        "/2A",
        "/2B",
        "/2C",
        "/2D",
        "/3A",
        "/3B",
        "/3C",
        "/3D",
        "/4A",
        "/4B",
        "/4C",
        "/4D"
    };

    scanf("%d", &desperdicio);
    for(i=0; i<desperdicio; i++)
        randaux();

    //codmax é o codigo da ultima carta e o tamanho do array. codmax+1 sera o numero de cartas
    codmax = 63;

    //criar vetor com os codigos das cartas
    for(int i=0; i<=codmax; i++)
        vetordecods[i] = i;


    Baralhar(vetordecods, codmax+1);

    //criar um baralho com os codigos baralhados
    criar(novobaralho, baralho, vetordecods, codmax);

    conta =0;
    iniciarjogo();
    //efetuar jogada (pedir codigos ao jogador e mostrar as cartas escolhidas)
    jogada(novobaralho, &conta);

    fimjogo(&conta, novobaralho);


}

