/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Fulvio Taroni Monteforte
       Thiago Lima Bahia Santos
Matricula: 20183005944
           20183000302
Descricao do programa: Algoritmos de Ordenacao
Data: 29/11/19
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#define MAXTAM 200000

typedef long TipoChave;

typedef struct TipoItem {
  TipoChave Chave;
  TipoChave PosOriginal;
  /* Guarda a posicao original de cada chave no vetor */
} TipoItem;

typedef int TipoIndice;

typedef TipoItem TipoVetor[MAXTAM + 1]; 
/* MAXTAM+1 por causa da sentinela em Insercao */

TipoVetor A;
TipoIndice i, n;

/* ------------------------------------------------- */
/* Bubblesort - Inicio */
void Bubblesort(TipoItem *A, TipoIndice n) {
	
	int i, j;
	TipoItem x;

	for (j=1; j<n; j++) {
		for (i=1; i<n; i++) {
			if (A[i].Chave > A[i+1].Chave) {
				x = A[i];
				A[i] = A[i+1];
				A[i+1] = x;
			}
		}
	}

}
/* Bubblesort - Fim */
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* Insercao - Inicio */
void Insercao(TipoItem *A, TipoIndice n) { 

	TipoIndice i, j;
  	TipoItem x;
  
  	for (i = 2; i <= n; i++) { 
  		x = A[i];  
  		j = i - 1;
      	A[0] = x; /* sentinela */
      	while (x.Chave < A[j].Chave) { 
      		A[j+1] = A[j];  
      		j--;
        }
      	A[j+1] = x;
    }

}
/* Insercao - Fim */
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* Selecao - Inicio */
void Selecao(TipoItem *A, TipoIndice n) { 
	
	TipoIndice i, j, Min;
  	TipoItem x;
  	
  	for (i = 1; i <= n - 1; i++) { 
  		Min = i;
      	for (j = i + 1; j <= n; j++) 
        	if (A[j].Chave < A[Min].Chave) 
        		Min = j;
      	x = A[Min]; 
      	A[Min] = A[i]; 
      	A[i] = x;
    }

}
/* Selecao - Fim */
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* Quicksort - Inicio */
void Particao(TipoIndice Esq, TipoIndice Dir, TipoIndice *i, TipoIndice *j, TipoItem *A) {

	TipoItem x, w;
  	*i = Esq;
  	*j = Dir;
  	x = A[(*i + *j) / 2]; /* obtem o pivo x */
  	do {
    	while (x.Chave > A[*i].Chave) {
    		(*i)++;
    	}
    	while(x.Chave < A[*j].Chave) {
        	(*j)--;
    	}
   		if (*i <= *j) {
        	w = A[*i]; 
        	A[*i] = A[*j]; 
        	A[*j] = w;
        	(*i)++;
        	(*j)--;
    	}
  	} while(*i <= *j);

}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A) {

	TipoIndice i, j;
  	Particao(Esq, Dir, &i, &j, A);
  
  	if (Esq < j) {
    	Ordena(Esq, j, A);
  	}
  	if (i < Dir) {
    	Ordena(i, Dir, A);
  	}

}

void Quicksort(TipoItem *A, TipoIndice n) {

	Ordena(1, n, A);

}
/* Quicksort - Fim */
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* Heapsort - Inicio */
void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A) { 

	TipoIndice i = Esq;
  	int j;
  	TipoItem x;
  
  	j = i * 2;
  	x = A[i];
  	while (j <= Dir) { 
  		if (j < Dir) { 
  			if (A[j].Chave < A[j+1].Chave)
        		j++;
      	}	
    	if (x.Chave >= A[j].Chave) 
    		goto L999;
    	A[i] = A[j];
    	i = j;  
    	j = i * 2;
	}
	L999: A[i] = x;

}

void Constroi(TipoItem *A, TipoIndice n) { 

	TipoIndice Esq;
  	Esq = n / 2 + 1;
  	
  	while (Esq > 1) { 
  		Esq--;
      	Refaz(Esq, n, A);
    }

}

void Heapsort(TipoItem *A, TipoIndice n) { 

	TipoIndice Esq, Dir;
  	TipoItem x;

  	Constroi(A, n);  /* constroi o heap */
  
  	Esq = 1;  Dir = n;
  	
  	while (Dir > 1) { 
  		/* ordena o vetor */
  		x = A[1];  
  		A[1] = A[Dir];  
  		A[Dir] = x;  
  		Dir--; 
      	Refaz(Esq, Dir, A);
    }

}
/* Heapsort - Fim */
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* Mergesort - Inicio */
void Merge(TipoItem *A, int i, int m, int j) {

	TipoVetor B;
	int x;
  	int k = i;
  	int l = m+1;

  	for (x=i; x<=j; x++) 
  		B[x] = A[x];

  	x = i;
  	while (k<=m && l<=j) {
    	if (B[k].Chave <= B[l].Chave) {
        	A[x++] = B[k++];
    	} 
    	else 
    		A[x++] = B[l++];
  	}
  	while (k<=m) {
    	A[x++] = B[k++];
  	}
  	while (l<=j) {
    	A[x++] = B[l++];
  	}

}

