#include <stdio.h>
#include <stdlib.h>
#include "complemento.h"

//Funções

///P2
void LerP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], FILE *arq, int seleciona);
void LerP2Novo(Arquivo arquivo, int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void GreenscreenP2(Arquivo arquivo,int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void CortaP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void RotacionaQuadP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo],int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void RotacionaGeralLargP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void RotacionaGeralAltP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura,int largura, int cor, int matriz[altura][largura], int seleciona);
void SalvarP2(Arquivo arquivo, int altura, int largura, int cor, int matriz[altura][largura]);


void LerP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], FILE *arq, int seleciona)
{
    int altura,largura,cor;
    fscanf(arq, "%d", &altura);
    printf("Altura: %d ", altura);

    fscanf(arq, "%d", &largura);
    printf("Largura: %d\n", largura);

    fscanf(arq, "%d", &cor);
    printf("Cor: %d\n", cor);

    //Lê a matriz
    int matriz[altura][largura];
    for(int i=0; i<altura; i++)
    {
        for(int j=0; j<largura; j++)
        {
            fscanf(arq, "%d", &matriz[i][j]);
        }

    }
    //Imprime a matriz
    for(int i=0; i<altura; i++)
    {
        for(int j=0; j<largura; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    fclose(arq);
    P2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona); //Chama o menu
}

void P2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo],int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    int escolha;
    printf("Digite 1 para aplicar efeito greenscreen\n"
            "2 para rotacionar a imagem\n"
            "3 para cortar a imagem e 0 para sair (salvar): \n");
    scanf("%d",&escolha);
    if(escolha != 0)
    {
        switch(escolha)
        {
            case 1:
                LerP2Novo(arquivo,altura,largura,cor,matriz,seleciona);//Lê a imagem de frente
                break;

            case 2:
                if( altura == largura)
                {
                    RotacionaQuadP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar imagem quadrada
                }
                else
                {
                    if(altura > largura)
                    {
                        RotacionaGeralAltP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar a imagem pela altura
                    }
                    else
                    {
                        RotacionaGeralLargP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar a imagem pela largura
                    }
                }
                break;

            case 3:
                CortaP2(arquivo,matrizNovo,largura,altura,cor,matriz,seleciona);//Chama a função de cortar
                break;

            default:
                printf("Digite um numero valido: ");
                break;
        }
    }
    SalvarP2(arquivo,altura,largura,cor,matriz);//Chama função de gravar no arquivo
    exit(0);
}

void LerP2Novo(Arquivo arquivo, int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    FILE *arqNovo;

    char nomeNovo[50];
    printf("Digite o nome do arquivo a ser adicionado ao fundo: ");
    scanf("%s",nomeNovo);

    arqNovo = fopen(nomeNovo, "r");
    if(arqNovo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fscanf(arqNovo, "%s", arquivo.tipoNovo);
    printf("Tipo: %s \n", arquivo.tipoNovo);

    fscanf(arqNovo, "%d", &arquivo.alturaNovo);
    printf("Altura: %d ", arquivo.alturaNovo);

    fscanf(arqNovo, "%d", &arquivo.larguraNovo);
    printf("Largura: %d\n", arquivo.larguraNovo);

    fscanf(arqNovo, "%d", &arquivo.corNovo);
    printf("Cor: %d\n", arquivo.corNovo);

    int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo];
    //Lê a matrizNovo
    for(int i = 0; i < arquivo.alturaNovo; i++)
    {
        for(int j = 0; j < arquivo.larguraNovo; j++)
        {
            fscanf(arqNovo, "%d", &matrizNovo[i][j]);
        }

    }
    //Printar a matrizNovo
    for(int i = 0; i < arquivo.alturaNovo; i++)
    {
        for(int j = 0; j < arquivo.larguraNovo; j++)
        {
            printf("%d ", matrizNovo[i][j]);
        }
        printf("\n");
    }

    fclose(arqNovo);

    if(altura >= arquivo.alturaNovo && largura >= arquivo.larguraNovo && arquivo.tipoNovo[1] == '2')
    {
        GreenscreenP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de greenscreen
    }
    else
    {
        if(arquivo.tipoNovo[1] != '2')
            printf("O arquivo nao e do tipo P2\n");
        if(altura < arquivo.alturaNovo || largura < arquivo.larguraNovo)
            printf("A imagem a ser aplicada e maior que a imagem original\n");
        P2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);
    }
}

