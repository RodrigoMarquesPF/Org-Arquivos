/* Rodrigo Marques Pau Ferro
Implementação de um arquivo de índice
E necessario colocar um cep para realucar a busca ./indice 00000000
Este programa necessita do arquico cep.dat.
Sera criado mais dois arquivos para realizar a busca, o arquivo CepsComIndice.dat que seram os ceps copiados do arquivo cep.dat
junto com os seus indices, e o arquivo cep_ordenado.dat que sera um arquivo ordenado pelos ceps  do arquivo CepsComIndice.dat, para
poder realizar a busca binaria.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;



struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};



typedef struct _Indice Indice;

struct _Indice
{
	
    char cep[8];
	int indice;
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Indice*)e1)->cep,((Indice*)e2)->cep,8);
}


void busca_binaria(char* nome_arq, char* cep){
    FILE* arquivo;
    arquivo = fopen(nome_arq,"rb"); // abrindo o arquivo cep_ordenado.dat, para leitura
    Indice o2;
    Endereco e2;


    int inicio, fim, meio;
	
	fseek(arquivo,0,SEEK_END);
    inicio =0;
	fim=(ftell(arquivo)/sizeof(Indice))-1;
	
	while(inicio <= fim){
		

		meio = (inicio+fim)/2;
		fseek(arquivo,meio*sizeof(Indice),SEEK_SET);
		fread(&o2,sizeof(Indice),1,arquivo);
		if(strncmp(cep,o2.cep,8)==0) //Se ele achar o cep no cep_ordenado.dat ele entra no while e abre o arquivo e pega o indice do cep achano no arquivo cep_ordenado.dat
		{
			FILE* fcep =fopen("cep.dat","rb");  // abrindo o arquivo cep.dat, para leitura
			fseek(fcep,o2.indice*sizeof(Endereco),SEEK_SET);
			fread(&e2,sizeof(Endereco),1,fcep);
			fclose(arquivo);// fecha cep_ordenado.dat
			printf("\nO cep procurado foi achado: \n\n");
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\nCEP: %.8s\n\n",e2.logradouro,e2.bairro,e2.cidade,e2.uf,e2.sigla,e2.cep);
			fclose(fcep);// fecha cep.dat
			break;
			
		}else{
			if(strncmp(cep,o2.cep,8)<0){
				
				fim= meio-1;
			}else{
				
				inicio=meio+1;
			}
		}
		
    }
	while(inicio>fim){
		printf("\n\nO cep procurado nao foi achado !\n\n");
		break;
	}
}



int main(int argc, char**argv)
{
    FILE *fcep;
    FILE *fcepIndice;
    Endereco e;
	Indice o;
	Indice *ind;
	int indice =0;
	long posicao, qtd;
	int c;

	if(argc != 2)
	{
		fprintf(stderr, "\n Escreva um cep para realizar a busca \n\n ");
		return 1;
	}


	fcep = fopen("cep.dat","rb");                  // abrindo o arquivo cep.dat que não esta ordenado, para leitura
	fcepIndice = fopen("CepsComIndices.dat","wb");// criando o arquivo CepsComIndices.dat, para escrita

	fread(&e,sizeof(Endereco),1,fcep);
	
	while (!feof(fcep))
	{
		

		strcpy(o.cep, e.cep);
		o.indice= indice;
 		fwrite(&o,sizeof(Indice),1,fcepIndice);
		indice++;
		fread(&e,sizeof(Endereco),1,fcep);
	}

	fclose(fcep); //fecha cep.dat
	fclose(fcepIndice);  //fecha CepsComIndices.dat



	fcepIndice = fopen("CepsComIndices.dat","rb");  // abrindo o arquivo CepsComIndices.dat que não esta ordenado, para leitura
	fseek(fcepIndice,0,SEEK_END);
	posicao = ftell(fcepIndice);
	
	qtd = posicao/sizeof(Indice);
	
	ind = (Indice*) malloc(posicao);
	if(ind == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(fcepIndice);
		return -1;
	}

	rewind(fcepIndice); // Vai para o inicio do arquivo
	fread(ind,sizeof(Indice),qtd,fcepIndice);
	fclose(fcepIndice);  //fecha CepsComIndices.dat
	qsort(ind,qtd,sizeof(Indice),compara);
	

	fcepIndice = fopen("cep_ordenado.dat","wb");   // criando o arquivo cep_ordenado.dat, para escrita

	fwrite(ind,sizeof(Indice),qtd,fcepIndice);
	fclose(fcepIndice);   //fecha cep_ordenado.dat
	
	free(ind);

 	busca_binaria("cep_ordenado.dat",argv[1]);  // Passa o arquivo cep_ordenado.dat e o cep digitado para ser procurado pela busca binaria
			

	return(0);
}