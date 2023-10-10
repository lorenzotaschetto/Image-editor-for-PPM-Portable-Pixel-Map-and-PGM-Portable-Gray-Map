#include <stdio.h>
#include <stdlib.h>

#include "complemento.h"

Arquivo arquivo;

//Struct
typedef struct
{
    int altura;
    int largura;
    int cor;
}ArquivoP3;

//Funções

///P3
void P3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void LerP3Novo();
void GreenscreenP3(ArquivoP3 arquivoNovo, int matrizNovo[arquivoNovo.altura][arquivoNovo.largura][3], ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void GrayScaleP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void CortaP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void RotacionaQuadP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void RotacionaGeralLargP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void RotacionaGeralAltP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);
void SalvarP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3]);



void LerP3(FILE *arq)
{

    ArquivoP3 arquivoP3;

    fscanf(arq, "%d", &arquivoP3.altura);
    printf("Altura: %d ", arquivoP3.altura);

    fscanf(arq, "%d", &arquivoP3.largura);
    printf("Largura: %d\n", arquivoP3.largura);

    fscanf(arq, "%d", &arquivoP3.cor);
    printf("Cor: %d\n", arquivoP3.cor);

    int matriz[arquivoP3.altura][arquivoP3.largura][3];

    //Lê a matriz
    for(int i=0; i<arquivoP3.altura; i++)
    {
       for(int j=0; j<arquivoP3.largura; j++)
       {
          for(int k=0; k<3; k++)
          {
             fscanf(arq, "%d", &matriz[i][j][k]);
          }
       }
    }
    //Imprime a matriz
    for(int i=0; i<arquivoP3.altura; i++)
    {
        for(int j=0; j<arquivoP3.largura; j++)
        {
            for(int k=0; k<3; k++)
            {
                printf("%d ", matriz[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    fclose(arq);
    P3(arquivoP3,matriz); //Chama o menu
}

void P3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int escolha;
    printf("Digite 1 para aplicar efeito greenscreen\n"
            "2 para rotacionar a imagem\n"
            "3 para cortar a imagem\n"
            "4 para aplicar grayscale e 0 para sair (salvar): \n");
    scanf("%d",&escolha);
    if(escolha != 0)
    {
        switch(escolha)
        {
            case 1:
                LerP3Novo(arquivoP3,matriz);//Lê a imagem de frente
                break;

            case 2:
                if(arquivoP3.altura == arquivoP3.largura)
                {
                    RotacionaQuadP3(arquivoP3,matriz);//Chama a função de rotacionar imagem quadrada
                }
                else
                {
                    if(arquivoP3.altura > arquivoP3.largura)
                    {
                        RotacionaGeralAltP3(arquivoP3,matriz);//Chama a função de rotacionar a imagem pela altura
                    }
                    else
                    {
                        RotacionaGeralLargP3(arquivoP3,matriz);//Chama a função de rotacionar a imagem pela largura
                    }
                }
                break;

            case 3:
                CortaP3(arquivoP3,matriz);//Chama a função de cortar
                break;

            case 4:
                GrayScaleP3(arquivoP3,matriz);
                break;

            default:
                printf("Digite um numero valido: ");
                break;
        }
    }
    SalvarP3(arquivoP3,matriz);//Chama função de gravar no arquivo
    exit(0);
}

void LerP3Novo(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura])
{
    ArquivoP3 arquivoNovo;

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

    fscanf(arq, "%s", tipo);
    printf("Tipo: %s\n", tipo);

    fscanf(arq, "%d", &arquivoNovo.altura);
    printf("Altura: %d ", arquivoNovo.altura);

    fscanf(arq, "%d", &arquivoNovo.largura);
    printf("Largura: %d\n", arquivoNovo.largura);

    fscanf(arq, "%d", &arquivoNovo.cor);
    printf("Cor: %d\n", arquivoNovo.cor);

    int matrizNovo[arquivoNovo.altura][arquivoNovo.largura][3];

    //Lê a matriz
    for(int i=0; i<arquivoNovo.altura; i++)
    {
        for(int j=0; j<arquivoNovo.largura; j++)
        {
            for(int k=0; k<3; k++)
            {
                fscanf(arq, "%d", &matrizNovo[i][j][k]);
            }
        }
    }
    //Imprime a matriz
    for(int i=0; i<arquivoNovo.altura; i++)
    {
        for(int j=0; j<arquivoNovo.largura; j++)
        {
            for(int k=0; k<3; k++)
            {
                printf("%d ", matrizNovo[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    fclose(arq);

    if(arquivoP3.altura >= arquivoNovo.altura && arquivoP3.largura >= arquivoNovo.largura && tipo[1] == '3')
    {
        GreenscreenP3(arquivoNovo,matrizNovo,arquivoP3,matriz);//Chama a função de greenscreen
    }
    else
    {
        if(tipo[1] != '3')
            printf("O arquivo nao e do tipo P2\n");
        if(arquivoP3.altura < arquivoNovo.altura || arquivoP3.largura < arquivoNovo.largura)
            printf("A imagem a ser aplicada e maior que a imagem original\n");
        P3(arquivoP3,matriz);
    }
}

void GreenscreenP3(ArquivoP3 arquivoNovo, int matrizNovo[arquivoNovo.altura][arquivoNovo.largura][3], ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int mascara;
    printf("Digite o valor da cor que deseja remover (o a %d): ",arquivoNovo.cor);
    scanf("%d", &mascara);

    //Imprime a matriz sem greenscreen
    for(int i = 0; i < arquivoP3.altura; i++)
    {
        for(int j = 0; j < arquivoP3.largura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                printf("%d ", matriz[i][j][k]);
            }
        }
        printf("\n");
    }
    printf("\n");
    //Aplica o greenscreen
    for(int i = 0; i < arquivoNovo.altura; i++)
    {
        for(int j = 0; j < arquivoNovo.largura; j++)
        {
            if(matrizNovo[i][j][0] != mascara && matrizNovo[i][j][1] != mascara && matrizNovo[i][j][2] != mascara)
            {
                matriz[i][j][0] = matrizNovo[i][j][0];
                matriz[i][j][1] = matrizNovo[i][j][1];
                matriz[i][j][2] = matrizNovo[i][j][2];
            }
        }
    }

    printf("Imagem com efeito greenscreen aplicado\n");
    //Imprime a matriz com greenscreen
    for(int i = 0; i < arquivoP3.altura; i++)
    {
        for(int j = 0; j < arquivoP3.largura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                printf("%d ", matriz[i][j][k]);
            }
        }
        printf("\n");
    }
    P3(arquivoP3,matriz); //Chama o menu
}

void GrayScaleP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int media;
    int matrizP2[arquivoP3.altura][arquivoP3.largura];
    //Aplicar o efeito grayscale
    for(int i=0; i<arquivoP3.altura; i++)
    {
        for(int j=0; j<arquivoP3.largura; j++)
        {
            media = (matriz[i][j][0] + matriz[i][j][1] + matriz[i][j][2])/3;
            matrizP2[i][j] = media;
        }
    }
    printf("Efeito GrayScale aplicado\n");
    //Imprimir a matriz
    for(int i=0; i<arquivoP3.altura; i++)
    {
        for(int j=0; j<arquivoP3.largura; j++)
        {
            printf("%d ", matrizP2[i][j]);
        }
        printf("\n");
    }
    int altura = arquivoP3.altura;
    int largura = arquivoP3.largura;
    int cor = 15;
    int seleciona = 1;

    P2(arquivo,matrizP2,altura,largura,cor,matrizP2,seleciona);//Chama o menu de P2
}

void CortaP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
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
    int matrizCortada[y2-y1][x2-x1][3];
    //Matriz cortada recebe os valores da matriz original
    for(int i = 0; i < y2-y1; i++)
    {
        for(int j = 0; j < x2-x1; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                matrizCortada[i][j][k] = matriz[i+y1][j+x1][k];
            }
        }
    }
    //Imprime a matriz cortada
    printf("Matriz cortada: \n");
    for(int i = 0; i < y2-y1; i++)
    {
        for(int j = 0; j < x2-x1; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                printf("%d ", matrizCortada[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
    arquivoP3.altura = y2-y1;
    arquivoP3.largura = x2-x1;
    P3(arquivoP3,matrizCortada);  //Chama o menu de P3
}

void RotacionaQuadP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int matrizAux1[arquivoP3.altura][arquivoP3.largura][3];
    int angulo;

    printf("Digite o angulo a ser rotacionado\n"
            "1 para 90 graus\n"
            "2 para 180 graus\n"
            "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < angulo; i++)
    {
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matrizAux1[i][j][k] = matriz[i][j][k];
                }
            }
        }

        //Rotaciona a matriz
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matriz[j][arquivoP3.altura-1-i][k] = matrizAux1[i][j][k];
                }
            }
        }

        if(i == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(i == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(i == 2)
            printf("Imagem rotacionada 270 graus\n");
        //Imprime a matriz rotacionada
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k ++)
                {
                    printf("%d ", matriz[i][j][k]);
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
    P3(arquivoP3,matriz); //Chama o menu
}

void RotacionaGeralLargP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int matrizAux3A[arquivoP3.largura][arquivoP3.largura][3];
    int matrizAux3B[arquivoP3.largura][arquivoP3.largura][3];
    int angulo;
    printf("Digite o angulo a ser rotacionado\n"
            "1 para 90 graus\n"
            "2 para 180 graus\n"
            "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Preenche a matriz auxiliar com -1
    for(int i = 0; i < arquivoP3.largura; i++)
    {
        for(int j = 0; j < arquivoP3.largura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                matrizAux3A[i][j][k] = -1;
            }
        }
    }
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < arquivoP3.largura; i++)
    {
        for(int j = 0; j < arquivoP3.largura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                if(i < arquivoP3.altura)
                {
                    matrizAux3A[i][j][k] = matriz[i][j][k];
                }
            }
        }
    }

    int iRot;
    for(iRot = 0; iRot < angulo; iRot ++)
    {
        //Copia a matriz auxiliar para outra auxiliar
        for(int i = 0; i < arquivoP3.largura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matrizAux3B[i][j][k] = matrizAux3A[i][j][k];
                }
            }
        }
        //Rotaciona a matriz
        for(int i = 0; i < arquivoP3.largura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matrizAux3A[j][arquivoP3.largura-1-i][k] = matrizAux3B[i][j][k];
                }
            }
        }

        if(iRot == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(iRot == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(iRot == 2)
            printf("Imagem rotacionada 270 graus\n");

        //Imprime a matriz rotacionada
        for(int i = 0; i < arquivoP3.largura; i++)
        {
            for(int j = 0; j < arquivoP3.largura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    if(matrizAux3A[i][j][k] >= 0)
                    {
                        printf("%d ",matrizAux3A[i][j][k]);
                    }
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
    P3(arquivoP3,matrizAux3A); //Chama o menu
}

void RotacionaGeralAltP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    int matrizAux2A[arquivoP3.altura][arquivoP3.altura][3];
    int matrizAux2B[arquivoP3.altura][arquivoP3.altura][3];
    int angulo;
    printf("Digite o angulo a ser rotacionado\n"
            "1 para 90 graus\n"
            "2 para 180 graus\n"
            "3 para 270 graus:\n ");
    scanf("%d",&angulo);
    //Preenche a matriz auxiliar com -1
    for(int i = 0; i < arquivoP3.altura; i++)
    {
        for(int j = 0; j < arquivoP3.altura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                matrizAux2A[i][j][k] = -1;
            }
        }
    }
    //Copia a matriz original para a matriz auxiliar
    for(int i = 0; i < arquivoP3.altura; i++)
    {
        for(int j = 0; j < arquivoP3.altura; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                if(j < arquivoP3.largura)
                {
                    matrizAux2A[i][j][k] = matriz[i][j][k];
                }
            }
        }
    }

    int iRot;
    for(iRot = 0; iRot < angulo; iRot ++)
    {
        //Copia a matriz auxiliar para outra auxiliar
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.altura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matrizAux2B[i][j][k] = matrizAux2A[i][j][k];
                }
            }
        }
        //Rotaciona a matriz
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.altura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    matrizAux2A[j][arquivoP3.altura-1-i][k] = matrizAux2B[i][j][k];
                }
            }
        }

        if(iRot == 0)
            printf("Imagem rotacionada 90 graus\n");
        if(iRot == 1)
            printf("Imagem rotacionada 180 graus\n");
        if(iRot == 2)
            printf("Imagem rotacionada 270 graus\n");

        //Imprime a matriz rotacionada
        for(int i = 0; i < arquivoP3.altura; i++)
        {
            for(int j = 0; j < arquivoP3.altura; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    if(matrizAux2A[i][j][k] >= 0)
                    {
                        printf("%d ",matrizAux2A[i][j][k]);
                    }
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
    P3(arquivoP3,matrizAux2A); //Chama o menu
}

void SalvarP3(ArquivoP3 arquivoP3, int matriz[arquivoP3.altura][arquivoP3.largura][3])
{
    FILE *arq;
    char nomeSalvar[50];
    printf("Digite o nome a ser salvo: ");
    scanf("%s",nomeSalvar);
    arq = fopen(nomeSalvar,"w");

    fprintf(arq, "P3\n");
    fprintf(arq, "%d ", arquivoP3.altura);
    fprintf(arq, "%d\n", arquivoP3.largura);
    fprintf(arq, "%d\n", arquivoP3.cor);

    //Imprime a matriz
    for(int i = 0; i < arquivoP3.altura; i++)
    {
        for(int j = 0; j < arquivoP3.largura; j++)
        {
            for(int k  = 0; k < 3; k++)
            {
                fprintf(arq, "%d ", matriz[i][j][k]);
            }
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
}
