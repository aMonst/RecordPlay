#include "stdafx.h"
#include "HookProc.h"

LPEVENTNODE g_pMsgList;//����ͷָ��
DWORD g_NowTime;//��ǰ��Ϣ��ʱ��
DWORD g_PreTime;//ǰһ����Ϣ��ʱ��
UINT uLen = 0;//������

HHOOK g_hRecord;
HHOOK g_hReplay;

LRESULT CALLBACK JournalRecordProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		return ::CallNextHookEx(g_hRecord, code, wParam, lParam);
	}

	if (HC_ACTION == code)
	{
		EVENTNODE *pNewMsg = new EVENTNODE;
		pNewMsg->EventMsg.hwnd = ((LPEVENTMSG)lParam)->hwnd;
		pNewMsg->EventMsg.message = ((LPEVENTMSG)lParam)->message;
		pNewMsg->EventMsg.paramH = ((LPEVENTMSG)lParam)->paramH;
		pNewMsg->EventMsg.paramL = ((LPEVENTMSG)lParam)->paramL;
		pNewMsg->EventMsg.time = ((LPEVENTMSG)lParam)->time;
		pNewMsg->pNextMsg = NULL;
		AddMsgList(pNewMsg);
		uLen++;
	}

	return ::CallNextHookEx(g_hRecord, code, wParam, lParam);
}

LRESULT CALLBACK JournalPlaybackProc(int code, WPARAM wParam, LPARAM lParam)
{
	static BOOL bIsFirst = TRUE;//�Ƿ��ǵ�һ�ν���HC_GETNEXT
	static EVENTNODE *s_pPreMsg = g_pMsgList;//��ǰ��Ϣ
	static EVENTNODE *s_pLastMsg;//ǰһ����Ϣ
	static UINT i = 0;//��ǰ�ڵ�������λ��

	if (code < 0)
	{
		return ::CallNextHookEx(g_hReplay, code, wParam, lParam);
	}
	switch (code)
	{
	case HC_GETNEXT:
		{
			if (NULL != s_pPreMsg && i < uLen -1)
			{
				((LPEVENTMSG)lParam)->hwnd = s_pPreMsg->EventMsg.hwnd;
				((LPEVENTMSG)lParam)->message = s_pPreMsg->EventMsg.message;
				((LPEVENTMSG)lParam)->paramH = s_pPreMsg->EventMsg.paramH;
				((LPEVENTMSG)lParam)->paramL = s_pPreMsg->EventMsg.paramL;
				((LPEVENTMSG)lParam)->time = s_pPreMsg->EventMsg.time;
			}else
			{
				return 0;
			}

			if (bIsFirst && s_pPreMsg != g_pMsgList)
			{
				bIsFirst = FALSE;
				g_NowTime = s_pPreMsg->EventMsg.time;
				g_PreTime = s_pLastMsg->EventMsg.time;
				return g_NowTime - g_PreTime;
			}else
			{
				return 0;
			}
		}
		break;
	case HC_SKIP:
		{
			if (NULL != s_pPreMsg->pNextMsg)
			{
				bIsFirst = TRUE;
				s_pLastMsg = s_pPreMsg;
				s_pPreMsg = s_pPreMsg->pNextMsg;
				i++;
			}else
			{
				i = 0;
				s_pPreMsg = g_pMsgList;

				UnhookWindowsHookEx(g_hReplay);
			}
		}
		break;
	default:
		return ::CallNextHookEx(g_hReplay, code, wParam, lParam);
	}
	return 0;
}

void AddMsgList(EVENTNODE *pNewMsg)
{
	if (NULL == g_pMsgList)
	{
		g_pMsgList = pNewMsg;
	}else
	{
		EVENTNODE *pTemp = g_pMsgList;
		while (NULL != pTemp->pNextMsg)
		{
			pTemp = pTemp->pNextMsg;
		}

		pTemp->pNextMsg = pNewMsg;
	}
}

void FreeMsgList()
{
	EVENTNODE *pTemp = g_pMsgList;
	while (NULL != pTemp)
	{
		g_pMsgList = pTemp->pNextMsg;

		delete pTemp;
		pTemp = g_pMsgList;
	}
	uLen = 0;
}