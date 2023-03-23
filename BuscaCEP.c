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
	
	inicio =0;

	fseek(f,0,SEEK_END);
	fim=ftell(f);
	
	


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
				//fseek(f,meio-1,SEEK_SET);
				//fim = ftell(f);
				fim= meio-1;
			}else{
				//fseek(f,meio+1,SEEK_SET);
				//inicio= ftell(f);
				inicio=meio+1;
			}
			fread(&e,sizeof(Endereco),1,f);
		}
		
	}
	



	/*qt = fread(&e,sizeof(Endereco),1,f);
	while(qt > 0)
	{
		c++;
		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep  => strcmp(argv[1],e.cep) == 0
		
		qt = fread(&e,sizeof(Endereco),1,f);		
	}*/
	printf("Total Lido: %d\n", c);
	fclose(f);
}