void GreenscreenP2(Arquivo arquivo,int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura,int largura, int cor, int matriz[altura][largura], int seleciona)
{
    if(seleciona >= 0)
    {
        int controleCorte;
        printf("Deseja cortar a nova imagem?\n"
               "1-SIM\n"
               "2-NAO\n");
        scanf("%d",&controleCorte);

        if(controleCorte==1)
        {
            seleciona = 0;

            CortaP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);
        }
        else
        {
            printf("Ok, imagem nao cortada\n");
        }
    }
    seleciona = 1;
    int controleGiro;
    printf("Deseja rotacionar a nova imagem?\n"
            "1-SIM\n"
            "2-NAO:\n");
    scanf("%d",&controleGiro);
    if(controleGiro==1)
    {
        seleciona = 0;
        if(arquivo.alturaNovo == arquivo.larguraNovo)
        {
            RotacionaQuadP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar imagem quadrada
        }
        else
        {
            if(arquivo.alturaNovo > arquivo.larguraNovo)
            {
                RotacionaGeralAltP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar a imagem pela altura
            }
            else
            {
                RotacionaGeralLargP2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama a função de rotacionar a imagem pela largura
            }
        }
        printf("Ok, imagem rotacionada\n");
        seleciona = 1;
    }
    else
    {
        printf("Ok, imagem nao rotacionada\n");
    }

    int mascara;
    printf("Digite o valor da cor que deseja remover (o a %d): ",arquivo.corNovo);
    scanf("%d", &mascara);

    //Imprime a matriz sem greenscreen
    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < largura; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //Aplica o greenscreen
    for(int i = 0; i < arquivo.alturaNovo; i++)
    {
        for(int j = 0; j < arquivo.larguraNovo; j++)
        {
            if(matrizNovo[i][j] != mascara)
            {
                matriz[i][j] = matrizNovo[i][j];
            }
        }
    }
    printf("Imagem com efeito greenscreen aplicado\n");
    //Imprime a matriz com greenscreen
    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < largura; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    P2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona);//Chama o menu
}

