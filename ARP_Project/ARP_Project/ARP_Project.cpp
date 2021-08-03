#include "stdafx.h"

//함수 구현
int __cdecl ARP_send(char * macad, char * send_ip, int k);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
BOOL GetMACAddress();
BOOL CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
BOOL GetMyIP();
DWORD WINAPI cachetable_thread(LPVOID);
void SetBitmap();

#define MAX_SEND_IMAGE 9

//전역변수
HDC hdc;
PAINTSTRUCT ps;
DWORD ThreadID;
HANDLE hthread[100];
HWND dig;
HINSTANCE g_inst;
LRESULT timeoutout;
HBITMAP send_packet[MAX_SEND_IMAGE], request[3][6], cach_table;

char arr_ip[5][16]={0};
char arr_mac[5][17]={0};
int empty_Line=0;
int table_Line_used[5]={0};


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_inst = hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDG_Dlg1), NULL, WinProc);
	return TRUE;
}


BOOL CALLBACK WinProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	dig=hDlg;
	int index=0;
	int thread_num=0;

	send_packet[0] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_DEFAULT));

	switch(uMsg)
	{
	case WM_INITDIALOG:
		GetMyIP();
		GetMACAddress();
		SetTimer(dig, 1, 100, NULL);
		SendMessage(GetDlgItem(dig, IDC_LIST4), LB_ADDSTRING, 0, (LPARAM)"FREE");
		SendMessage(GetDlgItem(dig, IDC_LIST10), LB_ADDSTRING, 0, (LPARAM)"FREE");
		SendMessage(GetDlgItem(dig, IDC_LIST16), LB_ADDSTRING, 0, (LPARAM)"FREE");
		SendMessage(GetDlgItem(dig, IDC_LIST22), LB_ADDSTRING, 0, (LPARAM)"FREE");
		SendMessage(GetDlgItem(dig, IDC_LIST28), LB_ADDSTRING, 0, (LPARAM)"FREE");
		return TRUE;
	case WM_PAINT:		
		hdc = BeginPaint(dig, &ps);
		DrawBitmap(hdc, 0, 105, send_packet[0]);
				ReleaseDC(dig, hdc);
		EndPaint(dig, &ps);
		return TRUE;
	case WM_TIMER:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			hthread[thread_num]=CreateThread(NULL,0,cachetable_thread,NULL,0,&ThreadID);
			thread_num++;
			return TRUE;
		case IDCANCEL:
			EndDialog(dig, 0);
			return TRUE;
		}
	}
	return FALSE;
}


