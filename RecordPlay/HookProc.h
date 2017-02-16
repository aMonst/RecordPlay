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

extern HHOOK g_hRecord;//¼�ƹ��Ӿ��
extern HHOOK g_hReplay;//�طŹ��Ӿ��
extern LPEVENTNODE g_pMsgList;//����ͷָ��
extern UINT uLen;//������

#endif