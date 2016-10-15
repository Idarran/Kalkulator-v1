//Program:		Kalkulator
//Programista:	Hubert Hodowaniec

#include <windows.h>
#include <math.h>

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
#define BUTTONPR 122 //procent

#define BUTTONSIN 123 
#define BUTTONCOS 124
#define BUTTONTG 125
#define BUTTONLN 126
#define BUTTONLG 127

#define EDITBX 666 //pole tekstowe

#define MAXOUT 25
#define MAXIN  10


//prototypy funkcji
void ustawWartosc(char* val);
void oblicz(void);
double liczbaOdwrotna(double val);
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp);
HWND UstawOkno(char* cClass, char* cTitle, int nWidth, int nHeight, HINSTANCE hInstance);

//zmienne globalne
HWND hOkno,
hB0, hB1, hB2, hB3, hB4, hB5, hB6, hB7, hB8, hB9,
hBC, hBB,
hBD, hBO, hBX, hBDZ,
hBR, hBK, hBPI,
hBP, hBS, hBLO, hBPR,
hBSIN, hBCOS, hBTG, hBLN, hBLG,
hEB;

int flag_Fun = 0;		//flaga funkcji: 0=brak, 1=dodawanie, 2=odejmowanie, itd.
int flag_New = 1;		//flaga nowy/kolejny
double dTotal = 0;		//wartoœæ bufora
char cBuf[MAXOUT];		//bufor


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	char* cClass = "Kalkulator";	// nazwa klasy
	char* cTitle = "Kalkulator";	// nazwa okienka
	const int nSzer = 320;			// szerokoœæ okienka
	const int nWys = 250;			// wysokoœæ okienka

	MSG msg;

	hOkno = UstawOkno(cClass, cTitle, nSzer, nWys, hInstance);

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

	SetWindowText(hEB, "0."); //ustawia wartoœæ pocz¹tkow¹ w oknie


	HWND UstawOkno(char* cClass, char* cTitle, int nWidth, int nHeight, HINSTANCE hInstance)
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
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "cClass";
		RegisterClassEx(&wc);

		//tworzenie okna...
		hOkno = CreateWindowEx(0, cClass, cTitle,
			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, nSzer, nWys,
			NULL, NULL, hInstance, NULL);

		if (NULL == hOkno) 
			return -1; //sprawdzenie, czy siê uda³o

		return hOkno;
	}

	//pêtla obs³ugi komunikatów
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//funkcja obs³ugi komunikatów okna
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
	static bool dot;
	static bool backsp;

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
				case BUTTON0:			// BUTTON0 clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetWindowText(hEB, "0.");
						nNew = 0;
					}

					if ((strlen(cBuf) > 0) && (strlen(cBuf) < MAXIN))
					{
						strcat(&cBuf[0], "0");
						SetWindowText(hEB, cBuf);
					}

					backsp = true;

					break;
				}
				case BUTTON1:			// BUTTON1 clicked
				{
					ustawWartosc("1");
					backsp = true;

					break;
				}
				case BUTTON2:			// BUTTON2 clicked
				{
					ustawWartosc("2");
					backsp = true;

					break;
				}
				case BUTTON3:			// BUTTON3 clicked
				{
					ustawWartosc("3");
					backsp = true;

					break;
				}
				case BUTTON4:			// BUTTON4 clicked
				{
					ustawWartosc("4");
					backsp = true;

					break;
				}
				case BUTTON5:			// BUTTON5 clicked
				{
					ustawWartosc("5");
					backsp = true;

					break;
				}
				case BUTTON6:			// BUTTON6 clicked
				{
					ustawWartosc("6");
					backsp = true;

					break;
				}
				case BUTTON7:			// BUTTON7 clicked
				{
					ustawWartosc("7");
					backsp = true;
					break;
				}
				case BUTTON8:			// BUTTON8 clicked
				{
					ustawWartosc("8");
					backsp = true;
					break;
				}
				case BUTTON9:			// BUTTON9 clicked
				{
					ustawWartosc("9");
					backsp = true;
					break;
				}
				case BUTTONPI:
				{
					ustawWartosc("3.14");
					backsp = true;
					break;
				}
				case BUTTONK:			// Dot clicked
				{
					if (nNew)
					{
						cBuf[0] = 0;
						SetWindowText(hEB, cBuf);
						nNew = 0;
					}

					if ((!dot) && (strlen(cBuf) < MAXIN))
					{
						strcat(&cBuf[0], ".");
						SetWindowText(hEB, cBuf);
						dot = true;
					}

					backsp = true;

					break;
				}
				case BUTTONC:					// BUTTON C clicked
				{
					dTotal = 0;					// Clear total
					cBuf[0] = 0;				// Clear char buffer
					SetWindowText(hEB, "0.");
					nNew = 1;					// Set new digit
					nFunc = 0;					// set function to none
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONB:					// Backspace clicked
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
				}
				case BUTTOND:				// '+' clicked
				{
					oblicz();
					nFunc = 1;				// Set function to add
					dot = false;
					backsp = false;

					break;
				}
				case BUTTONO:				// '-' clicked
				{
					oblicz();
					nFunc = 2;				// Set function to subtract
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONX:				// 'x' clicked
				{
					oblicz();
					nFunc = 3;				// Set function to multiply
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONDZ:				// '/' clicked
				{
					oblicz();
					nFunc = 4;				// Set function to divide
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONR:				// '=' clicked
				{
					oblicz();
					nFunc = 0;
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONP:				// 'sqrt' clicked
				{
					double dRoot;

					GetWindowText(hEB, cBuf, MAXOUT);
					dRoot = sqrt(atof(cBuf));

					cBuf[0] = 0;			// Empty char buffer
					_gcvt(dRoot, MAXOUT, cBuf);
					SetWindowText(hEB, cBuf);
					nNew = 1;				// Set new digit
					dot = false;
					backsp = false;

					break;
				}
				case BUTTONLO:				// '1/x' clicked
				{
					double dRecip;

					GetWindowText(hEB, cBuf, MAXOUT);
					dRecip = 1 / atof(cBuf);

					cBuf[0] = 0;			// Empty char buffer
					_gcvt(dRecip, MAXOUT, cBuf);
					SetWindowText(hEB, cBuf);
					nNew = 1;				// Set new digit
					dot = false;
					backsp = false;
					break;
				}
				case BUTTONS:				// 'x!' clicked
				{
					double dFact;
					double dFraction, dInt;

					GetWindowText(hEB, cBuf, MAXOUT);

					if (atof(cBuf)<0)
					{
						strcpy(cBuf, "-E-");
						dTotal = 0;
					}
					else
					{
						dFraction = modf(atof(cBuf), &dInt);

						if ((dFraction == 0) && (dInt >= 0))
						{
							dFact = Factorial(atof(cBuf));
							cBuf[0] = 0;			// Empty char buffer
							_gcvt(dFact, MAXOUT, cBuf);
						}
						else
						{
							strcpy(cBuf, "-E-");
							dTotal = 0;
						}
					}

					SetWindowText(hEB, cBuf);
					nNew = 1;					// Set new digit
					dot = false;
					backsp = false;
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