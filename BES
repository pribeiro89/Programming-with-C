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
	char *name;
	int investment;
} Aldrabice;

Aldrabice aldrabice(char *name, int investment){
	Aldrabice result;
	result.name = name;
	result.investment = investment;
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

//--------------FUNÇOES DE COMPARAÇAO-----------------------

int name_cmp(Aldrabice p, Aldrabice q)
{
	return strcmp(p.name, q.name);
}

int investment_cmp(Aldrabice p, Aldrabice q)
{
	int result = q.investment - p.investment;
	if (result == 0)//de ser 0, sao iguais
		result = strcmp(p.name, q.name);//e vai-se comparar o y
	return result;
}

typedef int (*Aldrabice_cmp)(Aldrabice, Aldrabice);

//-----------------MERGESORT PARA ESTRUTURAS-----------------

int Aldrabice_copy (const Aldrabice *a, int n, Aldrabice *b)
{
	if (n < 0)
		n = 0;
	memmove(b, a, n * sizeof(Aldrabice));//copia os elementos de a(q como sao ints têm 4 bytes cada um)
								  //para o array b
	return n;
}

int Aldrabice_merge (const Aldrabice *a, int n, const Aldrabice *b, int m, Aldrabice *c, int(*cmp)(Aldrabice, Aldrabice))
{
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)//enquanto nao chegar ao fim dos arrays a e b
		if (cmp(a[i], b[j]) <= 0)//compara as posiçoes de a e b, se b for maior:
			c[result++] = a[i++];//copia o elemento de a para c
		else
			c[result++] = b[j++];//se nao, copia o elemento de b para c
	result += Aldrabice_copy(a + i, n - i, c+result);//quando um dos arrays chega ao fim,
	result += Aldrabice_copy(b + j, m - j, c+result);//copia-se o restante do outro para o array c
	return result;//retorna o tamanho de c
}

void Aldrabice_sort_i(Aldrabice *a, int n, Aldrabice *b, int(*cmp)(Aldrabice, Aldrabice))
{
	if (n > 1)
	{
		int m = n / 2;
		Aldrabice_sort_i(a, m, b, cmp);
		Aldrabice_sort_i(a+m, n-m, b, cmp);
		Aldrabice_merge(a, m, a+m, n-m, b, cmp);
		Aldrabice_copy(b, n, a);
	}
}

void Aldrabice_sort(Aldrabice *a, int n, int(*cmp)(Aldrabice, Aldrabice))
{
	Aldrabice *b = malloc(n * sizeof(Aldrabice));//aloca a memoria para b
	Aldrabice_sort_i(a, n, b, cmp);//depois ordena recursivamente 
}

/*----------------------BUSCA DICOTÓMICA COM STRINGS------------------*/

int Aldrabice_rank(Aldrabice *s, int n, const char *x)
{
	int result = 0;
	while (n > 0)
	{
		int m = n / 2;
		if (strcmp(x, s[m].name) <= 0)
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

//Calcula o índice da primeira ocorrência de um valor dado investment array ordenado, devolvendo -1, se não houver.
int Aldrabice_bfind(Aldrabice *s, int n, const char *x)
{
 int r = Aldrabice_rank(s, n, x);
 return r < n && strcmp(s[r].name, x) == 0 ? r : -1;
} 

/*---------------------------------------------------------------------*/
/*--------------------------PROGRAMA-----------------------------------*/
/*---------------------------------------------------------------------*/

//Ler de um ficheiro para um array preenchido com o construtor aldrabice, q é do tipo estrutura Aldrabice
int struct_read(FILE *f, Aldrabice *a){
	int result = 0;
	char name[100];//dimensoes arbitrarias
	int aldrabice_investment;
  	while (fscanf(f, "%s%d", name, &aldrabice_investment) != EOF){ //le 2 valores do ficheiro f, linha a linha, e coloca-os nas variaveis da estrutura
  		a[result++] =	aldrabice(str_dup(name), aldrabice_investment);//as cadeias lidas são duplicadas para o heap e os endereços são guardados na estrutura.
  	}
  	return result;//devolve o tamanha do array para onde se guardou os valores
}

double list_aldrabice(Aldrabice *cheat, int n, Aldrabice *valid, int m, Aldrabice *b, int(*cmp)(Aldrabice, Aldrabice)){
	int result = 0;
	int i = 0;
	int j = 0;
	while (i < n && j < m)//enquanto nao chegar ao fim dos arrays a e b
		if (cmp(cheat[i], valid[j]) == 0){//compara as posiçoes de a e b, se b for maior:
			b[result++] = aldrabice(str_dup(cheat[i].name), (cheat[i].investment - valid[j].investment));//copia o elemento de a para c
			i++;
			j++;
		}
		else if (cmp(cheat[i], valid[j]) > 0)
		{
			j++;
		}
		else
			i++;
	return result;//retorna o tamanho de b
}

//Escrever o array de estruturas investment ficheiro
void final_write(FILE *f, Aldrabice *b, int n)
{
    int i;
	for (i = 0; i < n; i++)
		fprintf(stdout, "%s %d\n", b[i].name, (b[i].investment)); //escreve no ficheiro f, com o formato indicado, cada posiçao de a, q contem os 2 valores da estrutura


void test_list_aldrabice(char *filename){
	Aldrabice cheat[100];
	Aldrabice valid[100];
	Aldrabice b[100];
	FILE *f = fopen(filename, "r");
	assert(f != NULL);
	int n_cheat = struct_read(f, cheat);
	int n_valid = struct_read(stdin, valid);
	Aldrabice_sort(cheat, n_cheat, name_cmp);
	Aldrabice_sort(valid, n_valid, name_cmp);
	int n_list = list_aldrabice(cheat, n_cheat, valid, n_valid, b, name_cmp);
	Aldrabice_sort(b, n_list, investment_cmp);
	final_write(f, b, n_list);
}

int main(int argc, char *argv[])
{
	test_list_aldrabice(argv[1]);
	return 0;
}
