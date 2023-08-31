#include <stdio.h>
#include <string.h>

#define TAMANHO 256


int main(int argc, char** argv)
{
    FILE *entrada;
    char c;
    int v [TAMANHO];

	if(argc != 2)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"rt");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

    /*Usei a funsão memset() para preencher o array v 
    com o valor 0.*/
	memset( v, 0, sizeof(v));
    
    c = fgetc(entrada);
    
    while(c!=EOF){

        v[c]++;
        c = fgetc(entrada);

    }
    
    /*Usei um if para separar os sinais de controle (não-imprimível) do byte 0 ao 31 e o 127,  dos sinais gráficos que sao imprimiveis*/
    for (int i = 0; i < TAMANHO; i++)
    {
        if(v[i]!=0){
            if(i<=31 || i==127){
                printf("O byte [ %d ] e um sinal de controle (não-imprimível) [ %c ] que aparece %d vez \n",i,i,v[i]);
            }else{
                if(v[i]==1){
                    printf("O byte [ %d ] de sinal gráfico [ %c ] que aparece %d vez \n",i,i,v[i]);
                }else{
                    printf("O byte [ %d ] de sinal gráfico [ %c ] que aparece %d vezes \n",i,i,v[i]);
                }
            }
        }
    }
    



	fclose(entrada);
	
	return 0;
}