void RotacionaQuadP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    if(seleciona == 0)
    {
        altura = arquivo.alturaNovo;
        largura = arquivo.larguraNovo;
    }
    int matrizAux1[altura][largura];
    int angulo;

    printf("Digite o angulo a ser rotacionado\n"
                    "1 para 90 graus\n"
                    "2 para 180 graus\n"
                    "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < angulo; i++)
    {
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                if(seleciona == 1)
                    matrizAux1[i][j] = matriz[i][j];
                else
                    matrizAux1[i][j] = matrizNovo[i][j];
            }
        }

        //Rotaciona a matriz
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                if(seleciona == 1)
                    matriz[j][altura-1-i] = matrizAux1[i][j];
                else
                    matrizNovo[j][altura-1-i] = matrizAux1[i][j];
            }
        }

        if(i == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(i == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(i == 2)
            printf("Imagem rotacionada 270 graus\n");
        //Imprime a matriz rotacionada
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                if(seleciona == 1)
                    printf("%d ", matriz[i][j]);
                else
                    printf("%d ", matrizNovo[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    if(seleciona == 1)
    {
        P2(arquivo,matrizNovo,altura,largura,cor,matriz,seleciona); //Chama o menu
    }
}

void RotacionaGeralLargP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo],int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    if(seleciona == 0)
    {
        altura = arquivo.alturaNovo;
        largura = arquivo.larguraNovo;
    }
    int matrizAux3A[largura][largura];
    int matrizAux3B[largura][largura];
    int angulo;
    printf("Digite o angulo a ser rotacionado\n"
                    "1 para 90 graus\n"
                    "2 para 180 graus\n"
                    "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Preenche a matriz auxiliar com -1
    for(int i = 0; i < largura; i++)
    {
        for(int j = 0; j < largura; j++)
        {
            matrizAux3A[i][j] = -1;
        }
    }
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < largura; i++)
    {
        for(int j = 0; j < largura; j++)
        {
            if(i < altura)
            {
                if(seleciona == 1)
                    matrizAux3A[i][j] = matriz[i][j];
                else
                    matrizAux3A[i][j] = matrizNovo[i][j];
            }
        }
    }

    int iRot;
    for(iRot = 0; iRot < angulo; iRot ++)
    {
        //Copia a matriz auxiliar para outra auxiliar
        for(int i = 0; i < largura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                matrizAux3B[i][j] = matrizAux3A[i][j];
            }
        }
        //Rotaciona a matriz
        for(int i = 0; i < largura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                matrizAux3A[j][largura-1-i] = matrizAux3B[i][j];
            }
        }

        if(iRot == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(iRot == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(iRot == 2)
            printf("Imagem rotacionada 270 graus\n");

        //Imprime a matriz rotacionada
        for(int i = 0; i < largura; i++)
        {
            for(int j = 0; j < largura; j++)
            {
                if(matrizAux3A[i][j] >= 0)
                {
                    printf("%d ",matrizAux3A[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    if(seleciona == 1)
        P2(arquivo,matrizNovo,altura,largura,cor,matrizAux3A,seleciona); //Chama o menu
}

void RotacionaGeralAltP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    if(seleciona == 0)
    {
        altura = arquivo.alturaNovo;
        largura = arquivo.larguraNovo;
    }
    int matrizAux2A[altura][altura];
    int matrizAux2B[altura][altura];

    int angulo;
    printf("Digite o angulo a ser rotacionado\n"
                    "1 para 90 graus\n"
                    "2 para 180 graus\n"
                    "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Preenche a matriz auxiliar com -1
    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < altura; j++)
        {
            matrizAux2A[i][j] = -1;
        }
    }
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < altura; j++)
        {
            if(j < largura)
            {
                if(seleciona == 1)
                    matrizAux2A[i][j] = matriz[i][j];
                else
                    matrizAux2A[i][j] = matrizNovo[i][j];
            }
        }
    }
    int iRot;
    for(iRot = 0; iRot < angulo; iRot ++)
    {
        //Copia a matriz auxiliar para outra auxiliar
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < altura; j++)
            {
                matrizAux2B[i][j] = matrizAux2A[i][j];
            }
        }
        //Rotaciona a matriz
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < altura; j++)
            {
                matrizAux2A[j][altura-1-i] = matrizAux2B[i][j];
            }
        }

        if(iRot == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(iRot == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(iRot == 2)
            printf("Imagem rotacionada 270 graus\n");

        //Imprime a matriz rotacionada
        for(int i = 0; i < altura; i++)
        {
            for(int j = 0; j < altura; j++)
            {
                if(matrizAux2A[i][j] >= 0)
                {
                    printf("%d ",matrizAux2A[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    if(seleciona == 1)
        P2(arquivo,matrizNovo,altura,largura,cor,matrizAux2A,seleciona); //Chama o menu
}

void CortaP2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura, int largura, int cor, int matriz[altura][largura], int seleciona)
{
    int x1, x2, y1, y2;

    printf("Digite o valor de x1: ");
    scanf("%d", &x1);
    printf("Digite o valor de x2: ");
    scanf("%d", &x2);

    printf("Digite o valor de y1: ");
    scanf("%d", &y1);
    printf("Digite o valor de y2: ");
    scanf("%d", &y2);
    int matrizCortada[y2-y1][x2-x1];
    //Matriz cortada recebe os valores da matriz original
    for(int i = 0; i < y2-y1; i++)
    {
        for(int j = 0; j < x2-x1; j++)
        {
            if(seleciona == 1)
                matrizCortada[i][j] = matriz[i+y1][j+x1];
            else
                matrizCortada[i][j] = matrizNovo[i+y1][j+x1];

        }
    }
    //Imprime a matriz cortada
    printf("Imagem cortada\n");
    for(int i = 0; i < y2-y1; i++)
    {
        for(int j = 0; j < x2-x1; j++)
        {
            printf("%d ",matrizCortada[i][j]);
        }
        printf("\n");
    }

    if(seleciona == 1)
    {
        P2(arquivo,matrizNovo,y2-y1,x2-x1,cor,matrizCortada,seleciona); //Chama o menu
    }
    else
    {
        seleciona = -1;
        arquivo.alturaNovo = y2-y1;
        arquivo.larguraNovo = x2-x1;
        printf("Ok, imagem cortada\n");

        GreenscreenP2(arquivo,matrizCortada,altura,largura,cor,matriz,seleciona);//Chama o greenscreen
    }
}

void SalvarP2(Arquivo arquivo, int altura, int largura, int cor, int matriz[altura][largura])
{
    FILE *arq;
    char nomeSalvar[50];
    printf("Digite o nome a ser salvo: ");
    scanf("%s",nomeSalvar);
    arq = fopen(nomeSalvar,"w");

    fprintf(arq, "P2\n");
    fprintf(arq, "%d ", altura);
    fprintf(arq, "%d\n", largura);
    fprintf(arq, "%d\n", cor);

    //Imprime a matriz
    for(int i = 0; i < altura; i++)
    {
        for(int j=0; j < largura; j++)
        {
            fprintf(arq, "%d ", matriz[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

int main()
{
    Arquivo arquivo;

    FILE *arq;
    char nome[30];
    char tipo[3];

    printf("Digite o nome do arquivo: ");
    scanf("%s",nome);

    arq = fopen(nome, "r");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo");
        exit(1);
    }

    int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo];

    fscanf(arq, "%s", tipo);
    printf("Tipo: %s\n", tipo);

    int seleciona = 1;
    if(tipo[1] == '3')
    {
        LerP3(arq);

    }
    if( tipo[1] == '2')
    {

        LerP2(arquivo,matrizNovo,arq,seleciona);
    }
}
