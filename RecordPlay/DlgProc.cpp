#include "stdafx.h"
#include "DlgProc.h"
#include "HookProc.h"

BOOL g_bIsRecord = TRUE;
BOOL g_bLoad = FALSE;

BEGIN_DLG_MSGMAP(RecordDlg)
	ON_DLG_MSGMAP(WM_CLOSE, OnClose)
	ON_DLG_MSGMAP(WM_COMMAND, OnCommand)
END_DLG_MSGMAP()

BTNMSG g_BtnMsg[] = {
	{IDB_COPY, OnCopy},
	{IDB_PLAYBACK, OnPlayBack},
	{IDB_SAVE, OnSave},
	{IDB_LOAD, OnLoad},
	{0, NULL},
};

IMPLEMENT_DLGPROC(RecordDlg)

BOOL OnClose(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	FreeMsgList();
	EndDialog(hDlg,WM_CLOSE);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	BTNMSG *pBtnMsg = g_BtnMsg;

	while (0 != pBtnMsg->uBtnID)
	{
		if (LOWORD(wParam) == pBtnMsg->uBtnID)
		{
			return pBtnMsg->pBtnProc(hDlg,wParam, lParam);
		}
		pBtnMsg++;
	}

	return FALSE;
}

BOOL OnCopy(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	if (BN_CLICKED == HIWORD(wParam))
	{
		if (g_bIsRecord)
		{
			SetWindowText(GetDlgItem(hDlg, IDB_COPY), "停止");
			g_bIsRecord = FALSE;
			g_hRecord = SetWindowsHookEx(WH_JOURNALRECORD, (HOOKPROC)JournalRecordProc, GetModuleHandle(NULL), 0);
		}
		else
		{
			SetWindowText(GetDlgItem(hDlg, IDB_COPY), "录制");
			g_bIsRecord = TRUE;
			UnhookWindowsHookEx(g_hRecord);
		}

		if (g_bIsRecord)
		{
			EnableWindow(GetDlgItem(hDlg, IDB_PLAYBACK),TRUE);
		}
		else
		{
			EnableWindow(GetDlgItem(hDlg, IDB_PLAYBACK),FALSE);
		}
	}
	return TRUE;
}

BOOL OnPlayBack(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	g_hReplay = SetWindowsHookEx(WH_JOURNALPLAYBACK, (HOOKPROC)JournalPlaybackProc, GetModuleHandle(NULL), 0);
	return TRUE;
}

BOOL OnSave(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	if (NULL != g_pMsgList)
	{
		HANDLE hFile = CreateFile("MsgFile.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		EVENTNODE *pTemp = g_pMsgList;
		DWORD dwRealWrite;//真实写入的大小
		while (NULL != pTemp)
		{
			WriteFile(hFile, &(pTemp->EventMsg), sizeof(EVENTMSG), &dwRealWrite, NULL);

			if (0 == dwRealWrite)
			{
				break;
			}

			pTemp = pTemp->pNextMsg;
		}

		CloseHandle(hFile);
	}
	return TRUE;
}

BOOL OnLoad(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	g_bLoad = TRUE;
	FreeMsgList();
	HANDLE hFile = CreateFile("MsgFile.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRelRead;
	EVENTNODE *pEndList;

	do 
	{
		if(NULL == g_pMsgList)
		{
			g_pMsgList = new EVENTNODE;
			ReadFile(hFile, &(g_pMsgList->EventMsg), sizeof(EVENTMSG),&dwRelRead, NULL);
			if (0 == dwRelRead)
			{
				break;
			}
			pEndList = g_pMsgList;
		}else
		{
			EVENTNODE *pNewMsg = new EVENTNODE;
			pNewMsg->pNextMsg = NULL;
			ReadFile(hFile, &(pNewMsg->EventMsg), sizeof(EVENTMSG),&dwRelRead, NULL);
			if (0 == dwRelRead)
			{
				break;
			}
			pEndList->pNextMsg = pNewMsg;
			pEndList = pEndList->pNextMsg;
		}

		uLen++;
	} while (TRUE);

	if (g_bLoad && NULL != g_pMsgList)
	{
		EnableWindow(GetDlgItem(hDlg, IDB_PLAYBACK),TRUE);
	}
	else
	{
		EnableWindow(GetDlgItem(hDlg, IDB_PLAYBACK),FALSE);
	}

	CloseHandle(hFile);
	return TRUE;
}