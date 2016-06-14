#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int X[100];
int lungimeatraseului;
typedef struct nod
{

	int valoare,ramura,vizitat;
	nod* parinte;
};
typedef struct lista
{
	nod* nodinlista;
	lista* urmatorul;
};
lista* primul=(lista*)malloc(sizeof(lista));
int verificarenodnou(nod* ver)
{
	int ok=1;
	int ram=ver->ramura;
	while(ver->parinte!=NULL)
	{
		if(ver->parinte->ramura==ram)
			ok=0;
		ver=ver->parinte;
	}
	return ok;
}
void introducereinlista(nod* a)
{
	lista* noua=(lista*)malloc(sizeof(lista));
	noua->nodinlista=a;
	noua->urmatorul=NULL;
	if(primul==NULL)
	{
		primul=noua;
	}
	else
	{
		if(primul->nodinlista->valoare > noua->nodinlista->valoare)
		{
			noua->urmatorul=primul;
			primul=noua;
			return;
		}
		else
		{
			lista* c;
			c=primul;
			while(c->urmatorul != NULL)
			{
				if(c->urmatorul->nodinlista->valoare > noua->nodinlista->valoare)
				{
					noua->urmatorul = c->urmatorul;
					c->urmatorul=noua;
					return;
				}
				c=c->urmatorul;
			}
			c->urmatorul=noua;
			return;
		}
	}

}
void solutiebuna(nod* sol)
{
	int i;
	if(lungimeatraseului==-1||lungimeatraseului>sol->valoare+A[sol->ramura-1][0])
	{
		lungimeatraseului=sol->valoare+A[sol->ramura-1][0];
		i=1;
		while(sol->parinte!=NULL)
		{
			X[i]=sol->ramura;
			i++;
			sol=sol->parinte;
		}
	}
}
void branch(nod* l)
{
	primul=primul->urmatorul;
	for(int i=0;i<n;i++)
	{
		if(A[l->ramura-1][i]>=0)
		{
			nod* nou=(nod*)malloc(sizeof(nod));
			nou->parinte=l;
			nou->valoare=l->valoare+A[l->ramura-1][i];
			nou->vizitat=l->vizitat+1;
			nou->ramura=i+1;
			if(verificarenodnou(nou)==1)
			{
				if(nou->vizitat==n)
				{
					solutiebuna(nou);
				}
				else
				{
					introducereinlista(nou);
				}
			}
		}
	}
}
void main()
{
	int i,j,min;
	for(i=0;i<n;i++)
	{
		min=100;
		for(j=0;j<n;j++)
		{
			if(A[i][j]<min&&A[i][j]>0)
				min=A[i][j];
		}
		lungimeatraseului+=min;
		for(j=0;j<n;j++)
		{
			A[i][j]-=min;
		}
	}
	nod* start;
	X[0]=1;
	X[n]=1;
	start=(nod*)malloc(sizeof(nod));
	start->parinte=NULL;
	start->ramura=1;
	start->vizitat=1;
	start->valoare=lungimeatraseului;
	primul->nodinlista=start;
	primul->urmatorul=NULL;
	lungimeatraseului=-1;
	while(primul!=NULL)
	{
		branch(primul->nodinlista);
	}
	printf("Lungimea celui mai scurt traseu este: %d.\nTraseul este:\n",lungimeatraseului);
	for(i=0;i<=n;i++)
	{
		if(i!=n)
			printf("%d=>",X[i]);
		else
			printf("%d",X[i]);
	}
}