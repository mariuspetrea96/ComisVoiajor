// Win32Project.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Win32Project.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LOADSTRING 100
int n, A[20][20],ok,ok1,X[20],lungimeatraseului;
char buf[100];
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
void formarebuf()
{
	char a[20];
	strcpy_s(buf,"Lungimea traseului minim este: ");
	_itoa_s(lungimeatraseului,a,10);
	strcat_s(buf, a);
	strcat_s(buf,"\nTraseul este: ");
	for(int i=0;i<=n;i++)
	{
		
		_itoa_s(X[i],a,10);
		strcat_s(buf,a);
		if(i!=n)
		{
			strcat_s(buf,"->");
		}
	}
}
void calculeaza(HWND hWnd)
{
	nod* start;
	X[0]=1;
	X[n]=1;
	start=(nod*)malloc(sizeof(nod));
	start->parinte=NULL;
	start->ramura=1;
	start->vizitat=1;
	start->valoare=lungimeatraseului;
	primul->nodinlista=(nod*)malloc(sizeof(nod));
	primul->nodinlista=start;
	primul->urmatorul=NULL;
	lungimeatraseului=-1;
	while(primul!=NULL)
	{
		branch(primul->nodinlista);
	}
	formarebuf();
	MessageBox(hWnd,buf,"Solution",MB_ICONQUESTION);
	return;
}


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szWindowClass1[MAX_LOADSTRING];
HWND Buton1,Buton2,Buton3, hwnd1,hwnd2, Buton4, Buton5, ButonNr, ButonForm, Casuta[1000];
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM				MyRegisterClass1(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK	WndProc1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void tabela(HWND hWnd, int n){
	if(n>12)
	{
		MessageBox(NULL,
				"Ati depasit numarul maxim de\ndrumuri permis!",
				"ERROR",
				MB_ICONQUESTION);
		return;
	}
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++){
		Casuta[i*n+j]=CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 
			10 + 45 * i, 40 + 25 * j, 40, 20, hWnd, (HMENU)(n * i + j), hInst, NULL);
		if(i==j)
		{
			SetDlgItemText(hWnd,n*i+j,"inf.");
			EnableWindow(GetDlgItem(hWnd,n*i+j),FALSE);
		}
	}
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_STRING104, szWindowClass1, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterClass1(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass1(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc1;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GRAF);
	wcex.lpszClassName	= szWindowClass1;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd,hwnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "Travelling salesman problem", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 650, 510, NULL, NULL, hInstance, NULL);
   hwnd = CreateWindow(szWindowClass1, "Solver", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 650, 510, NULL, NULL, hInstance, NULL);


   if (!hWnd || !hwnd)
   {
      return FALSE;
   }
   hwnd1=hWnd;
   hwnd2=hwnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

	PAINTSTRUCT ps;
	HDC hdc;

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId	=LOWORD(wParam);
		wmEvent	=HIWORD(wParam);
		switch (wmId)
		{
		case IDM_BACK:
			{
				for (int i = 0; i < n*n; i++)
				{
					DestroyWindow(Casuta[i]);
				}
				DestroyWindow(ButonNr);
				ButonNr=CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 
					10, 10, 60, 20, hWnd, (HMENU)EDIT_BOX_1, hInst, NULL);
			  ShowWindow(hwnd1, SW_SHOWDEFAULT);
			  ShowWindow(hWnd, SW_HIDE);
			break;
			}
		case BUTTON_TABEL:
			{
				for (int i = 0; i < n*n; i++)
				{
					DestroyWindow(Casuta[i]);
				}
				n=GetDlgItemInt(hWnd, EDIT_BOX_1, NULL, NULL);
				tabela(hWnd,n);
			}
			break;
		case IDM_CALC:
			{
				if(n==NULL)
				{
					break;
				}
				int i,j;
				for(i=0;i<n;i++)
				{
					for(j=0;j<=n;j++)
					{
						A[i][j]=GetDlgItemInt(hWnd, i*n+j, NULL, NULL);
					}
				}
				ok=1;
				for(int i=0;i<n;i++)
				{
					for(int j=0;j<n;j++)
					{
						if(A[i][j]==NULL&&i!=j)
						{
							ok=0;
							i=n;
							j=n;
						}
					}
				}
				if(ok==0)
				{
							MessageBox(NULL,
								"Nu ati atribuit valori tuturor drumurilor!",
								"ERROR",
								MB_ICONQUESTION);
				}
				else
				{
					ok1=1;
					for(i=0;i<n;i++)
					{
						for(j=0;j<n;j++)
						{
							if(A[i][j]!=A[j][i])
							{
								ok1=0;
								i=n;j=n;
							}
						}
					}
					if(ok1==0)
					{
						MessageBox(NULL,
								"Graful este neorientat!\n\n Valorile trebuie sa fie introduse\nsimetric fata de diagonala pincipala!",
								"ERROR",
								MB_ICONQUESTION);
					}
					else
					{
						calculeaza(hWnd);
					}
				}
			}
			break;
		case IDM_REV:
			{
				for (int i = 0; i < n*n; i++)
				{
					DestroyWindow(Casuta[i]);
				}
				DestroyWindow(ButonNr);
				ButonNr=CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 
					10, 10, 60, 20, hWnd, (HMENU)EDIT_BOX_1, hInst, NULL);
			break;
			}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CREATE:
		Buton4=CreateWindowEx(NULL,"BUTTON","Back",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,550,410,60,20,hWnd,(HMENU)IDM_BACK,GetModuleHandle(NULL),NULL);
		Buton5=CreateWindowEx(NULL,"BUTTON","Revino!",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,150,10,60,20,hWnd,(HMENU)IDM_REV,GetModuleHandle(NULL),NULL);
		Buton5=CreateWindowEx(NULL,"BUTTON","Calculeaza!",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,20,410,100,20,hWnd,(HMENU)IDM_CALC,GetModuleHandle(NULL),NULL);
		ButonNr=CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 
			10, 10, 60, 20, hWnd, (HMENU)EDIT_BOX_1, hInst, NULL);
		ButonForm=CreateWindow("BUTTON", "Ok!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			80, 10, 60, 20, hWnd, (HMENU)BUTTON_TABEL, hInst, NULL);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;


	switch (message)
	{
	case WM_CREATE:
	{
		CreateWindowEx(NULL, TEXT("STATIC"), "TRAVELLING SALESMAN PROBLEM",WS_CHILD | WS_VISIBLE | SS_LEFT,200, 20, 240, 20,hWnd,NULL,GetModuleHandle(NULL) , NULL ); 
		CreateWindowEx(NULL, TEXT("STATIC"), "Realizator: Petrea Marius",WS_CHILD | WS_VISIBLE | SS_LEFT,240, 50, 170, 20,hWnd,NULL,GetModuleHandle(NULL) , NULL ); 
		CreateWindowEx(NULL, TEXT("STATIC"), "Coordonator: Prof. Pura Mihai",WS_CHILD | WS_VISIBLE | SS_LEFT,225, 80, 200, 20,hWnd,NULL,GetModuleHandle(NULL) , NULL ); 
		Buton1=CreateWindowEx(NULL,TEXT("BUTTON"),"Start",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,20,400,60,40,hWnd,(HMENU)IDM_START,GetModuleHandle(NULL),NULL);
		Buton2=CreateWindowEx(NULL,TEXT("BUTTON"),"Info",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,490,400,60,40,hWnd,(HMENU)IDM_INFO,GetModuleHandle(NULL),NULL);
		Buton3=CreateWindowEx(NULL,TEXT("BUTTON"),"Close",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,560,400,60,40,hWnd,(HMENU)IDM_EXIT,GetModuleHandle(NULL),NULL);
	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_START:
		
			  ShowWindow(hwnd2, SW_SHOWDEFAULT);
			  ShowWindow(hWnd, SW_HIDE);
			break;		
		case IDM_ABOUT:
			MessageBox(NULL,
						"Proiect realizat de:\nPetrea Marius \n\nIndrumator:\nPura Mihai\n\n\xa9 Copyright Iunie 2016",
						"About...",
						MB_ICONQUESTION);
			break;

		case IDM_INFO:
			{
			MessageBox(NULL,
						"Programul determina costul minim si traseul ce trebuie urmat, pentru a trece prin fiecare nod al unui graf neorientat.\nPentru a incepe dati click pe butonul \"Start\", urmand sa apara o noua fereastra ce va colecta informatiile.\nPentru numarul de noduri se va introduce in casuta de text numarul dorit si se va apasa butonul \"Ok!\".\nVa aparea o matrice patratica ce trebuie umpluta cu valorile costurilor.\nIn cazul in care se doreste revenirea la inceputul celei de a doua fereste se va apasa butonul \"Revino!\".\nDaca valorile introduse respecta cerintele, la apasarea butonului \"Calculeaza!\" programul va determina lungimea si costul si le va afisa intr-un DialogBox.\nDaca valorile introduse nu sunt corecte se vor afisa mesaje corespunzatoare.\nButonul \"Back\" revine la fereastra principala.\n\nProgramul se inchide prin apasarea butonului \"X\" sau a butonului \"Close\". ",
						"User Guide",
						MB_ICONQUESTION);
			break;
			}

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
