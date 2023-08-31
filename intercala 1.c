/*Rodrigo Marques Pau Ferro
    Marcos Samuel de Mesquita Faben
    Carlos Henrique de Oliveira Pereira*/

#include <stdio.h>
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


int main()
{
    FILE *fa;
    FILE *fb;
    FILE *fc;
    Endereco ea, eb;

    fa=fopen("cep_a.dat","rb");
    fb=fopen("cep_b.dat","rb");
    fc=fopen("saida.dat","wb");

    fread(&ea,sizeof(Endereco),1,fa);
    fread(&eb,sizeof(Endereco),1,fb);

    while(!feof(fa) && !feof(fb))
    {
        if(strncmp(ea.cep,eb.cep,8)<0){
            fwrite(&ea,sizeof(Endereco),1,fc);
            fread(&ea,sizeof(Endereco),1,fa);
        }
        else{
            fwrite(&eb,sizeof(Endereco),1,fc);
            fread(&eb,sizeof(Endereco),1,fb);
        }
 
        
    }

           while (!feof(fa))
        {
            fwrite(&ea,sizeof(Endereco),1,fc);
            fread(&ea,sizeof(Endereco),1,fa);
        }
         while (!feof(fb))
        {
            fwrite(&eb,sizeof(Endereco),1,fc);
            fread(&eb,sizeof(Endereco),1,fb);
        }

    fclose(fa);
    fclose(fb);
    fclose(fc);

}