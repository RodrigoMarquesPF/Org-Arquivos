/* Carlos Henrique de Oliveira Pereira
Rodrigo Marques Pau Ferro */



#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c;
	int inicio, fim, meio;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}


	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep_ordenado.dat","rb");
	
	

	fseek(f,0,SEEK_END);
    inicio =0;
	fim=(ftell(f)/sizeof(Endereco))-1;
	

	while(inicio <= fim){
		c++;

		meio = (inicio+fim)/2;
		fseek(f,meio*sizeof(Endereco),SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);

       
		if(strncmp(argv[1],e.cep,8)==0)
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
			
		}else{
			if(strncmp(argv[1],e.cep,8)<0){
				
				fim= meio-1;
			}else{
				
				inicio=meio+1;
			}
			
		}
		
	}
	
	
	printf("Total de Buscas: %d\n", c);
	fclose(f);
}