#ifndef __HOOKPROC_H__
#define __HOOKPROC_H__
#include "windows.h"
typedef struct EVENTNODE
{
	EVENTMSG EventMsg;
	EVENTNODE *pNextMsg;
};

typedef EVENTNODE* LPEVENTNODE;

LRESULT CALLBACK JournalRecordProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK JournalPlaybackProc(int code, WPARAM wParam, LPARAM lParam);
void AddMsgList(EVENTNODE *pNewMsg);
void FreeMsgList();

extern HHOOK g_hRecord;//录制钩子句柄
extern HHOOK g_hReplay;//回放钩子句柄
extern LPEVENTNODE g_pMsgList;//链表头指针
extern UINT uLen;//链表长度

#endif