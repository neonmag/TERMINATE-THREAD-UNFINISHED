#include "PriorityDlg.h"
using namespace std;

int index;
int length;
TCHAR* buf;
bool full = false;

void CPriorityDlg::PrintProcessInfo(PROCESSENTRY32 processInfo, HWND hList)
{
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(processInfo.szExeFile));
}

CPriorityDlg* CPriorityDlg::ptr = NULL;

CPriorityDlg::CPriorityDlg(void)
{
	ptr = this;
}

CPriorityDlg::~CPriorityDlg(void)
{

}

void CPriorityDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CPriorityDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	for (int i = 0; i < 3; i++)
	{
		hButton[i] = GetDlgItem(hwnd, IDC_BUTTON1 + i);
	}
	hList = GetDlgItem(hwnd, IDC_LIST1);
	return TRUE;
}

void CPriorityDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BUTTON1:
	{
		if (full == true)
		{
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
		}
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 processInfo = { sizeof(PROCESSENTRY32) };
		res = Process32First(hSnapshot, &processInfo);
		if (res == TRUE) {
			do {
				PrintProcessInfo(processInfo, hList);
			} while (Process32Next(hSnapshot, &processInfo));
		}
		CloseHandle(hSnapshot);
		full = true;
		break;
	}
	case IDC_BUTTON2:
	{ 
		index = SendMessage(hList, LB_GETCURSEL, 0, 0);
		length = SendMessage(hList, LB_GETTEXTLEN, index, 0);
		buf = new TCHAR[length + 1];
		SendMessage(hList, LB_GETTEXT, index, LPARAM(buf));
		HANDLE h = GetStdHandle(DWORD(buf));
		TerminateThread(h, 0);
		CloseHandle(h);
		break;
	}
	}
}

BOOL CALLBACK CPriorityDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}