DWORD WINAPI cachetable_thread(LPVOID ipParam)
{
	int i,j, k, l, m;
	HWND TABLE_STATE, TABLE_QUEUE, TABLE_ATTEMPT, TABLE_TIMEOUT, TABLE_IP, TABLE_MAC;
	LRESULT queue_index, state_index, attempt_index, timeout_index, mac_index, ip_index;
	char send_ip[16]={"000000000000000"};
	char macad[18];

	int attem=1, queue, timeout=900; 
    char quebuffer[5], attemptbuffer[5], timeoutbuffer[5];
	int attempt=0;
	char *ap = attemptbuffer;
	char *qp = quebuffer;
	char *tp = timeoutbuffer;

	int sig;
	char state[30]={"FREE"};
	char nullch[2]={" "};

	SetBitmap(); //비트맵 세팅
	GetDlgItemTextA(dig, IDC_IPADDRESS1, send_ip, 16);

	for(j=0;j<MAX_SEND_IMAGE-1;j++)
	{
		if(table_Line_used[j]==0)
		{	
			empty_Line=j;
			break;
		}
	}
	
	sig = ARP_send(macad,send_ip,j);


	for(k=0;k<MAX_SEND_IMAGE;k++)	
	{
		Sleep(200);
		hdc = GetDC(dig);
		DrawBitmap(hdc, 0, 105, send_packet[k]);
	}
	strcpy(arr_ip[j],send_ip);
	
	switch(empty_Line){
		case 0:
			TABLE_STATE = GetDlgItem(dig, IDC_LIST4);
			TABLE_QUEUE = GetDlgItem(dig, IDC_LIST5);
			TABLE_ATTEMPT = GetDlgItem(dig, IDC_LIST6);
			TABLE_TIMEOUT = GetDlgItem(dig, IDC_LIST7);
			TABLE_IP = GetDlgItem(dig, IDC_LIST8);
			TABLE_MAC = GetDlgItem(dig, IDC_LIST9);
			table_Line_used[0]=1;
			break;
		case 1:
			TABLE_STATE = GetDlgItem(dig, IDC_LIST10);
			TABLE_QUEUE = GetDlgItem(dig, IDC_LIST11);
			TABLE_ATTEMPT = GetDlgItem(dig, IDC_LIST12);
			TABLE_TIMEOUT = GetDlgItem(dig, IDC_LIST13);
			TABLE_IP = GetDlgItem(dig, IDC_LIST14);
			TABLE_MAC = GetDlgItem(dig, IDC_LIST15);
			table_Line_used[1]=1;
			break;
		case 2:
			TABLE_STATE = GetDlgItem(dig, IDC_LIST16);
			TABLE_QUEUE = GetDlgItem(dig, IDC_LIST17);
			TABLE_ATTEMPT = GetDlgItem(dig, IDC_LIST18);
			TABLE_TIMEOUT = GetDlgItem(dig, IDC_LIST19);
			TABLE_IP = GetDlgItem(dig, IDC_LIST20);
			TABLE_MAC = GetDlgItem(dig, IDC_LIST21);
			table_Line_used[2]=1;
			break;
		case 3:
			TABLE_STATE = GetDlgItem(dig, IDC_LIST22);
			TABLE_QUEUE = GetDlgItem(dig, IDC_LIST23);
			TABLE_ATTEMPT = GetDlgItem(dig, IDC_LIST24);
			TABLE_TIMEOUT = GetDlgItem(dig, IDC_LIST25);
			TABLE_IP = GetDlgItem(dig, IDC_LIST26);
			TABLE_MAC = GetDlgItem(dig, IDC_LIST27);
			table_Line_used[3]=1;
			break;
		case 4:
			TABLE_STATE = GetDlgItem(dig, IDC_LIST28);
			TABLE_QUEUE = GetDlgItem(dig, IDC_LIST29);
			TABLE_ATTEMPT = GetDlgItem(dig, IDC_LIST30);
			TABLE_TIMEOUT = GetDlgItem(dig, IDC_LIST31);
			TABLE_IP = GetDlgItem(dig, IDC_LIST32);
			TABLE_MAC = GetDlgItem(dig, IDC_LIST33);
			table_Line_used[4]=1;
			break;
	}
	empty_Line++;

	srand(time(NULL));	
	queue = rand() % 50 + 1;
	l = rand() % 3;
	_itoa( queue, quebuffer, 10 );
	_itoa( attem, attemptbuffer, 10 );
	_itoa( timeout, timeoutbuffer, 10 );

	SendMessage(TABLE_STATE, LB_RESETCONTENT, 0, 0);
	strcpy(state,"Pendding");
	timeout_index=SendMessage(TABLE_TIMEOUT, LB_ADDSTRING, 0, (LPARAM)nullch);
	mac_index=SendMessage(TABLE_MAC, LB_ADDSTRING, 0, (LPARAM)nullch);
	state_index=SendMessage(TABLE_STATE, LB_ADDSTRING, 0, (LPARAM)state);
	ip_index=SendMessage(TABLE_IP, LB_ADDSTRING, 0, (LPARAM)send_ip);
	queue_index=SendMessage(TABLE_QUEUE, LB_ADDSTRING, 0, (LPARAM)qp);
	attempt_index=SendMessage(TABLE_ATTEMPT, LB_ADDSTRING, 0, (LPARAM)ap);
	if(sig==1)
	{
		for(i=0;i<6;i++)
		{
			Sleep(2000);
			sig = ARP_send(macad,send_ip,j);
			if(sig==2)
				break;
			attempt++;
			_itoa( attempt, attemptbuffer, 10 );
			SendMessage(TABLE_ATTEMPT, LB_DELETESTRING, attempt_index, 0);
			SendMessage(TABLE_ATTEMPT, LB_INSERTSTRING, attempt_index, (LPARAM)ap);
		}
		if(sig==2)
		{
			for(k=0;k<6;k++)
			{
				Sleep(500);
				hdc = GetDC(dig);
				DrawBitmap(hdc, 0, 105, request[l][k]);
			}
			SendMessage(TABLE_STATE, LB_RESETCONTENT, state_index, 0);
			strcpy(state,"Resolved");
			SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
			SendMessage(TABLE_STATE, LB_DELETESTRING, state_index,0);
			SendMessage(TABLE_MAC, LB_DELETESTRING, mac_index, 0);
			SendMessage(TABLE_TIMEOUT, LB_INSERTSTRING, timeout_index, (LPARAM)tp);
			SendMessage(TABLE_MAC, LB_INSERTSTRING, mac_index, (LPARAM)macad);
			SendMessage(TABLE_STATE, LB_INSERTSTRING, state_index, (LPARAM)state);
			if(timeout != 0)
			{
				while(timeout > 0)
				{
					Sleep(500);
					SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
					timeout = timeout - 60;
					_itoa( timeout, timeoutbuffer, 10 );
					SendMessage(TABLE_TIMEOUT, LB_INSERTSTRING, timeout_index, (LPARAM)tp);
				}
			SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
			SendMessage(TABLE_MAC, LB_DELETESTRING, state_index, 0);
			SendMessage(TABLE_STATE, LB_DELETESTRING, mac_index, 0);
			SendMessage(TABLE_IP, LB_DELETESTRING, ip_index, 0);
			SendMessage(TABLE_QUEUE, LB_DELETESTRING, queue_index, 0);
			SendMessage(TABLE_ATTEMPT, LB_DELETESTRING, attempt_index, 0);
			strcpy(arr_ip[j],"");
			table_Line_used[j]=0;
			return 0;
			}
		}
		else
		{
			SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
			SendMessage(TABLE_MAC, LB_DELETESTRING, state_index, 0);
			SendMessage(TABLE_STATE, LB_RESETCONTENT, state_index, 0);
			SendMessage(TABLE_STATE, LB_ADDSTRING, mac_index, (LPARAM)"FREE");
			SendMessage(TABLE_IP, LB_DELETESTRING, ip_index, 0);
			SendMessage(TABLE_QUEUE, LB_DELETESTRING, queue_index, 0);
			SendMessage(TABLE_ATTEMPT, LB_DELETESTRING, attempt_index, 0);
			attem=1;
			strcpy(arr_ip[j],"");
			table_Line_used[j]=0;
			return 0;
		}
	}
	else if(sig == 2)
	{
		for(k=0;k<6;k++)
		{
			Sleep(500);
			hdc = GetDC(dig);
			DrawBitmap(hdc, 0, 105, request[l][k]);
		}
		SendMessage(TABLE_STATE, LB_RESETCONTENT, state_index, 0);
		strcpy(state,"Resolved");
		SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
		SendMessage(TABLE_STATE, LB_DELETESTRING, state_index, 0);
		SendMessage(TABLE_MAC, LB_DELETESTRING, mac_index, 0);
		SendMessage(TABLE_TIMEOUT, LB_INSERTSTRING, timeout_index, (LPARAM)tp);
		SendMessage(TABLE_MAC, LB_INSERTSTRING, mac_index, (LPARAM)macad);
		SendMessage(TABLE_STATE, LB_INSERTSTRING, state_index, (LPARAM)state);
		if(timeout != 0)
		{
			while(timeout > 0)
			{
				Sleep(2000);
				timeout = timeout - 60;
				_itoa( timeout, timeoutbuffer, 10 );
				char *tp = timeoutbuffer;
				SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
				SendMessage(TABLE_TIMEOUT, LB_INSERTSTRING, timeout_index, (LPARAM)tp);
			}
			SendMessage(TABLE_TIMEOUT, LB_DELETESTRING, timeout_index, 0);
			SendMessage(TABLE_MAC, LB_DELETESTRING, state_index, 0);
			SendMessage(TABLE_STATE, LB_RESETCONTENT, state_index, 0);
			SendMessage(TABLE_STATE, LB_ADDSTRING, mac_index, (LPARAM)"FREE");
			SendMessage(TABLE_IP, LB_DELETESTRING, ip_index, 0);
			SendMessage(TABLE_QUEUE, LB_DELETESTRING, queue_index, 0);
			SendMessage(TABLE_ATTEMPT, LB_DELETESTRING, attempt_index, 0);
		}
	}
	strcpy(arr_ip[j],"");
	table_Line_used[j]=0;
	return 0;	
}

