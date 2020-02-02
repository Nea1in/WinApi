// Win32Project8.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project8.h"
#include<iostream>
#include<stdio.h>
#include<string.h>


#define IDT_TIMER_1 1001
using namespace std;
HINSTANCE hInst;
HWND hPic;
HBITMAP hBitMap;




CHAR selected_item[255];
double gs_pay = 0;
double mc_pay = 0;

char textsaved[20];

double mc_items_amount[4] = { 0,0,0,0 };
double mc_items_prices[4] = { 4.00,5.40,7.20,4.40 };

char *fuelTypes[3] = { "A_95","B_93","C_91" };
double fuels[3] = { 9.50,9.45,9.25 };
int cur_gas;

void SetWindowToDefault(HWND hWnd){
	char* defaultFuelprice = new char[5];
	cur_gas = 0;
	sprintf(defaultFuelprice, "%0.2lf", fuels[0]);
	SetWindowTextA(GetDlgItem(hWnd, IDC_STATIC_FUEL_PRICE), defaultFuelprice);
	KillTimer(hWnd, IDT_TIMER_1);
	SetTimer(hWnd, IDT_TIMER_1, 10000, NULL);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK2), BM_SETCHECK, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK3), BM_SETCHECK, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK4), BM_SETCHECK, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDC_CHECK5), BM_SETCHECK, 0, 0);
	CheckDlgButton(hWnd,IDC_RADIO1, FALSE);
	CheckDlgButton(hWnd, IDC_RADIO2, FALSE);
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), FALSE); 	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT2), "");
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), FALSE);	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT3), "");
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), FALSE);	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT4), "");
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), FALSE);	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT5), "");
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), FALSE);	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT6), "");
	EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), FALSE);	SetWindowTextA(GetDlgItem(hWnd, IDC_EDIT7), "");

	gs_pay = 0;
	mc_pay = 0;
	cur_gas = 0;
	ShowWindow(GetDlgItem(hWnd, IDC_STATIC_TO_PAY_3), SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, RESULT_PAY_TYPE), SW_HIDE);
	SetWindowText(GetDlgItem(hWnd, IDC_STATIC100), L"До Оплати");
	SetWindowText(GetDlgItem(hWnd, IDC_STATIC_PAY_TYPE), L"грн.");

	SetWindowTextA(GetDlgItem(hWnd, IDC_STATIC_TO_PAY_1), "0");
	SetWindowTextA(GetDlgItem(hWnd, IDC_STATIC_TO_PAY_2), "0");
}

HWND notify;

BOOL CALLBACK    MainDlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, MainDlgProc);

	 return 0;
}



char* float_to_str(double myfloat) {
	char *str = new char[20];
	sprintf(str, "%0.2lf", myfloat);
	return str;
}
void recalculateAndPrint(HWND hDlg, int label_id) {
	double total_price = 0;
	if (label_id == IDC_STATIC_TO_PAY_2) {
		for (int i = 0; i < ARRAYSIZE(mc_items_amount); i++) {
			total_price += mc_items_amount[i] * mc_items_prices[i];
		}
		mc_pay = total_price;
		char* result = float_to_str(total_price);
		SetWindowTextA(GetDlgItem(hDlg, label_id), result);
	}
	else if (label_id == IDC_STATIC_TO_PAY_3) {
		total_price = mc_pay + gs_pay;
		char* result = float_to_str(total_price);

		ShowWindow(GetDlgItem(hDlg, IDC_STATIC_TO_PAY_3), 1);
		ShowWindow(GetDlgItem(hDlg, RESULT_PAY_TYPE), 1);

		SetWindowTextA(GetDlgItem(hDlg, label_id), result);
	}
}

