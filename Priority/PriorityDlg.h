#pragma once
#include "Header.h"


class CPriorityDlg
{
public:
	CPriorityDlg(void);
public:
	~CPriorityDlg(void);
	void PrintProcessInfo(PROCESSENTRY32 processInfo, HWND hList);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CPriorityDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hButton[3], hList;
	HANDLE hSnapshot;
	BOOL res;
};