BOOL GetMACAddress()
{
	char * macad = new char[30];
	HWND INIT_MAC;
	INIT_MAC = GetDlgItem(dig, IDC_LIST2);
    DWORD size = sizeof(PIP_ADAPTER_INFO);

    PIP_ADAPTER_INFO Info;

    ZeroMemory( &Info, size );

    int result = GetAdaptersInfo( Info, &size );        // 첫번째 랜카드 MAC address 가져오기

    if (result == ERROR_BUFFER_OVERFLOW)    // GetAdaptersInfo가 메모리가 부족하면 재 할당하고 재호출
    {
        Info = (PIP_ADAPTER_INFO)malloc(size);
        GetAdaptersInfo( Info, &size );
    }

	sprintf(macad,"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X",Info->Address[0], Info->Address[1], Info->Address[2], Info->Address[3], Info->Address[4], Info->Address[5]);
	SendMessage(INIT_MAC, LB_ADDSTRING, 0, (LPARAM)macad);
    return true;
}


BOOL GetMyIP()
{
	WSADATA wsa;
	IN_ADDR addr;
	HWND hList;
	hList = GetDlgItem(dig, IDC_LIST1);
	char LocalName[256], IPAddr[16], i = 0;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) 
		return FALSE;
	if(gethostname(LocalName, 256) == SOCKET_ERROR) 
		return FALSE;
	HOSTENT *ptr = gethostbyname(LocalName);
	if(ptr == NULL) return FALSE;
	while(ptr->h_addr_list[i] != NULL)
	{
		memcpy(&addr, ptr->h_addr_list[i], ptr->h_length);
		wsprintfA(IPAddr, "%s", inet_ntoa(addr));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)IPAddr);  // Add LocalIP in ListBox.
		i++;
	}
	WSACleanup();
	return TRUE;
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;
	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);
	GetObjectA(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void SetBitmap()
{
	send_packet[0] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_DEFAULT));
	send_packet[1] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_1));
	send_packet[2] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_2));
	send_packet[3] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_3));
	send_packet[4] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_4));
	send_packet[5] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_5));
	send_packet[6] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_6));
	send_packet[7] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_7));
	send_packet[8] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_SEND_8));
	request[0][0] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ1));
	request[0][1] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ2));
	request[0][2] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ3));
	request[0][3] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ4));
	request[0][4] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ5));
	request[0][5] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM1_REQ6));
	request[1][0] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ1));
	request[1][1] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ2));
	request[1][2] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ3));
	request[1][3] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ4));
	request[1][4] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ5));
	request[1][5] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM2_REQ6));
	request[2][0] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ1));
	request[2][1] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ2));
	request[2][2] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ3));
	request[2][3] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ4));
	request[2][4] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ5));
	request[2][5] = LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_COM3_REQ6));
	cach_table= LoadBitmap(g_inst, MAKEINTRESOURCE(IDB_DEFAULT));
}

int __cdecl ARP_send(char * macad, char * send_ip, int k)
{
	int signal;
	int i, j; 
	HRESULT hr; 
	IPAddr ipAddr; 
	ULONG pulMac[2]; 
	ULONG ulLen; 
	ulLen = 6; 
	char * szMac = new char[ulLen*3]; 
	ipAddr = inet_addr(send_ip);
	memset (pulMac, 0xff, sizeof (pulMac));
	PBYTE pbHexMac = (PBYTE) pulMac; 
	hr = SendARP (ipAddr, 0, pulMac, &ulLen);
	if(hr != NO_ERROR)
	{
		signal=1;
		szMac = "";
		return signal;
	}
	for (i = 0, j = 0; i < (int)ulLen - 1; ++i)
		j += sprintf (szMac + j, "%02X:", pbHexMac[i]);
	sprintf (szMac + j, "%02X", pbHexMac[i]);
	signal = 2;
	strcpy(macad,szMac);
	return signal ;
}
