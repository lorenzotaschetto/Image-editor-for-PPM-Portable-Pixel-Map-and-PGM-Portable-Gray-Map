//Struct

typedef struct
{
    int alturaNovo;
    int larguraNovo;
    char tipoNovo[3];
    int corNovo;
}Arquivo;

//Funções

void LerP3();
void P2(Arquivo arquivo, int matrizNovo[arquivo.alturaNovo][arquivo.larguraNovo], int altura, int largura, int cor, int matriz[altura][largura], int seleciona);


