#include <windows.h>
#include <stdio.h>

void SetTitle(char * title)
{
    SetConsoleTitle(title);
}

void SetColor(int ForeColor, int BackGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                    //获取当前窗口句柄
    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}

void SetConsoleWindowSize(int width, int height)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置控制台窗口的缓冲区大小
	COORD size = {width, height};
	SetConsoleScreenBufferSize(handle, size);
	//设置控制台窗口大小,最大坐标是缓冲区大小-1
	SMALL_RECT rect = {0, 0, width-1, height-1};
	SetConsoleWindowInfo(handle, 1, &rect);
}
void SetPosition(int x, int y)
{
    COORD cursorPosition;   //光标的坐标
    HANDLE handle;          //当前窗口句柄
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorPosition.X = x;   //设置x、y坐标
    cursorPosition.Y = y;
    SetConsoleCursorPosition(handle, cursorPosition);
}

int GetKey()

{
    HANDLE handle;          //当前窗口句柄
    handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Read;
    INPUT_RECORD Event;
    //得到控制台的输入
    ReadConsoleInput(handle, &Event, 1, &Read);
    //如果输入事件是一个键盘事件，就进行判断，返回按下键的虚拟键码
    if(Event.EventType == KEY_EVENT)
    {
        if(Event.Event.KeyEvent.bKeyDown)//返回值为true，表示有键被按下
        {
             return Event.Event.KeyEvent.wVirtualKeyCode;//返回按下键的虚拟键码
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
}//画竖线函数
void DrawLineX(int count, int X, int Y, char c)
{
    SetPosition(X,Y);
    int i;
    for(i=X; i<count; i++)
    {
        SetPosition(i,Y);
        printf("%c",c);
    }
}//画横线函数
