#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*--------------------------------------------------------------------*/
/*--------------------------ESTRUTURAS--------------------------------*/
/*--------------------------------------------------------------------*/

typedef struct
{
	char *string;
	int num;
} StructInts;

StructInts structints(char *string, int num){
	StructInts result;
	result.string = string;
	result.num = num;
	return result;
}

/*--------------------------------------------------------------------*/
/*---------------------------FUNÇÕES GERAIS---------------------------*/
/*--------------------------------------------------------------------*/

//Duplica a cadeia s para uma cadeia result e devolve o enderenço de result(copia recem criada)
char *str_dup(const char *s)
{
    char *result = (char *) malloc(strlen(s) + 1);//aloca memoria para result com o comprimento de s
    strcpy(result, s);//copia s para result
    return result;//devolve o endereço de result que é o que foi copiado
}

double round(double x)
{
	return floor(x+0.5);
}

//--------------FUNÇOES DE COMPARAÇAO-----------------------

int string_cmp(StructInts *p, StructInts *q)
{
	return strcmp(p->string, q->string);
}

int string_cmp_v(const void *p, const void *q)
{
	return string_cmp((StructInts *) p, (StructInts *) q);
}

int num_cmp(StructInts *p, StructInts *q)
{
	int result = q->num - p->num;
	if (result == 0)//se for 0, sao iguais
		result = strcmp(p->string, q->string);//e vai-se comparar o y
	return result;
}

int num_cmp_v(const void *p, const void *q)
{
	return num_cmp((StructInts *) p, (StructInts *) q);
}

typedef int (*StructInts_cmp)(StructInts, StructInts);

/*----------------------BUSCA DICOTÓMICA COM STRINGS------------------*/

int StructInts_rank(StructInts *s, int n, const char *x)
{
	int result = 0;
	while (n > 0)
	{
		int m = n / 2;
		if (strcmp(x, s[m].string) <= 0)
			n = m;
 		else
 		{
	 		result += m+1;
 			s += m+1;
	 		n -= m+1;
 		}
	}
 return result;
} 

//Calcula o índice da primeira ocorrência de um valor dado num array ordenado, devolvendo -1, se não houver.
int StructInts_bfind(StructInts *s, int n, const char *x)
{
 int r = StructInts_rank(s, n, x);
 return r < n && strcmp(s[r].string, x) == 0 ? r : -1;
} 

/*---------------------------------------------------------------------*/
/*--------------------------LEITURA E ESCRITA--------------------------*/
/*---------------------------------------------------------------------*/

//Le de um ficheiro, linha a linha, cada conjunto de dois valores e coloca-os nas variaveis da estrutura
//Guarda no array a(de tipo estrutura StructInts), cada conjunto de valores
int structints_read(FILE *f, StructInts *a){
	int result = 0;
	char string[100];
	int popul_num;
  	while (fscanf(f, "%s%d", string, &popul_num) != EOF){
  		a[result++] =	structints(str_dup(string), popul_num);
  	}
  	return result;//devolve o tamanha do array a
}

//Escrever o array de estruturas na consola, forçando o double
void final_write(FILE *f, StructInts *b, int n)
{
    int i;
	for (i = 0; i < n; i++)
		fprintf(f, "%s %f\n", b[i].string, (double)(b[i].num)/1000000);
}

//Escrever o array de estruturas na consola 
void final_write2(FILE *f, StructInts *b, int n)
{
    int i;
	for (i = 0; i < n; i++)
		fprintf(f, "%s %d\n", b[i].string, (b[i].num));
}

/*---------------------------------------------------------------------*/
/*--------------------------PROGRAMA SIRIA-----------------------------*/
/*---------------------------------------------------------------------*/

//Procura no array de pop cada elemento do array fighters
//Caso encontre, copia para o array b, o pais e o quociente desejado
double relative_participation(StructInts *pop, int n, StructInts *fighter, int m, StructInts *b){
	int result = 0;

		for (int j = 0; j < m; j++){
			int dic_place = StructInts_bfind(pop, n, fighter[j].string); 
			if (dic_place >= 0){ 
				b[result++] = structints(str_dup(fighter[j].string), round(((double)(fighter[j].num)/(pop[dic_place].num))*1000000)); 
			}
		}
	return result;
}

void test_relative_participation(char *filestring){
	StructInts pop[100];
	StructInts fighter[100];
	StructInts b[100];
	FILE *f = fopen(filestring, "r");
	assert(f != NULL);
	int n_pop = structints_read(f, pop); //le do ficheiro
	int n_fig = structints_read(stdin, fighter); //ler da consola
	qsort(pop, n_pop, sizeof(StructInts), string_cmp_v); //ordena o array pop
	int n_rel = relative_participation(pop, n_pop, fighter, n_fig, b); //copia para b os pais encontrados(repetidos em ambos os ficheiros) e o quociente de combatentes correspondente
	qsort(b, n_rel, sizeof(StructInts), num_cmp_v); //ordena o array b
	final_write(stdout, b, n_rel); //escreve na consola o array b
}

/*---------------------------------------------------------------------*/
/*--------------------------PROGRAMA BES-------------------------------*/
/*---------------------------------------------------------------------*/

//Enquanto não chegar ao fim dos arrays cheat and valid, compara cada posição e verifica se são iguais.
//Caso sejam iguais, copia para o array b a diferença dos valores de cada array(aldrabice)
//Caso sejam diferentes, avança no array com maior valor (vai ver se o valor de cheat é maior que o de valid, se não for, é porque o valid é que é)
double list_structints(StructInts *cheat, int n, StructInts *valid, int m, StructInts *b, int(*cmp)(StructInts *, StructInts *)){
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)
		if (cmp(&cheat[i], &valid[j]) == 0){
			b[result++] = structints(str_dup(cheat[i].string), (cheat[i].num - valid[j].num));//copia o elemento de a para c
			i++;
			j++;
		}
		else if (cmp(&cheat[i], &valid[j]) > 0)
			j++;
		else
			i++;
	return result;//retorna o tamanho de b
}

void test_list_structints(char *filestring){
	StructInts cheat[100];
	StructInts valid[100];
	StructInts b[100];
	FILE *f = fopen(filestring, "r");
	assert(f != NULL);
	int n_cheat = structints_read(f, cheat);//le do ficheiro
	int n_valid = structints_read(stdin, valid);//le da consola
	qsort(cheat, n_cheat, sizeof(StructInts), string_cmp_v);//ordena o cheat
	qsort(valid, n_valid, sizeof(StructInts), string_cmp_v);//ordena o valid
	int n_list = list_structints(cheat, n_cheat, valid, n_valid, b, string_cmp);//compara-os para encontrar repetidos e escreve em b a aldrabice
	qsort(b, n_list, sizeof(StructInts), num_cmp_v);//ordena o b
	final_write2(stdout, b, n_list);//escreve na consola o array b
}

/*-----------------------------------------------------*/
/*------------------------MAIN-------------------------*/
/*-----------------------------------------------------*/

int main(int argc, char **argv)
{
	char x = *argv[1];
	if (x == 'S') //para escolhermos correr a função do problema da Siria
	{
		test_relative_participation(argv[2]);
	}
	else if(x == 'B') //para escolhermos correr a função do problema do BES
	{
		test_list_structints(argv[2]);
	}
	return 0;
}