BOOL CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG: {
		HICON hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hDlg, WM_SETICON, 1, (LPARAM)hIcon1);
		HWND hCombo;
		SendMessageA(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)fuelTypes[0]);
		SendMessageA(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)fuelTypes[1]);
		SendMessageA(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)fuelTypes[2]);
		SendMessageA(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		char* defaultFuelprice = new char[5];
		cur_gas = 0;
		sprintf(defaultFuelprice, "%0.2lf", fuels[0]);
		SetWindowTextA(GetDlgItem(hDlg, IDC_STATIC_FUEL_PRICE), defaultFuelprice);
		SetTimer(hDlg, IDT_TIMER_1, 10000, NULL);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON1: {
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_3);
		}
						  break;
		
		case IDC_COMBO1:
		{
			if (HIWORD(wParam) == CBN_SELENDOK) {
				/*EnableWindow(GetDlgItem(hDlg, IDC_RADIO1), TRUE);
				EnableWindow(GetDlgItem(hDlg, IDC_RADIO2), TRUE);*/
				int i = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
				SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETLBTEXT, i, (LPARAM)selected_item);


				char *price = new char[100];
				switch (selected_item[0])
				{
				case 'A': {
					sprintf(price, "%0.2lf", fuels[0]);
					cur_gas = 0;

				} break;
				case 'B': {
					sprintf(price, "%0.2lf", fuels[1]);
					cur_gas = 1;
				} break;
				case 'C': {
					sprintf(price, "%0.2lf", fuels[2]);
					cur_gas = 2;
				} break;
				default:
				{
					sprintf(price, "%0.2lf", fuels[0]);
					cur_gas = 0;
				}

				}
				SetWindowTextA(GetDlgItem(hDlg, IDC_STATIC_FUEL_PRICE), price);
			}
		}
		break;
		case IDC_EDIT6: {

			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT6), textsaved, 20);
			gs_pay = atof(textsaved)*fuels[cur_gas];
			char *str = float_to_str(gs_pay);
			SetWindowTextA(GetDlgItem(hDlg, IDC_STATIC_TO_PAY_1), str);
		}break;
		case IDC_EDIT7: {

			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT7), textsaved, 20);
			gs_pay = atof(textsaved);
			double l_amount = gs_pay / fuels[cur_gas];
			char *str = float_to_str(l_amount);

			SetWindowTextA(GetDlgItem(hDlg, IDC_STATIC_TO_PAY_1), str);
		}

		case IDC_CHECK2:
		{
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT2))) {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT2), FALSE);

			}
			else {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT2), TRUE);
			}
			mc_items_amount[0] = 0;
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_CHECK3:
		{
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT3))) {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT3), FALSE);

			}
			else {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT3), TRUE);
			}
			mc_items_amount[1] = 0;
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_CHECK4:
		{
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT4))) {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT4), FALSE);

			}
			else {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT4), TRUE);
			}
			mc_items_amount[2] = 0;
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_CHECK5:
		{
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT5))) {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT5), FALSE);

			}
			else {
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT5), TRUE);
			}
			mc_items_amount[3] = 0;
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);

		}
		break;
		case IDC_RADIO1:
		{
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT6), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT7), FALSE);
			SetWindowText(GetDlgItem(hDlg, IDC_STATIC100), L"До Оплати");
			SetWindowText(GetDlgItem(hDlg, IDC_STATIC_PAY_TYPE), L"грн.");

		}
		break;
		case IDC_RADIO2:
		{
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT7), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT6), FALSE);
			SetWindowText(GetDlgItem(hDlg, IDC_STATIC_PAY_TYPE), L"л.");
			SetWindowText(GetDlgItem(hDlg, IDC_STATIC100), L"До Видачі");
		}
		break;
		case IDC_EDIT2:
		{
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), textsaved, 20);
			if (IsDlgButtonChecked(hDlg, IDC_CHECK2) && textsaved) {
				mc_items_amount[0] = atoi(textsaved);
			}
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_EDIT3:
		{
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), textsaved, 20);

			if (IsDlgButtonChecked(hDlg, IDC_CHECK3) && textsaved) {
				mc_items_amount[1] = atoi(textsaved);
			}
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_EDIT4:
		{
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT4), textsaved, 20);
			if (IsDlgButtonChecked(hDlg, IDC_CHECK4) && textsaved) {
				mc_items_amount[2] = atoi(textsaved);
			}
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;
		case IDC_EDIT5:
		{
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT5), textsaved, 20);
			if (IsDlgButtonChecked(hDlg, IDC_CHECK5) && textsaved) {
				mc_items_amount[3] = atoi(textsaved);
			}
			recalculateAndPrint(hDlg, IDC_STATIC_TO_PAY_2);
		}
		break;

		default:
			break;
		}
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
	}
	case WM_TIMER: {
		switch (wParam)
		{
		case IDT_TIMER_1:
		{
			HWND hwndTimer = GetDlgItem(hDlg, IDT_TIMER_1);   // handle to window for timer messages 
			MSG msg;          // message structure 

			while (GetMessage(&msg, // message structure 
				NULL,           // handle to window to receive the message 
				0,           // lowest message to examine 
				0))          // highest message to examine 
			{

				// Post WM_TIMER messages to the hwndTimer procedure. 

				if (msg.message == WM_TIMER)
				{
					msg.hwnd = hwndTimer;
					
					int msgboxID = MessageBoxA(hDlg, "Buy something or go away?", "Notify", MB_YESNO);
					switch (msgboxID) {
						case IDNO: {
							SetWindowToDefault(hDlg);
							//PostQuitMessage(0);
						}
						case IDYES:{
							KillTimer(hDlg, IDT_TIMER_1);
							SetTimer(hDlg, IDT_TIMER_1, 10000, NULL);
						}
						   break;
					}
					
					break;
					//SetTimer(hDlg, IDT_TIMER_1, 10000, NULL);
				}

				TranslateMessage(&msg); // translates virtual-key codes 
				DispatchMessage(&msg);  // dispatches message to window 
			}

		}

		return 0;
		}
	}break;
	case WM_PAINT:
	{
		
	}break;

	return TRUE;
	}
	return FALSE;
}
