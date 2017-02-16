// RecordPlay.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DlgProc.h"
HINSTANCE g_hDlg;
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	g_hDlg = hInstance;
	DialogBox(g_hDlg, MAKEINTRESOURCE(IDD_DIALOG1), NULL, GET_DLGPROC(RecordDlg));	
	return 0;
}



