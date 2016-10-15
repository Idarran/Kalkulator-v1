//Program:		Kalkulator
//Programista:	Hubert Hodowaniec

#include <windows.h>
#include <cmath>
#include <string>

#define BUTTON0 100
#define BUTTON1 101
#define BUTTON2 102
#define BUTTON3 103
#define BUTTON4 104
#define BUTTON5 105
#define BUTTON6 106
#define BUTTON7 107
#define BUTTON8 108
#define BUTTON9 109

#define BUTTONC 110 //czyszczenie pola edycyjnego
#define BUTTONB 111 //cofanie poprzedniego znaku

#define BUTTOND 112 //dodawanie
#define BUTTONO 113 //odejmowanie
#define BUTTONX 114 //mno¿enie
#define BUTTONDZ 115 //dzielenie

#define BUTTONR 116 //=
#define BUTTONK 117 //kropka dziesiêtna
#define BUTTONPI 118 //liczba pi

#define BUTTONP 119 //pierwiastek
#define BUTTONS 120 //silnia
#define BUTTONLO 121 //liczba odwrotna
//#define BUTTONPR 122 //procent

#define BUTTONSIN 123 
#define BUTTONCOS 124
#define BUTTONTG 125
#define BUTTONLN 126
#define BUTTONLG 127

#define EDITBX 666 //pole tekstowe

#define MAXOUT 25
#define MAXIN  10
#define PI 3.14159265


//prototypy funkcji
void ustawWartosc(HWND hEB, double display);
double oblicz(int functionflag, double display1, double display2);
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp);
HWND ustawOkno(char* cClass, char* cTitle, int nSzer, int nWys, HINSTANCE hInstance);

//zmienne globalne
HWND hOkno,
hB0, hB1, hB2, hB3, hB4, hB5, hB6, hB7, hB8, hB9,
hBC, hBB,
hBD, hBO, hBX, hBDZ,
hBR, hBK, hBPI,
hBP, hBS, hBLO, hBPR,
hBSIN, hBCOS, hBTG, hBLN, hBLG,
hEB;

double display1 = 0, display2 = 0;
double wynik = 0;
int functionflag = 0;	//flaga funkcji: 0=brak, 1=dodawanie, 2=odejmowanie, itd.
int flag_New = 1;		//flaga nowy/kolejny
//double dTotal = 0;		//wartoœæ bufora
//char cBuf[MAXOUT];		//bufor