void Mergesort(TipoItem *A, int i, int j) {
	
	int m;
  	
  	if (i < j) {
    	m = (i + j - 1) / 2;
    	Mergesort(A, i, m);
    	Mergesort(A, m + 1, j);
    	Merge(A, i, m, j); /* Intercala A[i..m] e A[m+1..j] em A[i..j] */
  	}

}
/* Mergesort - Fim */
/* ------------------------------------------------- */

void Imprime(TipoItem *V, TipoIndice n) { 

	for (i = 1; i <= n; i++)
		printf("%li ", V[i].Chave);  
	printf("\n");

}

void ImprimePos(TipoItem *V, TipoIndice n) { 

	for (i = 1; i <= n; i++)
		printf("%li(%li) ", V[i].Chave, V[i].PosOriginal);  
	printf("\n");

}

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n) {

	for (i = 1; i <= n; i++)
    	Destino[i] = Fonte[i];

}

void Testa(TipoItem *V, TipoIndice n) { 

	for (i = 2; i <= n; i++) {
    	if (V[i].Chave < V[i-1].Chave) {
      		printf("ERRO: ");
      		Imprime(V, n);
      		return;
    	}
  	}
  	printf("OK: ");
  	Imprime(V, n);

}

void TestaEstabilidade(TipoItem *V, TipoIndice n) { 

	for (i = 2; i <= n; i++) {
    	if (V[i].Chave == V[i-1].Chave && V[i].PosOriginal < V[i-1].PosOriginal) {
      		printf("INSTAVEL: ");
      		ImprimePos(V, n);
      		return;
    	}
  	}
  	printf("ESTAVEL: ");
  	ImprimePos(V, n);

}

double rand0a1() { 

	double resultado;

	resultado = (double) rand() / INT_MAX; /* Dividir pelo maior inteiro */
	if (resultado > 1.0) 
		resultado = 1.0;
	
	return resultado;

}

void Permut(TipoItem *A, int n) { 

	int i, j;
  	TipoItem b;

  	for (i = n; i > 1; i--) { 
  		j = (i * rand0a1()) + 1;
    	b = A[i];
    	A[i] = A[j];
    	A[j] = b;
  	}

}

void Permut20(TipoItem *A, int n) { 

	int i, j, k, n20;
  	TipoItem b;

  	n20 = (int) (n * 0.1);
  	for (i = 0; i < n20; i++) {
  		j = 1 + (rand() % (n - 1)); /* Sorteia a primeira posicao aleatoria para ser permutada */
  		k = 1 + (rand() % (n - 1)); /* Sorteia a segunda posicao aleatoria para ser permutada */
     	b = A[j];
    	A[j] = A[k];
    	A[k] = b; 		
  	}

}

void Inverte(TipoItem *A, int n) {

	int i, j;
	TipoItem b;

	for (i = 1, j = n; i < n/2; i++, j--) {
		b = A[i];
		A[i] = A[j];
		A[j] = b;
	}

}

