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
	char *country;
	int num;
} Population;

Population population(char *country, int num){
	Population result;
	result.country = country;
	result.num = num;
	return result;
}

/*--------------------------------------------------------------------*/
/*---------------------------Funções Gerais---------------------------*/
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

int country_cmp(Population p, Population q)
{
	return strcmp(p.country, q.country);
}

int num_cmp(Population p, Population q)
{
	int result = q.num - p.num;
	if (result == 0)//de ser 0, sao iguais
		result = strcmp(p.country, q.country);//e vai-se comparar o y
	return result;
}

typedef int (*Population_cmp)(Population, Population);

//-----------------MERGESORT PARA ESTRUTURAS-----------------

int Population_copy (const Population *a, int n, Population *b)
{
	if (n < 0)
		n = 0;
	memmove(b, a, n * sizeof(Population));//copia os elementos de a(q como sao ints têm 4 bytes cada um)
								  //para o array b
	return n;
}

int Population_merge (const Population *a, int n, const Population *b, int m, Population *c, int(*cmp)(Population, Population))
{
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)//enquanto nao chegar ao fim dos arrays a e b
		if (cmp(a[i], b[j]) <= 0)//compara as posiçoes de a e b, se b for maior:
			c[result++] = a[i++];//copia o elemento de a para c
		else
			c[result++] = b[j++];//se nao, copia o elemento de b para c
	result += Population_copy(a + i, n - i, c+result);//quando um dos arrays chega ao fim,
	result += Population_copy(b + j, m - j, c+result);//copia-se o restante do outro para o array c
	return result;//retorna o tamanho de c
}

void Population_sort_i(Population *a, int n, Population *b, int(*cmp)(Population, Population))
{
	if (n > 1)
	{
		int m = n / 2;
		Population_sort_i(a, m, b, cmp);
		Population_sort_i(a+m, n-m, b, cmp);
		Population_merge(a, m, a+m, n-m, b, cmp);
		Population_copy(b, n, a);
	}
}

void Population_sort(Population *a, int n, int(*cmp)(Population, Population))
{
	Population *b = malloc(n * sizeof(Population));//aloca a memoria para b
	Population_sort_i(a, n, b, cmp);//depois ordena recursivamente 
}

/*----------------------BUSCA DICOTÓMICA COM STRINGS------------------*/

int Population_rank(Population *s, int n, const char *x)
{
	int result = 0;
	while (n > 0)
	{
		int m = n / 2;
		if (strcmp(x, s[m].country) <= 0)
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
int Population_bfind(Population *s, int n, const char *x)
{
 int r = Population_rank(s, n, x);
 return r < n && strcmp(s[r].country, x) == 0 ? r : -1;
} 

/*---------------------------------------------------------------------*/
/*--------------------------PROGRAMA-----------------------------------*/
/*---------------------------------------------------------------------*/

//Ler de um ficheiro para um array preenchido com o construtor population, q é do tipo estrutura Population
int struct_read(FILE *f, Population *a){
	int result = 0;
	char country[100];//dimensoes arbitrarias
	int popul_num;
  	while (fscanf(f, "%s%d", country, &popul_num) != EOF){ //le 2 valores do ficheiro f, linha a linha, e coloca-os nas variaveis da estrutura
  		a[result++] =	population(str_dup(country), popul_num);//as cadeias lidas são duplicadas para o heap e os endereços são guardados na estrutura.
  	}
  	return result;//devolve o tamanha do array para onde se guardou os valores
}

double relative_participation(Population *pop, int n, Population *fighter, int m, Population *b){
	int result = 0;

		for (int j = 0; j < m; j++){
			int dic_place = Population_bfind(pop, n, fighter[j].country);
			if (dic_place >= 0){
				b[result++] = population(str_dup(fighter[j].country), round(((double)(fighter[j].num)/(pop[dic_place].num))*1000000));
			}
		}
	return result;
}

//Escrever o array de estruturas num ficheiro
void final_write(FILE *f, Population *b, int n)
{
    int i;
	for (i = 0; i < n; i++)
		fprintf(stdout, "%s %f\n", b[i].country, (double)(b[i].num)/1000000); //escreve no ficheiro f, com o formato indicado, cada posiçao de a, q contem os 2 valores da estrutura
}

void test_relative_participation(char *filename){
	Population pop[100];
	Population fighter[100];
	Population b[100];
	FILE *f = fopen(filename, "r");
	assert(f != NULL);
	int n_pop = struct_read(f, pop);
	int n_fig = struct_read(stdin, fighter);
	Population_sort(pop, n_pop, country_cmp);
	int n_rel = relative_participation(pop, n_pop, fighter, n_fig, b);
	Population_sort(b, n_rel, num_cmp);
	final_write(f, b, n_rel);
}

int main(int argc, char *argv[])
{
	test_relative_participation(argv[1]);
	return 0;
}
