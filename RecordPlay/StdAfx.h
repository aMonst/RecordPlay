// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>


// TODO: reference additional headers your program requires here

extern BOOL g_bIsRecord;//�Ƿ���¼��״̬
extern BOOL g_bLoad;//�Ƿ�����ļ�
extern HINSTANCE g_hDlg; //�Ի�����
extern HHOOK g_hRecord;//¼�ƹ��Ӿ��
extern HHOOK g_hReplay;//�طŹ��Ӿ��

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