HWND ustawOkno(char* cClass, char* cTitle, int nSzer, int nWys, HINSTANCE hInstance)
{
	//rejestracja klasy okienkowej
	WNDCLASSEX wc;
	HWND hOkno;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wnd_proc;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = cClass;
	RegisterClassEx(&wc);

	//tworzenie okna...
	hOkno = CreateWindowEx(0, cClass, cTitle,
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, nSzer, nWys,
		NULL, NULL, hInstance, NULL);

	/*
	if (NULL == hOkno)
		return -1; //sprawdzenie, czy siê uda³o
	*/

	return hOkno;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdline, int iCmdShow)
{
	char* cClass = "Kalkulator";	// nazwa klasy
	char* cTitle = "Kalkulator";	// nazwa okienka
	const int nSzer = 320;			// szerokoœæ okienka
	const int nWys = 250;			// wysokoœæ okienka

	MSG msg;

	hOkno = ustawOkno(cClass, cTitle, nSzer, nWys, hInstance);

	hB1 = CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 156, 40, 30, hOkno, (HMENU)BUTTON1, hInstance, NULL);
	hB2 = CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 156, 40, 30, hOkno, (HMENU)BUTTON2, hInstance, NULL);
	hB3 = CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 156, 40, 30, hOkno, (HMENU)BUTTON3, hInstance, NULL);
	hB4 = CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 124, 40, 30, hOkno, (HMENU)BUTTON4, hInstance, NULL);
	hB5 = CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 124, 40, 30, hOkno, (HMENU)BUTTON5, hInstance, NULL);
	hB6 = CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 124, 40, 30, hOkno, (HMENU)BUTTON6, hInstance, NULL);
	hB7 = CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 92, 40, 30, hOkno, (HMENU)BUTTON7, hInstance, NULL);
	hB8 = CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 92, 40, 30, hOkno, (HMENU)BUTTON8, hInstance, NULL);
	hB9 = CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 92, 40, 30, hOkno, (HMENU)BUTTON9, hInstance, NULL);

	hB0 = CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 188, 40, 30, hOkno, (HMENU)BUTTON0, hInstance, NULL);
	hBO = CreateWindow("button", ",", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 188, 40, 30, hOkno, (HMENU)BUTTONO, hInstance, NULL);
	hBPI = CreateWindow("button", "PI", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 188, 40, 30, hOkno, (HMENU)BUTTONPI, hInstance, NULL);

	hBD = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 92, 40, 30, hOkno, (HMENU)BUTTOND, hInstance, NULL);
	hBS = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 124, 40, 30, hOkno, (HMENU)BUTTONO, hInstance, NULL);
	hBX = CreateWindow("button", "x", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 156, 40, 30, hOkno, (HMENU)BUTTONX, hInstance, NULL);
	hBD = CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 188, 40, 30, hOkno, (HMENU)BUTTONDZ, hInstance, NULL);

	hBR = CreateWindow("button", "sqrt", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 205, 92, 40, 30, hOkno, (HMENU)BUTTONP, hInstance, NULL);
	hBS = CreateWindow("button", "x!", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 205, 124, 40, 30, hOkno, (HMENU)BUTTONS, hInstance, NULL);
	hBP = CreateWindow("button", "1/x", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 205, 156, 40, 30, hOkno, (HMENU)BUTTONLO, hInstance, NULL);
	hBR = CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 205, 188, 40, 30, hOkno, (HMENU)BUTTONR, hInstance, NULL);

	//hBSIN = CreateWindow("button", "SIN", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 124, 40, 30, hOkno, (HMENU)BUTTONSIN, hInstance, NULL);
	//hBCOS = CreateWindow("button", "COS", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 124, 40, 30, hOkno, (HMENU)BUTTONCOS, hInstance, NULL);
	//hBTG = CreateWindow("button", "TAN", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 92, 40, 30, hOkno, (HMENU)BUTTONTG, hInstance, NULL);
	//hBLN = CreateWindow("button", "LN", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 65, 92, 40, 30, hOkno, (HMENU)BUTTONLN, hInstance, NULL);
	//hBLG = CreateWindow("button", "LOG", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 110, 92, 40, 30, hOkno, (HMENU)BUTTONLG, hInstance, NULL);

	hBB = CreateWindow("button", "<-", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 55, 130, 30, hOkno, (HMENU)BUTTONB, hInstance, NULL);
	hBC = CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 55, 85, 30, hOkno, (HMENU)BUTTONC, hInstance, NULL);

	hEB = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT, 20, 20, 225, 25, hOkno, (HMENU)EDITBX, hInstance, NULL);

	ustawWartosc(hEB, 0); //ustawia wartoœæ pocz¹tkow¹ w oknie

	ShowWindow(hOkno, iCmdShow);
	UpdateWindow(hOkno);

	//pêtla obs³ugi komunikatów
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//funkcja obs³ugi komunikatów okna
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	static bool isFunctionActive;
	static bool kropka;

	switch (message)
	{
		case WM_COMMAND:
		{
			/*if (lp && LOWORD(wp) == EDITBX)
			{
				switch (HIWORD(wp))
				{
					case EN_SETFOCUS:
					{
						SetFocus(hOkno);
						break;
					}
				}
				break;
			}*/
			switch (LOWORD(wp))
			{
				case BUTTONR:				// '=' 
				{
					wynik = oblicz(functionflag, display1, display2);
					ustawWartosc(hEB, wynik);
					isFunctionActive = false;
					break;
				}
				case BUTTON0:			// BUTTON0 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (display1 != 0)
						display1 = display1 * 10;
					//backsp = true;
					break;
				}
				case BUTTON1:			// BUTTON1 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 1;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (1 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON2:			// BUTTON2 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 2;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (2 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON3:			// BUTTON3 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 3;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (3 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON4:			// BUTTON4 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 4;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (4 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON5:			// BUTTON5 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 5;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (5 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON6:			// BUTTON6 clicked
				{
					if (isFunctionActive)
						display1 = 0;			

					if (!kropka)
					{
						display1 = (display1 * 10) + 6;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (6 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON7:			// BUTTON7 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 7;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (7 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON8:			// BUTTON8 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 8;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (8 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTON9:			// BUTTON9 clicked
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + 9;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (9 / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTONPI:
				{
					if (isFunctionActive)
						display1 = 0;

					if (!kropka)
					{
						display1 = (display1 * 10) + PI;
						ustawWartosc(hEB, display1);
					}
					else
					{
						display1 = display1 + (PI / 10);
						ustawWartosc(hEB, display1);
					}
					break;
				}
				case BUTTONK:			// kropka dziesiêtna
				{
					if (!kropka)
						kropka = true;
					else if (kropka)
						kropka = false;
					break;
				}
				case BUTTONC:					// czyszczenie
				{
					display1 = 0;
					display2 = 0;
					ustawWartosc(hEB, display1);
					isFunctionActive = false;
					break;
				}
				/*case BUTTONB:					// TODO  Backspace clicked
				{
					if (backsp)
					{
						if (strlen(cBuf)>1)
						{
							char cLast[1];
							int iSLen = strlen(cBuf);
							cLast[0] = cBuf[iSLen - 1];
							if (strncmp(cLast, ".", 1) == 0)
							{
								dot = false;
							}
							strncpy(cTemp, cBuf, (iSLen - 1));
							cTemp[(iSLen - 1)] = '\0';
							strcpy(cBuf, cTemp);
							SetWindowText(hEB, cBuf);
						}
						else
						{
							if (strlen(cBuf) == 1)
							{
								cBuf[0] = 0;		// Clear char buffer
								SetWindowText(hEB, "0.");
								nNew = 1;			// Set new digit
								dot = false;
							}
						}
					}
					break;
				}*/
				case BUTTOND:				// '+' 
				{
					functionflag = 1;			
					isFunctionActive = true;
					display2 = display2 + display1;
					break;
				}
				case BUTTONO:				// '-' 
				{
					functionflag = 2;			
					isFunctionActive = true;
					display2 = display2 + display1;
					break;
				}
				case BUTTONX:				// '*' 
				{
					functionflag = 3;				
					isFunctionActive = true;
					display2 = display2 + display1;
					break;
				}
				case BUTTONDZ:				// '/' 
				{
					functionflag = 4;				
					isFunctionActive = true;
					display2 = display2 + display1;
					break;
				}
				case BUTTONP:				// 'sqrt' 
				{
					functionflag = 5;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONS:				// silnia
				{
					functionflag = 6;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONLO:				// '1/x' 
				{
					functionflag = 7;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONSIN:				// sinus 
				{
					functionflag = 8;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}					
				case BUTTONCOS:				// cosinus
				{
					functionflag = 9;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONTG:				// tangens
				{
					functionflag = 10;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONLN:				// ln
				{
					functionflag = 11;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				case BUTTONLG:				// log10				
				{
					functionflag = 12;
					isFunctionActive = true;
					//display2 = display2 + display1;
					break;
				}
				
			}
			break;
		}
	
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wp, lp);
	}
	return 0;
}

void ustawWartosc(HWND hEB,double display)
{
	std::string s = std::to_string(display);
	SetWindowText(hEB, s.c_str());
}

double oblicz(int functionflag, double display1, double display2)
{
	switch (functionflag)
	{
		double wynik;

		/*case 0:
		{
			GetWindowText(hEB, cBuf, MAXOUT);
			dTotal = atof(cBuf);
			break;
		}*/
		case 1: //dodawanie
		{
			return wynik = display1 + display2;
			break;
		}
		case 2: //odejmowanie
		{
			return wynik = display2 - display1;
			break;
		}
		case 3: //mono¿enie
		{
			return wynik = display1 * display2;
			break;
		}
		case 4: //dzielenie
		{
			return wynik = display2 / display1;
			break;
		}
		case 5: //pierwiastek
		{
			return wynik = sqrt(display2);
			break;
		}
		case 6: //silnia
		{
			double wynik = 1;
			for (int i = display2; i>0; i--) // TO DO: zabezpieczenie przed liczeniem z nieca³kowitych
				wynik *= i;
			return wynik; 
			break;
		}
		case 7: //odwracanie liczby
		{
			return wynik = 1/display2;
			break;
		}
		case 8: //sinus
		{
			return wynik = sin(display2*(PI/180));
			break;
		}
		case 9: //cosinus
		{
			return wynik = cos(display2*(PI/180));
			break;
		}
		case 10: //tangens
		{
			return wynik = tan(display2*(PI/180));
			break;
		}
		case 11: //ln
		{
			if (display2 > 0)
				return wynik = log(display2); //TO DO: zadbaæ by dzia³a³o tylko dla liczb dodatnich
			else
				return display2;
			break;
		}
		case 12: //log10
		{
			if (display2 > 0)
				return wynik = log10(display2); //TO DO: zadbaæ by dzia³a³o tylko dla liczb dodatnich
			else
				return display2;
			break;
		}
		default:
			return 1;
	}	
}