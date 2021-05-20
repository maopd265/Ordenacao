#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 50000000

char *vout;

void shellsort(char *v, int n) {
int i, j, h;
int aux;
for(h = 1; h < n; h = 3*h+1); /* calcula o h inicial. */
while(h > 0) {
   h = (h-1)/3; /* atualiza o valor de h. */
   for(i = h; i < n; i++) {
      aux = v[i];
      j = i;
      /* efetua comparações entre elementos com distância h: */
	  while (v[j-h] > aux) {
         v[j] = v[j-h];
         j -= h;
         if(j < h) break;
         }
      v[j] = aux;
      }
   }
}

void quick_sort(char vetor[],int left,int right){
if (right<= left) return;
if (left+1==right)
   {
   if (vetor[left]>vetor[right])
      {
      int aux=vetor[left];
      vetor[left]=vetor[right];
      vetor[right]=aux;
      }
   return;
   }
int pivot = vetor[left];
int inicio=left;
int fim=right;
left++;
do {
   if (vetor[left] <= pivot) left++;
   if (vetor[right] >= pivot) right--;
   if (left < right && vetor[left]>pivot && vetor[right]<pivot) { /* faz troca */
      int temp = vetor[left];
      vetor[left] = vetor[right];
      vetor[right] = temp;
   }
} while (left <= right);
/* troca pivot */
vetor[inicio] = vetor[right];
vetor[right] = pivot; pivot=right;
/* ordena sub-vetores restantes */
quick_sort(vetor,inicio,pivot-1);
quick_sort(vetor,pivot+1,fim);
}

void bubble(char v[])
{
     int i,j,aux;
     for (i=0;i<TAM;i++)
        {
        int trocou=0;
        for (j=0;j<TAM-i-2;j++)
           if (v[j]>v[j+1])
              {
              aux=v[j];
              v[j]=v[j+1];
              v[j+1]=aux;
              trocou=1;
              }
        if (!trocou) return;
        }
}

void merge(char vin[],int ini1, int fim1, int ini2, int fim2)
{
     int i,isai;
     int inicio=ini1;
     for (isai=ini1;isai<=fim2;isai++)
        if (ini1>fim1)
           vout[isai]=vin[ini2++];
        else if (ini2>fim2)
                vout[isai]=vin[ini1++];
             else if (vin[ini1]<vin[ini2])
                     vout[isai]=vin[ini1++];
                  else vout[isai]=vin[ini2++];
     for (i=inicio;i<=fim2;i++) vin[i]=vout[i];
        
}
                  
void mergesort(char v[],int ini, int fim)
{
     int i;
     if (ini<fim)
        {
        int meio=(fim+ini)/2;
        mergesort(v,ini,meio);
        mergesort(v,meio+1,fim);
        merge(v,ini,meio,meio+1,fim);
        }  
               
 }

#define pai(i) ((i-1)/2)
#define fesq(i) (i*2+1)
#define fdir(i) (i*2+2)

void corrige_descendo(char heap[],int i,int fim)
{
   if (fesq(i) < fim)    // Se index tem filho
      {
      // Seleciona o filho com menor valor (esquerda ou direita?)
      int filho = fesq(i);
      if (fdir(i) < fim && heap[fdir(i)] > heap[fesq(i)])
         filho = fdir(i);
      // Se o valor do pai é maior do que o valor do maior filho, terminamos
      if (heap[i] > heap[filho])
         return;
      // Caso contrário, trocamos o pai com o filho no heap e corrigimos agora para o filho
      int aux=heap[i];
	  heap[i]=heap[filho];
	  heap[filho]=aux;
      corrige_descendo(heap,filho,fim);
      }
   }

void corrige_subindo(char heap[],int i)
   {
   if (i > 0 && heap[i] > heap[pai(i)])
      {
	  int aux=heap[i];
	  heap[i]=heap[pai(i)];
	  heap[pai(i)]=aux;
	  corrige_subindo(heap,pai(i));
      }
   }

void heapsort(char v[])
{
int i;
for (i=1;i<TAM;i++)
   corrige_subindo(v,i);
for (i=TAM-1;i>0;i--)
   {
   int aux=v[i];
   v[i]=v[0];
   v[0]=aux;
   corrige_descendo(v,0,i-1);
   } 	
}

void radixsort(char vetor[], int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }
 
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++; 
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

int main()
{   int i;
    char *v,*w;
    time_t t1,t2;
    srand(time(NULL));
    v=(char *)malloc(TAM);
    w=(char *)malloc(TAM);
    vout=(char *)malloc(TAM);
    time(&t1);
    for (i=0;i<TAM;i++)
	   v[i]=w[i]=rand()%100;
    time(&t2);
    printf("\n Gerou os dados em %d segundos \n",t2-t1);
/*    time(&t1);
    quick_sort(v,0,TAM-1);
    time(&t2);
    printf("\n Ordenado por quick em %d segundos \n",t2-t1);
    for (i=0;i<TAM;i++)
	   v[i]=w[i];*/
    time(&t1);
    mergesort(v,0,TAM-1);
    time(&t2);
    printf("\n Ordenado por merge em %d segundos \n",t2-t1);
    for (i=0;i<TAM;i++)
	   v[i]=w[i];
//    for (i=0;i<TAM;i++) printf("%d ",v[i]);
    time(&t1);
    shellsort(v,TAM);
    time(&t2);
//    for (i=0;i<TAM;i++) printf("%d ",v[i]);
    printf("\n Ordenado por shellsort em %d segundos \n",t2-t1);
/*    for (i=0;i<TAM;i++)
	   v[i]=w[i];
    time(&t1);
    bubble(v);
    time(&t2);
    printf("\n Ordenado por bubble em %d segundos \n",t2-t1);*/
    for (i=0;i<TAM;i++)
	   v[i]=w[i];
    time(&t1);
    heapsort(v);
    time(&t2);
    printf("\n Ordenado por heap em %d segundos \n",t2-t1);
    for (i=0;i<TAM;i++)
	   v[i]=w[i];
    time(&t1);
    radixsort(v,TAM);
    time(&t2);
    printf("\n Ordenado por radix em %d segundos \n",t2-t1);
    system("pause");

}
