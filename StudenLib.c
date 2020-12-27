#include <windows.h>
#include <stdio.h>

void SetTitle(char * title)
{
    SetConsoleTitle(title);
}

void SetColor(int ForeColor, int BackGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                    //��ȡ��ǰ���ھ��
    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}

void SetConsoleWindowSize(int width, int height)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ÿ���̨���ڵĻ�������С
	COORD size = {width, height};
	SetConsoleScreenBufferSize(handle, size);
	//���ÿ���̨���ڴ�С,��������ǻ�������С-1
	SMALL_RECT rect = {0, 0, width-1, height-1};
	SetConsoleWindowInfo(handle, 1, &rect);
}
void SetPosition(int x, int y)
{
    COORD cursorPosition;   //��������
    HANDLE handle;          //��ǰ���ھ��
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorPosition.X = x;   //����x��y����
    cursorPosition.Y = y;
    SetConsoleCursorPosition(handle, cursorPosition);
}

int GetKey()

{
    HANDLE handle;          //��ǰ���ھ��
    handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Read;
    INPUT_RECORD Event;
    //�õ�����̨������
    ReadConsoleInput(handle, &Event, 1, &Read);
    //��������¼���һ�������¼����ͽ����жϣ����ذ��¼����������
    if(Event.EventType == KEY_EVENT)
    {
        if(Event.Event.KeyEvent.bKeyDown)//����ֵΪtrue����ʾ�м�������
        {
             return Event.Event.KeyEvent.wVirtualKeyCode;//���ذ��¼����������
        }
    }
    return 0;
}

void Clear(int X, int Y,int endX,int endY)
{

    int i,j;

    for(i=Y;i<endY;i++)
    {
       SetPosition(X,Y);
       for(j=X;j<endX;j++)
       {
           printf(" ");
       }
       Y++;
    }

}

void DrawLineY(int count, int X, int Y, char c)
{
    int i;
    for(i=Y; i<count; i++)
    {
       SetPosition(X,i);
       printf("%c",c);

    }
}//�����ߺ���
void DrawLineX(int count, int X, int Y, char c)
{
    SetPosition(X,Y);
    int i;
    for(i=X; i<count; i++)
    {
        SetPosition(i,Y);
        printf("%c",c);
    }
}//�����ߺ���
