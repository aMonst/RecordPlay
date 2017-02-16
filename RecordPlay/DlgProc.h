#ifndef __DLGPROC_H__
#define __DLGPROC_H__
#include "windows.h"
#include "DlgMsgMap.h"
#include "resource.h"

DECLARE_DLGMSGMAP(RecordDlg);
DECLARE_DLGMSGPROC(RecordDlg);

typedef BOOL (*PBTNPROC)(HWND hDlg,WPARAM wParam, LPARAM lParam);

struct BTNMSG
{
	WORD uBtnID;
	PBTNPROC pBtnProc;
};

BOOL OnClose(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnCopy(HWND hDlg,WPARAM wParam, LPARAM lParam);
BOOL OnPlayBack(HWND hDlg,WPARAM wParam, LPARAM lParam);
BOOL OnSave(HWND hDlg,WPARAM wParam, LPARAM lParam);
BOOL OnLoad(HWND hDlg,WPARAM wParam, LPARAM lParam);

#endif