/* Teste da medicao do tempo*/
int main(int argc, char *argv[])
{
     // Variaveis relacionadas com a medicao do tempo:
     int who = RUSAGE_SELF; //man: information shall be returned about resources used by the current process
     struct rusage usage;

     long utotalmicroseg, utotalseg; //tempo usuario: tempo que a CPU gasta executando o programa
     long stotalmicroseg, stotalseg; //tempo sistema: tempo que a CPU gasta executando chamadas
     //de sistemas para o programa
     
     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------
     //coloque aqui o algoritmo

	TipoVetor B;
	int opt, n, aflag, tflag, vflag = 0, rflag = 0;

	while ((opt = getopt (argc, argv, "a:n:t:v:r:")) != -1) {	
		switch (opt) {
			/* -a: algoritmo a ser executado. */
			case 'a':
				/* Seta aflag = 1 para o Bubblesort */
				if (!strcmp(argv[2], "Bubblesort"))
					aflag = 1;
				/* Seta aflag = 2 para o Insercao */
				if (!strcmp(argv[2], "Insercao"))
					aflag = 2;
				/* Seta aflag = 3 para o Selecao */
				if (!strcmp(argv[2], "Selecao"))
					aflag = 3;
				/* Seta aflag = 4 para o Quicksort */				
				if (!strcmp(argv[2], "Quicksort"))
					aflag = 4;					
				/* Seta aflag = 5 para o Heapsort */				
				if (!strcmp(argv[2], "Heapsort"))
					aflag = 5;
				/* Seta aflag = 6 para o Mergesort */
				if (!strcmp(argv[2], "Mergesort"))
					aflag = 6;								
				break;

			/* -n: número de elementos do vetor. */
			case 'n': 
				n = atoi(argv[4]);
				break;
			
			/* -t: tipo de entrada. O programa deverq gerar um vetor de entrada de um dos tipos a seguir: */
			/* 1 - em ordem crescente (ordenado) */
			/* 2 - em ordem descrescente */
			/* 3 - aleatorio */
			/* 4 - quase ordenado */
			case 't':
				tflag = atoi(argv[6]);
				break;

			/* -v: imprimir vetor original sim (S) ou não (N). Imprime somente as chaves dos registros. */
			case 'v':
				/* Seta vflag como verdadeiro para impressao do vetor original */
				if (!strcmp(argv[8], "S"))
					vflag = 1;
				break;

			/* -r: imprimir vetor ordenado sim (S) ou não (N). Imprime somente as chaves dos registros. */
			case 'r':
				/* Seta rflag como verdadeiro para impressao do vetor ordenado */			
				if (!strcmp(argv[10], "S"))
					rflag = 1;	
				break;			

            default:
            	printf("Erro! Opcao invalida ou faltando argumento.\n");
                return -1;					
		}
	}

	/* Gera um vetor completamente aleatorio com chaves entre 1 e n */
	for (i = 1; i <= n; i++)
    	A[i].Chave = 1 + (rand() % (n - 1));

	/* Se tflag = 1, gera um vetor em ordem crescente (ordenado) */
	if (tflag == 1) {
		Quicksort(A, n);
		for (i = 1; i <= n; i++)		
			A[i].PosOriginal = i;
  		Copia(A, B, n);
	}
	/* Se tflag = 2, gera um vetor em ordem descrescente (desordenado) */		
	if (tflag == 2) {
		Quicksort(A, n);		
  		Inverte(A, n);
		for (i = 1; i <= n; i++)		
			A[i].PosOriginal = i;  		
  		Copia(A, B, n);
	}
	/* Se tflag = 3, gera um vetor aleatório */		
	if (tflag == 3) {
  		Permut(A, n);
		for (i = 1; i <= n; i++)		
			A[i].PosOriginal = i;  		
  		Copia(A, B, n);		
	}
	/* Se tflag = 4, gera um vetor quase ordenado */
	if (tflag == 4) {
		Quicksort(A, n);
		Permut20(A, n);
		for (i = 1; i <= n; i++)		
			A[i].PosOriginal = i;		
  		Copia(A, B, n);  
	}		

	/* Se aflag = 1, executa o Bubblesort */
	if (aflag == 1)
		Bubblesort(B, n);
	/* Se aflag = 2, executa o Insercao */	
	if (aflag == 2) 
		Insercao(B, n);
	/* Se aflag = 3, executa o Selecao */	
	if (aflag == 3)
		Selecao(B, n);
	/* Se aflag = 4, executa o Quicksort */	
	if (aflag == 4)
		Quicksort(B, n);
	/* Se aflag = 5, executa o Heapsort */	
	if (aflag == 5)
		Heapsort(B, n);
	/* Se aflag = 6, executa o Mergesort */	
	if (aflag == 6)
		Mergesort(B, 1, n);

	/* Se vflag verdadeiro, imprime o vetor original */
	if (vflag == 1) {
		printf("Vetor original:\n");
		Imprime(A, n);
		printf("\n");
	}
	/* Se rflag verdadeiro, imprime o vetor ordenado */	
	if (rflag == 1) {
		printf("Vetor ordenado:\n");
  		TestaEstabilidade(B, n);
		printf("\n");  		
	}

     //--------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------

     getrusage(who, &usage);

     //tempo de usuário na CPU
     utotalseg = usage.ru_utime.tv_sec; //segundos
     utotalmicroseg = usage.ru_utime.tv_usec; //microsegundos

     //tempo de sistema na CPU
     stotalseg = usage.ru_stime.tv_sec; //segundos
     stotalmicroseg = usage.ru_stime.tv_usec; //microsegundos
     printf ("\n");
     printf ("***************************************************************\n");
     printf ("Tempo de usuario: %ld segundos e %ld microssegundos.\n", utotalseg, utotalmicroseg);
     printf ("Tempo de sistema: %ld segundos e %ld microssegundos.\n", stotalseg, stotalmicroseg);
     printf ("***************************************************************\n");
     printf ("\n");

     return(0);
}