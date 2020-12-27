#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <io.h>
#include <errno.h>
#include <math.h>

char tempuser[15];
char temppassword[16];
int count = 0;
Person curr_person;
char identity[4][10] = {"ROOT","学生","教师","教务处"};
int page = 1;
int user_count;

void Login_Menue()
{
    int X = 0,key;
    do{
        Draw_Login_Menue(X);
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 3 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    Person_Login(X);
}
void Draw_Login_Menue(int X)
{
     SetColor(10, 0);
    char menue[4][11] = {"root登录","学生登录","教师登录","教务处登录"};
    int i;
    //system("cls");
    SetConsoleWindowSize(120, 40);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(50,8);
    printf("欢迎进入学生管理系统");
    SetPosition(50,14);
    int Y = 14;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 3;
            SetPosition(50,Y);
    }

}
void Person_Login(int status)
{
    SetColor(10,0);
    DrawLogin();
    SetPosition(50,8);
    printf("欢迎进入%s登录系统",identity[status]);
    SetPosition(50,11);
    printf("剩余登陆次数:%d",2-count);
    SetPosition(50,14);
    printf("账号：");
    SetPosition(56,14);
    scanf("%s",tempuser);
    SetPosition(50,17);
    printf("密码：");
    SetPosition(56,17);
    Password_Input(temppassword);
    //printf("%s",temppassword);
    if(strcmp(tempuser,"root") == 0)
    {
        Init_Person(0);
    }
    else
    {
        Init_Person(atoi(tempuser));
    }
   if(Login_Verify() == 1)
    {
        if(status == 1)
        {
            Student_Menue();
        }
        else if(status == 2)
        {
            Teacher_Menue();
        }
        else if(status == 0)
        {
            Root_Menue();
        }
        else if(status == 3)
        {
            Dean_Office_Menue();
        }

    }
    else if(count < 2)
    {
        count++;
        Person_Login(status);
    }
    else
    {
        SetColor(4,0);
        SetPosition(45,19);
        printf("超过最大登陆次数，系统将关闭");
        SetPosition(0,32);
        exit(0);
    }
}

void DrawLogin()
{
    system("cls");
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
}
void  Password_Input(char * password)
{
    char ch;
    int i=0;
    while(1)
    {
           ch=getch();
           if(ch=='\r')//当读到回车符时输入结束
            {
		        break;
            }
            if(ch == '\b')
           {
               printf("%c %c",ch,ch);
               i--;
           }
           else
           {
               *(password+i)=ch;
                i++;
                printf("*");
           }
	}
	*(password+i) ='\0';
	//需要在字符的末尾补加字符串结束标志，才可以以字符串形式输出
}
int Login_Verify()
{
            if(strcmp(tempuser,curr_person.id) == 0 && strcmp(curr_person.pasword,temppassword) == 0)
            {
                SetPosition(50,19);
                printf("登陆成功");
                Sleep(1000);
                return 1;
            }
            else
            {
                SetPosition(50,19);
                SetColor(4,0);
                printf("登陆失败");
                Sleep(1000);
                return 0;
            }
}
void Root_Menue()
{
    system("cls");
    SetColor(10, 0);
    int X = 0,key;
    do{
        Draw_Root_Menue(X);
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 3 )
            X ++;
        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Recover();
    }
    else if(X == 1)
    {
        Root_Dean_Office_Menue();
    }
    else if(X == 2)
    {
      Password_Modify(0);
    }
    else if(X == 3)
    {
        SetPosition(0,31);
        SetColor(10,0);
        exit(0);
    }
}
void Root_Dean_Office_Menue()
{
    system("cls");
    SetColor(10, 0);
    int X = 0,key;
    do{
        Draw_Root_Dean_Office_Menue(X);
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 4 )
            X ++;
        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Draw_Dean_Office_Info_Menue(X);
    }
    else if(X == 1)
    {
        Add_A_User(0);
    }
    else if(X == 2) //删除
    {
        Delete();

    }
    else if(X == 3) //修改
    {
        Change_Dean_Office_Info_Menue();
    }
    else if(X == 4)
    {
        SetColor(10,0);
        Root_Menue();
    }
}

void Draw_Dean_Office_Info_Menue(int X)
{
    system("cls");
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    int key;
    SetPosition(50,7);
    printf("教务处成员信息如下");
    Show_Dean_Office_Info(page);
    do{
        Draw_Dean_Office_Info_Table(X);
        fflush(stdin);
        key = GetKey();
        if(key == 39 && X < 3 )
            X ++;
        else if(key == 37 && X > 0)
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);

    if(X == 0 && page > 1)
    {
        page--;
        Show_Dean_Office_Info(page);
        Draw_Dean_Office_Info_Menue(X);
    }
    else if(X == 1 && page < ceil(user_count/8.0))
    {
        page ++;
        Show_Dean_Office_Info(page);
        Draw_Dean_Office_Info_Menue(X);
    }
    else if(X == 2)
    {
        Search_User();
    }
    else if(X == 3)
    {

        Root_Dean_Office_Menue();
    }
    else
    {
         Draw_Dean_Office_Info_Menue(X);
    }


    //Show_Table();
    //SetPosition(50,14);
    //int Y = 14,i;


}

void Draw_Dean_Office_Info_Table(int X)
{
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'#');
    DrawLineY(30,99,5,'#');
    DrawLineX(100,18,27,'*');
    DrawLineX(100,18,30,'*');
    int i;
    char navigation[4][11] = {"上一页","下一页","搜索","回到主菜单"};
    SetPosition(23,28);
    int right_X = 23;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",navigation[i]);
            right_X += 20;
            SetPosition(right_X,28);
    }
    SetColor(10, 0);
    for(i=9; i<27; i += 2)
    {
        DrawLineX(100,18,i,'*');
    }
    DrawLineY(27,31,9,'#');
    DrawLineY(27,42,9,'#');
    DrawLineY(27,49,9,'#');
    DrawLineY(27,60,9,'#');
    DrawLineY(27,81,9,'#');
    SetPosition(20,10);
    printf("教务处编号");
    SetPosition(35,10);
    printf("姓名");
    SetPosition(44,10);
    printf("性别");
    SetPosition(51,10);
    printf("入职年份");
    SetPosition(62,10);
    printf("身份证号");
    SetPosition(88,10);
    printf("密码");
}
void Draw_Teacher_Info_Table(int X)
{
    DrawLineX(111,18,5,'*');
    DrawLineY(30,18,5,'#');
    DrawLineY(30,110,5,'#');
    DrawLineX(111,18,27,'*');
    DrawLineX(111,18,30,'*');
    int i;
    char navigation[4][11] = {"上一页","下一页","搜索","回到主菜单"};
    SetPosition(23,28);
    int right_X = 23;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",navigation[i]);
            right_X += 23;
            SetPosition(right_X,28);
    }
    SetColor(10, 0);
    for(i=9; i<27; i += 2)
    {
        DrawLineX(110,18,i,'*');
    }
    DrawLineY(27,31,9,'#');
    DrawLineY(27,42,9,'#');
    DrawLineY(27,49,9,'#');
    DrawLineY(27,60,9,'#');
    DrawLineY(27,80,9,'#');
    DrawLineY(27,90,9,'#');
    DrawLineY(27,100,9,'#');
    SetPosition(20,10);
    printf("教师编号");
    SetPosition(35,10);
    printf("姓名");
    SetPosition(44,10);
    printf("性别");
    SetPosition(51,10);
    printf("入职年份");
    SetPosition(62,10);
    printf("身份证号");
    SetPosition(81,10);
    printf("所授课程");
    SetPosition(93,10);
    printf("年级");
    SetPosition(104,10);
    printf("密码");
}
void Draw_Teacher_Info_Menue(int X)
{
    system("cls");
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    int key;
    Draw_Teacher_Info_Table(X);
    SetPosition(55,7);
    printf("教师信息如下");
    Show_Teacher_Info(page);
    do{
        Draw_Teacher_Info_Table(X);
        fflush(stdin);
        key = GetKey();
        if(key == 39 && X < 3 )
            X ++;
        else if(key == 37 && X > 0)
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);

    if(X == 0 && page > 1)
    {
        page--;
        Show_Teacher_Info(page);
        Draw_Teacher_Menue(X);
    }
    else if(X == 1 && page < ceil(user_count/8.0))
    {
        page ++;
        Show_Teacher_Info(page);
        Draw_Teacher_Menue(X);
    }
    else if(X == 2)
    {
        Search_User();
    }
    else if(X == 3)
    {

        SHow_User_Menue();
    }
    else
    {
         Draw_Dean_Office_Menue(0);
    }

}
void  Show_Teacher_Info(int page)
{
    int i;
    int Y = 12;
    Person person;
    char student_file_path[] = "teacher_user";
    char ** arry_filename = Creat_FileName_arry(student_file_path);
    char temp_filename[10];
    SetPosition(36,28);
    printf("%d/%.0lf",page,ceil(user_count/8.0));
    //printf("%s",curr_person.major);
    for(i=(page-1)*8; i<=page*8-1 && i<user_count && i>=0; i++)
    {
       FILE * fp = fopen(arry_filename[i],"r");
       fscanf(fp,"%s %s %s %d %s %s %s %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,person.pasword);
       SetPosition(22,Y);
       printf("%s",person.id);
       SetPosition(35,Y);
       printf("%s",person.names);
       SetPosition(44,Y);
       printf("%s",person.sex);
       SetPosition(51,Y);
       printf("%d",person.entranceDate);
       SetPosition(62,Y);
       printf("%s",person.IDCard);
       SetPosition(83,Y);
       printf("%s",person.major);
       SetPosition(93,Y);
       printf("%s",person.Grade);
       SetPosition(102,Y);
       printf("%s",person.pasword);
       Y += 2;
       fclose(fp);
    }
}
char **Creat_FileName_arry(char file_path[30])
{
    char temp_filename[15];
    char file_path_name[30];
    strcat(file_path,"\\");
    strcpy(file_path_name,file_path);
    Search_File(file_path);
    //printf("%d",user_count);
    FILE * fp = fopen("userlist.txt","r");
    char ** arry_filename;
    arry_filename = (char **)malloc(user_count * sizeof(char *));
    int i;
    for( i=0; i<user_count; i++)
    {
        arry_filename[i] = (char *)malloc(40);
        strcpy(arry_filename[i],file_path_name);
        fscanf(fp,"%s\t",temp_filename);
        strcat(arry_filename[i],temp_filename);
        //printf("%s",arry_filename[i]);
    }
    fclose(fp);
    return arry_filename;
}
void Show_Dean_Office_Info(int page)
{
    int i;
    int Y = 12;
    Person person;
    char dean_file_path[] = "dean_office_user";
    char ** arry_filename = Creat_FileName_arry(dean_file_path);
    char temp_filename[10];
    SetPosition(33,28);
    printf("%d/%.0lf",page,ceil(user_count/8.0));
   for(i=(page-1)*8; i<=page*8-1 && i<user_count && i>=0; i++)
   {
       FILE * fp = fopen(arry_filename[i],"r");
       fscanf(fp,"%s %s %s %d %s %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.pasword);
       SetPosition(21,Y);
       printf("%s",person.id);
       SetPosition(33,Y);
       printf("%s",person.names);
       SetPosition(45,Y);
       printf("%s",person.sex);
       SetPosition(52,Y);
       printf(" %d",person.entranceDate);
       SetPosition(61,Y);
       printf(" %s",person.IDCard);
       SetPosition(82,Y);
       printf(" %s",person.pasword);
       Y += 2;
       fclose(fp);
   }
}
void  Search_File(char dir[20])
{
    user_count = 0;
    long handle;                                                     //用于查找的句柄
	struct _finddata_t fileinfo;
	strcat(dir,"*.txt");
	//printf("%s",dir);                                    //文件信息的结构体
    FILE * fp;
	fp = fopen("userlist.txt", "w+");
	if (fp==0)
	{
		printf("can't open file\n");
        printf("%s",dir);
		exit(0);
	}
	handle=_findfirst(dir,&fileinfo);
	if(-1==handle)
		   ;
    else
        user_count++;
	fprintf(fp,"%s\t",fileinfo.name); //第一次查找

	while(!_findnext(handle,&fileinfo))                              //循环查找其他符合的文件，直到找不到其他的为止
	{
		fprintf(fp,"%s\t",fileinfo.name);
		user_count++;
	}
	_findclose(handle);
	fclose(fp);
	//printf("%d",user_count);

}
//void  Add_Dean_Office_User()
//{
//
//
//   system("cls");
//     DrawLineX(100,18,5,'*');
//    DrawLineY(30,18,5,'*');
//    DrawLineY(30,99,5,'*');
//    DrawLineX(100,18,10,'*');
//    DrawLineX(100,18,30,'*');
//   Person person;
//   SetPosition(40,13);
//   printf("职工号：");
//   scanf("%d",&person.id);
//   SetPosition(40,15);
//   printf("姓名：");
//   scanf("%s",person.names);
//   SetPosition(40,17);
//   printf("性别：");
//   scanf("%s",person.sex);
//   SetPosition(40,19);
//   printf("入职年份：");
//   scanf("%d",&person.entranceDate);
//   SetPosition(40,21);
//   printf("身份证号：");
//   scanf("%s",person.IDCard);
//   SetPosition(40,23);
//   printf("密码：");
//   Password_Input(person.pasword);
//   SetPosition(40,25);
//   printf("确认密码：");
//   Password_Input(temppassword);
//    //printf("%d",person.id);
//   if( strcmp(person.pasword,temppassword) != 0)
//   {
//       Add_Dean_Office_User_Again(person);
//   }
//   else if (Judge_Dean_Office_User(person))
//   {
//       printf("用户已存在！");
//       Add_Dean_Office_User();
//   }
//   else
//   {
//       printf("添加成功！");
//       Add_To_File(person);
//   }
//    SetPosition(50,28);
//    printf("按空格键返回");
//    fflush(stdin);
//    char key = getch();
//    if(key == 32)
//    {
//        Root_Menue();
//    }
//}
//void Add_Dean_Office_User_Again(Person person)
//{
//   SetPosition(40,13);
//   printf("职工号：%03d",person.id);
//   SetPosition(40,15);
//   printf("姓名：%s",person.names);
//   SetPosition(40,17);
//   printf("性别：%s",person.sex);
//   SetPosition(40,19);
//   printf("入职年份：%d",person.id);
//   SetPosition(40,21);
//   printf("身份证号：%s",person.IDCard);
//   SetPosition(40,23);
//   printf("密码：");
//   SetPosition(40,25);
//   Password_Input(person.pasword);
//   printf("确认密码：");
//   Password_Input(temppassword);
//   if( strcmp(person.pasword,temppassword) != 0)
//   {
//       Add_Dean_Office_User_Again(person);
//   }
//   else if (Judge_Dean_Office_User(person))
//   {
//       printf("用户已存在！");
//       Add_Dean_Office_User();
//   }
//   else
//   {
//       printf("添加成功！");
//       Add_To_File(person);
//   }
//}
int Judge_User(int id)
{
    char filename[50];
    Get_Filename(filename,id);
    FILE * fp = fopen(filename,"r");
    if(fp == NULL) //文件打不开，说明不存在此用户
    {
        return 0;
    }
    else  //否则存在此用户，不能添加
    {
        return 1;
    }
    fclose(fp);
}
void Add_To_File(Person person)
{
    char filename[50];
    Get_Filename(filename,atoi(person.id));
    //printf("%s",filename);
    FILE * fp = fopen(filename,"w");
    //printf("%d",Get_Person_Identity(atoi(person.id)));
    if(Get_Person_Identity(atoi(person.id)) == 1)  //学生
    {
        fprintf(fp,"%s  %s  %s  %d  %s  %s  %s  %.1lf  %.1lf  %.1lf  %s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.major,person.Grade,person.chinese,person.math,person.english,person.pasword);
    }
    else if(Get_Person_Identity(atoi(person.id)) == 2)  //教师
    {
        fprintf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.major,person.Grade,person.pasword);
    }
    else if(Get_Person_Identity(atoi(person.id)) == 3) //教务处
    {
       fprintf(fp,"%s\t%s\t%s\t%d\t%s\t%s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.pasword);
    }
    else if(Get_Person_Identity(atoi(person.id)) == 0) //root
    {
        fprintf(fp,"%s\t%s",tempuser,person.pasword);
    }
    fclose(fp);
}

void Get_Filename(char * filename, int n)
{
    char * filetype = ".txt";
    char  filenum[10];
    itoa(n,filenum,10);
    //printf("%d %s",n,filenum);
    char file_path[50];
    if(n == 0)
    {
        strcpy(file_path,".\\");
        strcpy(filenum,"root");

    }
    else if(n<1000)
    {
        strcpy(file_path,"dean_office_user\\");

    }
    else if(n<100000)
    {
        strcpy(file_path,"teacher_user\\");
    }
    else
    {
        strcpy(file_path,"student_user\\");
    }
    strcat(file_path,filenum);
    strcat(file_path,filetype);
    strcpy(filename,file_path);
    //printf("%s",filename);
}
int Get_Person_Identity(int n)
{
    if(n == 0)
    {
       return 0;
    }
    else if(n < 1000)
    {
        return 3;
    }
    else if(n < 100000)
    {
        return 2;
    }
    else
    {
        return 1;
    }

}
void Draw_Root_Dean_Office_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    char root_Dean_Office_Menue[5][20] = {"教务处成员查看","教务处成员添加","教务处成员删除","教务处成员信息修改","回到主菜单"};
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<5; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",root_Dean_Office_Menue[i]);
            Y += 3;
            SetPosition(50,Y);
    }
    SetColor(10, 0);
}
void Dean_Office_Menue()
{
    system("cls");
    SetColor(10, 0);
    int X = 0,key;

    do{
        Draw_Dean_Office_Menue(X);
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 6 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Add_user_Menue();
    }
    else if(X == 1)
    {
        SHow_User_Menue();
    }
    else if(X == 2)
    {
        Change_Menue();
    }
    else if(X == 3)
    {
        Delete();

    }
    else if(X == 4)
    {
        Dean_Info_Query();
    }
    else if(X == 5)
    {
        Password_Modify(3);
    }
    else if(X == 6)
    {
        SetPosition(1,35);
        SetColor(10,0);
        exit(0);
    }
}


void SHow_User_Menue()
{
      SetColor(10,0);
      SetConsoleWindowSize(120, 40);
      system("cls");
      int X = 0,key;
    do{
        Draw_SHow_User_Menue(X);

        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 2 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Draw_Student_Info_Menue(X);
    }
    else if(X == 1)
    {
        Draw_Teacher_Info_Menue(X);
    }
    else if(X == 2)
    {

        Dean_Office_Menue();
    }
}
void Draw_SHow_User_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    char menue[3][20] = {"学生信息查看","教师信息查看","回到主菜单"};
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<3; i++)
    {
        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 5;
            SetPosition(50,Y);
    }
    SetColor(10, 0);
}
void Draw_Student_Info_Menue(int X)
{
    system("cls");
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    int key;
    Draw_Student_Info_Table(X);
    SetPosition(65,7);
    printf("学生成绩信息如下");
    Show_Student_Info(page);
    do{
        Draw_Student_Info_Table(X);
        fflush(stdin);
        key = GetKey();
        if(key == 39 && X < 3 )
            X ++;
        else if(key == 37 && X > 0)
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);

    if(X == 0 && page > 1)
    {
        page--;
        Show_Student_Info(page);
        Draw_Student_Info_Menue(X);
    }
    else if(X == 1 && page < ceil(user_count/8.0))
    {
        page ++;
        Show_Student_Info(page);
        Draw_Student_Info_Menue(X);
    }
    else if(X == 2)
    {
       Search_User();
    }
    else if(X == 3)
    {

        SHow_User_Menue();
    }
    else
    {
         Draw_Student_Info_Menue(X);
    }
}
void Draw_Student_Info_Table(int X)
{
    SetConsoleWindowSize(150,50);
    char navigation[4][11] = {"上一页","下一页","搜索","回到主菜单"};
    SetPosition(23,28);
    int right_X = 23;
    int i;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",navigation[i]);
            right_X += 30;
            SetPosition(right_X,28);
    }
    SetColor(10, 0);
    DrawLineX(132,18,5,'*');
    DrawLineY(30,18,5,'#');
    DrawLineY(30,131,5,'#');
    DrawLineX(132,18,27,'*');
    DrawLineX(132,18,30,'*');
    SetPosition(23,28);
    for(i=9; i<27; i += 2)
    {
        DrawLineX(132,18,i,'*');
    }
    DrawLineY(27,31,9,'#');
    DrawLineY(27,42,9,'#');
    DrawLineY(27,49,9,'#');
    DrawLineY(27,60,9,'#');
    DrawLineY(27,81,9,'#');

    DrawLineY(27,91,9,'#');
    DrawLineY(27,101,9,'#');
    DrawLineY(27,111,9,'#');
    DrawLineY(27,121,9,'#');
    DrawLineY(27,131,9,'#');

    SetPosition(20,10);
    printf("学号");
    SetPosition(35,10);
    printf("姓名");
    SetPosition(44,10);
    printf("性别");
    SetPosition(51,10);
    printf("入学年份");
    SetPosition(62,10);
    printf("身份证号");
    SetPosition(85,10);
    printf("年级");
    SetPosition(115,10);
    printf("语文");
    SetPosition(95,10);
    printf("专业");
    SetPosition(105,10);
    printf("数学");
    SetPosition(125,10);
    printf("英语");

}
void Show_Student_Info(int page)
{

    int i;
    int Y = 12;
    Person person;
    char student_file_path[] = "student_user";
    char ** arry_filename = Creat_FileName_arry(student_file_path);
    char temp_filename[10];
    SetPosition(39,28);
    printf("%d/%.0lf",page,ceil(user_count/8.0));
    //printf("%s",curr_person.major);
    for(i=(page-1)*8; i<=page*8-1 && i<user_count && i>=0; i++)
    {
       FILE * fp = fopen(arry_filename[i],"r");
       fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,&person.chinese,&person.math,&person.english,person.pasword);
       SetPosition(20,Y);
       printf("%s",person.id);
       SetPosition(33,Y);
       printf("%s",person.names);
       SetPosition(45,Y);
       printf("%s",person.sex);
       SetPosition(52,Y);
       printf("%d",person.entranceDate);
       SetPosition(62,Y);
       printf("%s",person.IDCard);
       SetPosition(85,Y);
       printf("%s",person.Grade);
       SetPosition(95,Y);
       printf("%s",person.major);
       SetPosition(104,Y);
       printf("%.1lf",person.math);
       SetPosition(114,Y);
       printf("%.1lf",person.chinese);
       SetPosition(124,Y);
       printf("%.1lf",person.english);
       Y += 2;
       fclose(fp);
    }
}

void Draw_Dean_Office_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    DrawLineX(100,18,5,'*');
    DrawLineY(35,18,5,'*');
    DrawLineY(35,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,35,'*');
    SetPosition(45,8);
    printf("欢迎进入《教务处--%s》管理系统",curr_person.names);
    SetPosition(50,14);
    int Y = 14,i;
    char dean_Main_Menue[7][15] = {"成员添加","成员信息查看","成员信息修改","成员删除","个人资料查看","密码修改","退出登录"};
    for(i=0; i<7; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
        printf("%s",dean_Main_Menue[i]);
        Y += 3;
        SetPosition(50,Y);
    }
}
void Add_user_Menue()
{

      SetColor(10,0);
      SetConsoleWindowSize(120, 40);
      system("cls");
      int X = 0,key;
    do{
        Draw_Add_user_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 2 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Add_Student_Menue();
    }
    else if(X == 1)
    {
        Add_Teacher_Menue();
    }
    else if(X == 2)
    {

        Dean_Office_Menue();
    }

}
void Add_Student_Menue()
{
    SetColor(10,0);
    system("cls");
    int X = 0,key;
    do{
        Draw_Add_Student_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 2 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Add_A_User(1);
    }
    else if(X == 1)
    {
        Add_Many_User(1);
    }
    else if(X == 2)
    {
        Add_user_Menue();
    }
}
void Draw_Add_user_Menue(int X)
{
    //system("cls");
    //Clear(19,11,90,34);
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    char menue[3][20] = {"学生成员添加","教师成员添加","回到主菜单"};
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<3; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 5;
            SetPosition(50,Y);
    }
    SetColor(10, 0);
}

void Draw_Add_Student_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    char menue[3][20] = {"手动添加","导入文件批量添加","回到上一级菜单"};
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    int Y = 14,i;
    SetPosition(50,14);
    for(i=0; i<3; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 5;
            SetPosition(50,Y);
    }
}

void Add_Teacher_Menue()
{
    SetColor(10,0);
    system("cls");
    int X = 0,key;
    do{
        Draw_Add_Student_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 2 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Add_A_User(2);
    }
    else if(X == 1)
    {
        Add_Many_User(2);
    }
    else if(X == 2)
    {
        Add_user_Menue();
    }
}

void Draw_Add_Teacher_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    char menue[3][20] = {"手动添加","导入文件批量添加","回到上一级菜单"};
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<3; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 5;
            SetPosition(50,Y);
    }
}
void Add_Many_User(int status)
{
    SetColor(10,0);
    system("cls");
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    Person person;
    SetPosition(40,16);
    printf("请输入文件完整名称: ");
    char filename[30];
    scanf("%s",filename);
    FILE * fp = fopen(filename,"r");
    if(status == 1)
    {
        while (!feof(fp))
        {
        fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,&person.math,&person.english,&person.chinese,person.pasword);
        //printf("%s %s %s %d %s %s %s %lf %lf %lf %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,&person.math,&person.english,&person.chinese,person.pasword);
        Add_To_File(person);
        }
        SetPosition(40,17);
        printf("添加成功！");
        Sleep(1500);
        Dean_Office_Menue();
    }
    else if(status == 2)
    {
         while (!feof(fp))
         {
          fscanf(fp,"%s %s %s %d %s %s %s %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,person.pasword);
          //printf("11111111");
          Add_To_File(person);
         }
         SetPosition(40,17);
         printf("添加成功！");
          Sleep(1500);
        Dean_Office_Menue();
    }
    else if(fp == NULL)
    {
        SetPosition(40,17);
        printf("文件不存在！");
    }
     getchar();
}
void Add_A_User(int status)
{
    SetColor(10,0);
    system("cls");
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    Person person;
    if(status == 1)
    {
        SetPosition(35,13);
        printf("姓名：");
        scanf("%s",person.names);
        SetPosition(65,13);
        printf("学号：");
        scanf("%s",person.id);
        SetPosition(35,16);
        printf("入学年份：");
        scanf("%d",&person.entranceDate);
        SetPosition(65,16);
        printf("性别：");
        scanf("%s",person.sex);
        SetPosition(35,19);
        printf("身份证号：");
        scanf("%s",person.IDCard);
        SetPosition(65,19);
        printf("专业：");
        scanf("%s",person.major);
        SetPosition(35,22);
        printf("年级：");
        scanf("%s",person.Grade);
        SetPosition(65,22);
        printf("语文成绩：");
        scanf("%lf",&person.chinese);
        SetPosition(35,25);
        printf("数学成绩：");
        scanf("%lf",&person.math);
        SetPosition(65,25);
        printf("英语成绩：");
        scanf("%lf",&person.english);
        SetPosition(35,28);
        printf("账户密码：");
        scanf("%s",person.pasword);

     }
     else if(status == 2 )
     {
        SetPosition(40,13);
        printf("姓名：");
        scanf("%s",person.names);
        SetPosition(40,15);
        printf("教职工号：");
        scanf("%s",person.id);
        SetPosition(40,17);
        printf("入职年份：");
        scanf("%d",&person.entranceDate);
        SetPosition(40,19);
        printf("性别：");
        scanf("%s",person.sex);
        SetPosition(40,21);
        printf("身份证号：");
        scanf("%s",person.IDCard);
        SetPosition(40,23);
        printf("所授课程：");
        scanf("%s",person.major);
        SetPosition(40,25);
        printf("年级：");
        scanf("%s",person.Grade);
        SetPosition(40,27);
        printf("账户密码：");
        scanf("%s",person.pasword);
     }
     else if(status == 0)
     {
        SetPosition(40,13);
        printf("姓名：");
        scanf("%s",person.names);
        SetPosition(40,15);
        printf("教职工号：");
        scanf("%s",person.id);
        SetPosition(40,17);
        printf("入职年份：");
        scanf("%d",&person.entranceDate);
        SetPosition(40,19);
        printf("性别：");
        scanf("%s",person.sex);
        SetPosition(40,21);
        printf("身份证号：");
        scanf("%s",person.IDCard);
        SetPosition(40,23);
        printf("账户密码：");
        scanf("%s",person.pasword);
        if(Judge_User(atoi(person.id)) == 1)
        {
            SetPosition(40,29);
            printf("添加失败，已存在此成员！");
        }
        else
        {
            Add_To_File(person);
            SetPosition(40,29);
            printf("添加成功！");
        }
        SetPosition(50,29);
        printf("按回车键返回主菜单，按空格继续添加");
        int key = GetKey();
        if(key == 32)
            Add_A_User(status);
        else
            Root_Dean_Office_Menue();
    }
    if(Judge_User(atoi(person.id)) == 1)
    {
        SetPosition(40,29);
        printf("添加失败，已存在此成员！");
    }
    else
    {
        Add_To_File(person);
        SetPosition(40,29);
        printf("添加成功！");
    }
    SetPosition(50,29);
    printf("按回车键返回主菜单，按空格继续添加");
    int key = GetKey();
    if(key == 32)
        Add_A_User(status);
    else
        Dean_Office_Menue();
}















void Student_Menue()
{
    SetColor(10,0);
    system("cls");
    int X = 0,key;
    do{
        Draw_Student_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 3 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Student_Score_Query();
    }
    else if(X == 1)
    {
        Student_Info_Query();
    }
    else if(X == 2)
    {
      Password_Modify(1);
    }
    else if(X == 3)
    {
        SetPosition(1,35);
        SetColor(10,0);
        exit(0);
    }
}
void Teacher_Menue()
{
    SetColor(10,0);
    system("cls");
    int X = 0,key;
    do{
        Draw_Teacher_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 3 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Draw_Student_Score_Menue(X);
    }
    else if(X == 1)
    {
        Teacher_Info_Query();
    }
    else if(X == 2)
    {
        Password_Modify(2);
    }
    else if(X == 3)
    {
        SetPosition(1,35);
        SetColor(10,0);
        exit(0);
    }
}
void Show_Student_Score_Info(int page)
{
    int i;
    int Y = 12;
    Person person;
    char student_file_path[] = "student_user";

    char ** arry_filename = Creat_FileName_arry(student_file_path);
    char temp_filename[10];
    SetPosition(33,28);
    printf("%d/%.0lf",page,ceil(user_count/8.0));
    //printf("%s",curr_person.major);
    for(i=(page-1)*8; i<=page*8-1 && i<user_count && i>=0; i++)
    {
       FILE * fp = fopen(arry_filename[i],"r");
       fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",person.id,person.names,person.sex,&person.entranceDate,person.IDCard,person.major,person.Grade,&person.chinese,&person.math,&person.english,person.pasword);
       SetPosition(22,Y);
       printf("%s",person.id);
       SetPosition(39,Y);
       printf("%s",person.names);
       SetPosition(52,Y);
       printf("%s",person.sex);
       SetPosition(59,Y);
       printf("%s",person.Grade);
       if(strcmp(curr_person.major,"高数") == 0)
       {
            SetPosition(70,Y);
            printf("%s","高数");
            SetPosition(86,Y);
            printf("%.1lf",person.math);
       }
        if(strcmp(curr_person.major,"语文") == 0)
       {
            SetPosition(70,Y);
            printf("%s","语文");
            SetPosition(86,Y);
            printf("%.1lf",person.chinese);
       }
        if(strcmp(curr_person.major,"英语") == 0)
       {
            SetPosition(70,Y);
            printf("%s","英语");
            SetPosition(86,Y);
            printf("%.1lf",person.english);
       }
       Y += 2;
       fclose(fp);
    }
}
void Draw_Student_Score_Menue(int X)
{
    system("cls");
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    int key;
    Draw_Student_Score_Table(X);
    SetPosition(50,7);
    printf("学生信息如下");
    Show_Student_Score_Info(page);
    do{
        Draw_Student_Score_Table(X);
        fflush(stdin);
        key = GetKey();
        if(key == 39 && X < 3 )
            X ++;
        else if(key == 37 && X > 0)
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);

    if(X == 0 && page > 1)
    {
        page--;
        Show_Student_Score_Info(page);
        Draw_Student_Score_Menue(X);
    }
    else if(X == 1 && page < ceil(user_count/8.0))
    {
        page ++;
        Show_Student_Score_Info(page);
        Draw_Student_Score_Menue(X);
    }
    else if(X == 2)
    {
       Search_User();
    }
    else if(X == 3)
    {

        Teacher_Menue();
    }
    else
    {
         Draw_Student_Score_Menue(X);
    }


    //Show_Table();
    //SetPosition(50,14);
    //int Y = 14,i;
}
void Draw_Student_Score_Table(int X)
{
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'#');
    DrawLineY(30,99,5,'#');
    DrawLineX(100,18,27,'*');
    DrawLineX(100,18,30,'*');
    int i;
    char navigation[4][11] = {"上一页","下一页","搜索","回到主菜单"};
    SetPosition(23,28);
    int right_X = 23;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",navigation[i]);
            right_X += 20;
            SetPosition(right_X,28);
    }
    SetColor(10, 0);
    for(i=9; i<27; i += 2)
    {
        DrawLineX(100,18,i,'*');
    }
    DrawLineY(27,33,9,'#');
    DrawLineY(27,48,9,'#');
    DrawLineY(27,57,9,'#');
    DrawLineY(27,65,9,'#');
    DrawLineY(27,78,9,'#');
    SetPosition(24,10);
    printf("学号");
    SetPosition(39,10);
    printf("姓名");
    SetPosition(51,10);
    printf("性别");
    SetPosition(59,10);
    printf("年级");
    SetPosition(70,10);
    printf("课程");
    SetPosition(86,10);
    printf("成绩");
}
void Teacher_Info_Query()
{
    Clear(19,11,90,30);
    SetPosition(40,13);
    printf("姓名：%s",curr_person.names);
    SetPosition(40,15);
    printf("学号：%s",curr_person.id);
    SetPosition(40,19);
    printf("入学年份：%d",curr_person.entranceDate);
    SetPosition(40,17);
    printf("性别：%s",curr_person.sex);
    SetPosition(40,21);
    printf("身份证号：%s",curr_person.IDCard);
    SetPosition(40,23);
    printf("所授课程：%s",curr_person.major);
    SetPosition(40,25);
    printf("年级：%s",curr_person.Grade);
    SetPosition(40,27);
    printf("账户密码：%s",curr_person.pasword);
    SetPosition(50,29);
    printf("按空格键返回");
    fflush(stdin);
    char key = getch();
    if(key == 32)
    {
        Teacher_Menue();
    }
}
void Dean_Info_Query()
{
    Clear(19,11,90,35);
    SetPosition(40,13);
    printf("姓名：%s",curr_person.names);
    SetPosition(40,16);
    printf("学号：%s",curr_person.id);
    SetPosition(40,19);
    printf("入学年份：%d",curr_person.entranceDate);
    SetPosition(40,22);
    printf("性别：%s",curr_person.sex);
    SetPosition(40,25);
    printf("身份证号：%s",curr_person.IDCard);
    SetPosition(40,28);
    printf("账户密码：%s",curr_person.pasword);
    SetPosition(50,30);
    printf("按空格键返回");
    fflush(stdin);
    char key = getch();
    if(key == 32)
    {
        Dean_Office_Menue();
    }
}
void Draw_Teacher_Menue(int X)
{

    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(45,8);
    printf("欢迎进入《教师--%s》管理系统",curr_person.names);
    SetPosition(50,14);
    int Y = 14,i;
    char teacher[4][22] = {"所授课程学生成绩查看","个人资料","登录密码修改","退出登录"};
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",teacher[i]);
            Y += 3;
            SetPosition(50,Y);
    }
}
void Draw_Student_Menue(int X)
{
    SetColor(10,0);
    SetConsoleWindowSize(120, 40);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(45,8);
    printf("欢迎进入《学生--%s》管理系统",curr_person.names);
    SetPosition(50,14);
    int Y = 14,i;
    char student[4][15] = {"个人成绩查看","个人资料","登录密码修改","退出登录"};
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",student[i]);
            Y += 3;
            SetPosition(50,Y);
    }
}
//void Draw_Dean_Office_Menue(int X, Teacher * pNow_Teacher)
//{
//    SetColor(10,0);
//    char dean_Office[6][20] = {"学生成绩模块","学生信息模块","老师信息模块","个人资料","密码修改","退出登录"};
//    SetConsoleWindowSize(120, 40);
//    DrawLineX(100,18,5,'*');
//    DrawLineY(30,18,5,'*');
//    DrawLineY(30,99,5,'*');
//    DrawLineX(100,18,10,'*');
//    DrawLineX(100,18,30,'*');
//    SetPosition(45,8);
//    printf("欢迎进入《教务处--%s》管理系统",pNow_Student->names);
//    SetPosition(50,14);
//    int Y = 14,i;
//    for(i=0; i<6; i++)
//    {
//
//        if(X == i)
//        {
//            SetColor(4, 15);
//        }
//        else
//        {
//            SetColor(10, 0);
//        }
//            printf("%s",dean_Office[i]);
//            Y += 3;
//            SetPosition(50,Y);
//    }
//}
void Draw_Root_Menue(int X)
{
    SetColor(10,0);
    char root_Menue[4][20] = {"信息恢复","教务处模块","密码修改","退出登录"};
    SetConsoleWindowSize(120, 40);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,10,'*');
    DrawLineX(100,18,30,'*');
    SetPosition(45,8);
    printf("欢迎《ROOT》进入管理系统");
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<4; i++)
    {

        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",root_Menue[i]);
            Y += 3;
            SetPosition(50,Y);
    }
}

void  Init_Person(int id)
{
    char filename[30];
    Get_Filename(filename,id);
    FILE * fp = fopen(filename,"r");
    int status = Get_Person_Identity(id);

    if(fp == NULL)
    {
        printf("文件打开失败！");
    }
    else if(status == 0)
    {
        fscanf(fp,"%s %s",curr_person.names,curr_person.pasword);
        strcpy(curr_person.id,curr_person.names);
    }
    else if(status == 1)
    {
        fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",curr_person.id,curr_person.names,curr_person.sex,&curr_person.entranceDate,curr_person.IDCard,curr_person.major,curr_person.Grade,&curr_person.math,&curr_person.english,&curr_person.chinese,curr_person.pasword);
        //printf("初始化：%s %s %s %d %s %s %s %lf %lf %lf %s",curr_person.id,curr_person.names,curr_person.sex,curr_person.entranceDate,curr_person.IDCard,curr_person.major,curr_person.Grade,curr_person.math,curr_person.english,curr_person.chinese,curr_person.pasword);
    }
    else if(status == 2)
    {
        fscanf(fp,"%s %s %s %d %s %s %s %s",curr_person.id,curr_person.names,curr_person.sex,&curr_person.entranceDate,curr_person.IDCard,curr_person.major,curr_person.Grade,curr_person.pasword);
    }
    else if(status == 3)
    {
        fscanf(fp,"%s %s %s %d %s %s",curr_person.id,curr_person.names,curr_person.sex,&curr_person.entranceDate,curr_person.IDCard,curr_person.pasword);
    }
    //printf("%s %s %s %d %s %s",curr_person.id,curr_person.names,curr_person.sex,curr_person.entranceDate,curr_person.IDCard,curr_person.pasword);
}

void Student_Score_Query()
{
    Clear(19,11,90,30);
    SetPosition(40,13);
    printf("姓名：%s",curr_person.names);
    SetPosition(40,15);
    printf("学号：%s",curr_person.id);
    SetPosition(40,17);
    printf("语文分数：%.1lf",curr_person.chinese);
    SetPosition(40,19);
    printf("数学分数：%.1lf",curr_person.math);
    SetPosition(40,21);
    printf("数学分数：%.1lf",curr_person.english);
    SetPosition(50,28);
    printf("按空格键返回");
    fflush(stdin);
    char key = getch();
    if(key == 32)
    {
        Student_Menue();
    }
}
void Student_Info_Query()
{
    Clear(19,11,90,30);
    SetPosition(40,13);
    printf("姓名：%s",curr_person.names);
    SetPosition(40,15);
    printf("学号：%s",curr_person.id);
    SetPosition(40,19);
    printf("入学年份：%d",curr_person.entranceDate);
    SetPosition(40,17);
    printf("性别：%s",curr_person.sex);
    SetPosition(40,21);
    printf("身份证号：%s",curr_person.IDCard);
    SetPosition(40,23);
    printf("专业：%s",curr_person.major);
    SetPosition(40,25);
    printf("年级：%s",curr_person.Grade);
    SetPosition(40,27);
    printf("账户密码：%s",curr_person.pasword);
    SetPosition(50,29);
    printf("按空格键返回");
    fflush(stdin);
    char key = getch();
    if(key == 32)
    {
        Student_Menue();
    }
}
void Password_Modify(int status)
{
    SetColor(10, 0);
    char newpassword_1[16];
    char newpassword_2[16];
    char filename[40];
    Get_Filename(filename,curr_person.id);
    Clear(19,11,90,30);
    SetPosition(40,18);
    printf("原始密码：");
    SetPosition(50,18);
    Password_Input(temppassword);
    SetPosition(40,20);
    printf("新密码：");
    SetPosition(48,20);
    Password_Input(newpassword_1);
    SetPosition(40,22);
    printf("确认新密码：");
    SetPosition(52,22);
    Password_Input(newpassword_2);
    if(strcmp(temppassword,curr_person.pasword)!= 0)
    {
        SetPosition(40,25);
        SetColor(4, 0);
        printf("原始密码输入错误，请重新输入！");
        Sleep(3000);
        Password_Modify(status);
    }
    else if(strcmp(newpassword_1,newpassword_2) != 0)
    {
        SetPosition(40,25);
        SetColor(4, 0);
        printf("更新密码不一致，请重新输入！");
        Sleep(3000);
        Password_Modify(status);
    }
    else
    {
        strcpy(curr_person.pasword,newpassword_1);
        Add_To_File(curr_person);
        SetPosition(40,25);
        printf("修改成功！");
        Sleep(1500);
        if(status == 1)
           Student_Menue();
        else if(status == 2)
            Teacher_Menue();
        else if(status == 3)
            Dean_Office_Menue();
        else if(status == 0)
            Root_Menue();
    }

}

void Delete()  //删除学生信息
{
    system("cls");
    SetColor(10,0);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,30,'*');
    int id;
    SetPosition(42,8);
    printf("请输入您要删除的学生或老师的id:");
    SetPosition(42,9);
    scanf("%d",&id);
    Person information;
	char remove_filename[70],cloud_filename[70];
    char ids[10];
    itoa(id,ids,10);
    int n = Get_Person_Identity(id);
//    if(Get_Person_Identity(atoi(person.id)) == 1)  //学生
//    {
//        fprintf(fp,"%s  %s  %s  %d  %s  %s  %s  %.1lf  %.1lf  %.1lf  %s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.major,person.Grade,person.chinese,person.math,person.english,person.pasword);
//    }
//    else if(Get_Person_Identity(atoi(person.id)) == 2)  //教师
//    {
//        fprintf(fp,"%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.major,person.Grade,person.pasword);
//    }
//    else if(Get_Person_Identity(atoi(person.id)) == 3) //教务处
//    {
//       fprintf(fp,"%s\t%s\t%s\t%d\t%s\t%s",person.id,person.names,person.sex,person.entranceDate,person.IDCard,person.pasword);
//    }
    if(n == 1)
    {
        char student_File_Path[50] = "student_user\\";
        char student_Cloud_File_Path[50] = "student_cloud_user\\";
        strcat(student_File_Path,ids);
        strcat(student_File_Path,".txt");
        strcat(student_Cloud_File_Path,ids);
        strcat(student_Cloud_File_Path,".txt");
        FILE *fp = fopen(student_File_Path,"r+");
        FILE *fp2 = fopen(student_Cloud_File_Path,"w");
        fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,&information.chinese,&information.math,&information.english,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("专业：%s",information.major);
        SetPosition(40,25);
        printf("年级：%s",information.Grade);
        SetPosition(40,27);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("确认删除？");
        fflush(stdin);
        char key = getch();
        if(key == 32)
        {
//            while(!feof(fp))
//            {
//                fputc(fgetc(fp),fp2);
//            }
           //fclose(fp);
           // fclose(fp2);
            //printf("\n%s",student_Cloud_File_Path);
            //Add_To_File(information);

            fprintf(fp2,"%s  %s  %s  %d  %s  %s  %s  %.1lf  %.1lf  %.1lf  %s",information.id,information.names,information.sex,information.entranceDate,information.IDCard,information.major,information.Grade,information.chinese,information.math,information.english,information.pasword);
            fclose(fp);
            fclose(fp2);
        }
            int err = remove(student_File_Path);
            if(err == 0)
                printf("删除成功！");
            else if(err == -1)
                printf("删除失败！");

            Sleep(1500);
            Dean_Office_Menue();


    }
    else if(n == 2)
    {

        char teacher_File_Path[50] = "teacher_user\\";
        char teacher_Cloud_File_Path[50] = "teacher_could_user\\";
        strcat(teacher_File_Path,ids);
        strcat(teacher_File_Path,".txt");
        strcat(teacher_Cloud_File_Path,ids);
        strcat(teacher_Cloud_File_Path,".txt");
        FILE *fp = fopen(teacher_File_Path,"r+");
        FILE *fp2 = fopen(teacher_Cloud_File_Path,"w");
        fscanf(fp,"%s %s %s %d %s %s %s %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("年级：%s",information.Grade);
        SetPosition(40,25);
        printf("所授课程：%s",information.major);
        SetPosition(40,27);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("确认删除？");
        fflush(stdin);
        char key = getch();
        if(key == 32)
        {


            fprintf(fp2,"%s  %s  %s  %d   %s %s  %s  %s",information.id,information.names,information.sex,information.entranceDate,information.IDCard,information.major,information.Grade,information.chinese,information.math,information.english,information.pasword);
            fclose(fp);
            fclose(fp2);
            int err = remove(teacher_File_Path);
            if(err == 0)
                printf("删除成功！");
            else if(err == -1)
                printf("删除失败！");
        }

            Sleep(1500);
            Dean_Office_Menue();


    }
    else if(n == 3)
    {
        char teacher_File_Path[50] = "dean_office_user\\";
        char teacher_Cloud_File_Path[50] = "dean_office_could_user\\";
        strcat(teacher_File_Path,ids);
        strcat(teacher_File_Path,".txt");
        strcat(teacher_Cloud_File_Path,ids);
        strcat(teacher_Cloud_File_Path,".txt");
        FILE *fp = fopen(teacher_File_Path,"r+");
        FILE *fp2 = fopen(teacher_Cloud_File_Path,"w");
        fscanf(fp,"%s %s %s %d %s  %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("确认删除？");
        fflush(stdin);
        char key = getch();
        if(key == 32)
        {

            fprintf(fp2,"%s %s %s %d %s  %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.pasword);
            fclose(fp);
            fclose(fp2);
            int err = remove(teacher_File_Path);
            if(err == 0)
                printf("删除成功！");
            else if(err == -1)
                printf("删除失败！");
        }
            Sleep(1500);
            Root_Dean_Office_Menue();


    }

}

void Search_User()
{
    system("cls");
    SetColor(10,0);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,30,'*');
    int id;
    SetPosition(42,8);
    printf("请输入要查看的id:");
    scanf("%d",&id);
    char ids[10];
    itoa(id,ids,10);
    Person information;
    SetPosition(45,22);
	char remove_filename[70];
    int n = Get_Person_Identity(id);
    if(n == 1)
    {
        char student_File_Path[50] = "student_user\\";
        strcat(student_File_Path,ids);
        strcat(student_File_Path,".txt");
        FILE *fp = fopen(student_File_Path,"r+");
        fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,&information.chinese,&information.math,&information.english,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("专业：%s",information.major);
        SetPosition(40,25);
        printf("年级：%s",information.Grade);
        SetPosition(40,27);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("按任意键返回");
        fflush(stdin);
        char key = getch();
        Dean_Office_Menue();


    }
    else if(n == 2)
    {

        char teacher_File_Path[50] = "teacher_user\\";

        strcat(teacher_File_Path,ids);
        strcat(teacher_File_Path,".txt");
        FILE *fp = fopen(teacher_File_Path,"r+");
        fscanf(fp,"%s %s %s %d %s %s %s %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("年级：%s",information.Grade);
        SetPosition(40,25);
        printf("所授课程：%s",information.major);
        SetPosition(40,27);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("按任意键返回");
        fflush(stdin);
        char key = getch();
        Dean_Office_Menue();


    }
    else if(n == 3)
    {
        char teacher_File_Path[50] = "dean_office_user\\";
        strcat(teacher_File_Path,ids);
        strcat(teacher_File_Path,".txt");
        FILE *fp = fopen(teacher_File_Path,"r+");
        fscanf(fp,"%s %s %s %d %s  %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,&information.chinese,&information.math,&information.english,information.pasword);
        SetPosition(40,13);
        printf("姓名：%s",information.names);
        SetPosition(40,15);
        printf("学号：%s",information.id);
        SetPosition(40,19);
        printf("入学年份：%d",information.entranceDate);
        SetPosition(40,17);
        printf("性别：%s",information.sex);
        SetPosition(40,21);
        printf("身份证号：%s",information.IDCard);
        SetPosition(40,23);
        printf("账户密码：%s",information.pasword);
        SetPosition(50,29);
        printf("按任意键返回");
        fflush(stdin);
        char key = getch();
        Root_Dean_Office_Menue();
    }
}
void Recover() //恢复学生信息
{
    system("cls");
    SetColor(10,0);
    DrawLineX(100,18,5,'*');
    DrawLineY(30,18,5,'*');
    DrawLineY(30,99,5,'*');
    DrawLineX(100,18,30,'*');
    int id;
    SetPosition(42,8);
    printf("请输入您要删除的学生或老师的id：");
    scanf("%d",&id);
	char recover_filename[70],cloud_filename[70];
    char ids[10];
    itoa(id,ids,10);
	int n = Get_Person_Identity(id);
	if(n == 1)
	{
		char student_File_Path[50] = "student_user\\";
        char student_Cloud_File_Path[50] = "student_cloud_user\\";
        strcat(student_File_Path,ids);
        strcat(student_File_Path,".txt");
        strcat(student_Cloud_File_Path,ids);
        strcat(student_Cloud_File_Path,".txt");

        FILE *fp = fopen(student_Cloud_File_Path,"r+");
        FILE *fp2 = fopen(student_File_Path,"w");
        while(!feof(fp))
        {
            fputc(fgetc(fp),fp2);
        }
        fclose(fp);
        fclose(fp2);
		int err = remove(student_Cloud_File_Path);
		if(err == 0)
			printf("恢复成功！");
		else if(err == -1)
			printf("恢复失败！");
	}
	else if(n == 2)
	{
		char teacher_File_Path[50] = "teacher_user\\";
        char teacher_Cloud_File_Path[50] = "teacher_cloud_user\\";
        strcat(teacher_File_Path,ids);
        strcat(teacher_File_Path,".txt");
        strcat(teacher_Cloud_File_Path,ids);
        strcat(teacher_Cloud_File_Path,".txt");

        FILE *fp = fopen(teacher_Cloud_File_Path,"r+");
        FILE *fp2 = fopen(teacher_File_Path,"w");
        while(!feof(fp))
        {
            fputc(fgetc(fp),fp2);
        }
        fclose(fp);
        fclose(fp2);
		int err = remove(teacher_Cloud_File_Path);
		if(err == 0)
			printf("恢复成功！");
		else if(err == -1)
			printf("恢复失败！");
	}
	if(n == 3)
	{
		char dean_office_File_Path[50] = "dean_office_user\\";
        char dean_office_Cloud_File_Path[50] = "dean_office_could_user\\";
        strcat(dean_office_File_Path,ids);
        strcat(dean_office_File_Path,".txt");
        strcat(dean_office_Cloud_File_Path,ids);
        strcat(dean_office_Cloud_File_Path,".txt");

        FILE *fp = fopen(dean_office_Cloud_File_Path,"r+");
        FILE *fp2 = fopen(dean_office_File_Path,"w");
        while(!feof(fp))
        {
            fputc(fgetc(fp),fp2);
        }
        fclose(fp);
        fclose(fp2);
		int err = remove(dean_office_Cloud_File_Path);
		if(err == 0)
			printf("恢复成功！");
		else if(err == -1)
			printf("恢复失败！");
	}
	Root_Menue();

}
void Change_Menue()
{

    int X = 0,key;
    do{
        Draw_Change_Menue(X);
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 2 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
          break;
        }
    }while(1);
    if(X == 0)
    {
        Change_Student_Info_Menue();
    }
    else if(X == 1)
    {
        Change_Teacher_Info_Menue();
    }
    else if(X == 2)
    {

        Dean_Office_Menue();
    }
}



void Draw_Change_Menue(int X)
{
    //system("cls");
    SetColor(10,0);
    Clear(20,15,99,34);
    char menue[3][20] = {"学生信息修改","教师信息修改","回到主菜单"};
    SetPosition(50,14);
    int Y = 14,i;
    for(i=0; i<3; i++)
    {
        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 5;
            SetPosition(50,Y);
    }
    SetColor(10, 0);
}
void Change_Student_Info_Menue()
{
    SetColor(10,0);
    Clear(20,13,99,34);
    SetPosition(43,12);
    int num;
    char filename[30];
    Person information;
    printf("请输入要修改的学号：");
    scanf("%d",&num);
    Get_Filename(filename,num);
    FILE * fp = fopen(filename,"r");


    if(fp == NULL)
    {
        SetPosition(43,15);
        printf("没有此用户：");

    }
    else
    {
         fscanf(fp,"%s %s %s %d %s %s %s %lf %lf %lf %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,&information.chinese,&information.math,&information.english,information.pasword);
    }

    int X = 0,key;
    do{
       Draw_Change_Student_Info_Menue(X,information);
       SetPosition(55,32);
       printf("修改完成后按空格键返回");
        char key;
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 9 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
            SetColor(4,15);
            SetPosition(50,10+(X+1)*2);
            printf("                          ");
            SetPosition(50,10+(X+1)*2);
            if(X == 0)
            {
                scanf("%s",information.names);
            }
            else if(X == 1)
            {

                scanf("%s",information.sex);
            }
            else if(X == 2)
            {
                scanf("%s",information.Grade);

            }
            else if(X == 3)
            {
                scanf("%d",&information.entranceDate);
            }
            else if(X == 4)
            {
                scanf("%s",information.IDCard);

            }
            else if(X == 5)
            {
                scanf("%s",information.major);

            }
            else if(X == 6)
            {
                scanf("%lf",&information.chinese);

            }
            else if(X == 7)
            {
                scanf("%lf",&information.math);

            }
            else if(X == 8)
            {
                scanf("%lf",&information.english);

            }
            else if(X == 9)
            {
                scanf("%s",information.pasword);

            }
        }
        else if(key == 32)
        {
            Add_To_File(information);
            Dean_Office_Menue();
        }
    }while(1);



}
void Draw_Change_Student_Info_Menue(int X,Person information)
{
    SetColor(10,0);
    Clear(20,11,99,34);
    char menue[10][15] = {"姓名：","性别：","年级：","入学年份：","身份证号：","专业：","语文成绩：","数学成绩：","英语成绩：","密码："};
    SetPosition(40,12);
    int Y = 12,i;
    for(i=0; i<10; i++)
    {
        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 2;
            SetPosition(40,Y);
    }
    SetColor(10, 0);
    SetPosition(50,12);
    printf("%s",information.names);
    SetPosition(50,14);
    printf("%s",information.sex);
    SetPosition(50,16);
    printf("%s",information.Grade);
    SetPosition(50,18);
    printf("%d",information.entranceDate);
    SetPosition(50,20);
    printf("%s",information.IDCard);
    SetPosition(50,22);
    printf("%s",information.major);
    SetPosition(50,24);
    printf("%.1lf",information.chinese);
    SetPosition(50,26);
    printf("%.1lf",information.math);
    SetPosition(50,28);
    printf("%.1lf",information.english);
    SetPosition(50,30);
    printf("%s",information.pasword);

    SetColor(10, 0);

}
void Change_Dean_Office_Info_Menue()
{
    SetColor(10,0);
    Clear(20,13,99,34);
    SetPosition(43,12);
    int num;
    char filename[30];
    Person information;
    printf("请输入要修改的学号：");
    scanf("%d",&num);
    Get_Filename(filename,num);
    FILE * fp = fopen(filename,"r");


    if(fp == NULL)
    {
        SetPosition(43,15);
        printf("没有此用户：");

    }
    else
    {
         fscanf(fp,"%s %s %s %d %s %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.pasword);
    }

    int X = 0,key;
    do{
       Draw_Change_Dean_Office_Info_Menue(X,information);
       SetPosition(55,32);
       printf("修改完成后按空格键返回");
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 5 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
            SetColor(4,15);
            SetPosition(50,10+(X+1)*2);
            printf("                        ");
            SetPosition(50,10+(X+1)*2);
            if(X == 0)
            {
                scanf("%s",information.names);
            }
            else if(X == 1)
            {

                scanf("%s",information.sex);
            }
            else if(X == 2)
            {
                scanf("%d",&information.entranceDate);
            }
            else if(X == 3)
            {
                scanf("%s",information.IDCard);

            }
            else if(X == 4)
            {
                scanf("%s",information.pasword);

            }



        }
        else if(key == 32)
        {
            Add_To_File(information);
            Root_Dean_Office_Menue();
        }
    }while(1);



}
void Draw_Change_Dean_Office_Info_Menue(int X,Person information)
{
    SetColor(10,0);
    Clear(20,11,99,29);
    char menue[5][15] = {"姓名：","性别：","入职年份：","身份证号：","密码："};
    SetPosition(40,12);
    int Y = 12,i;
    for(i=0; i<5; i++)
    {
        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 2;
            SetPosition(40,Y);
    }
    SetColor(10, 0);
    SetPosition(50,12);
    printf("%s",information.names);
    SetPosition(50,14);
    printf("%s",information.sex);
    SetPosition(50,16);
    printf("%d",information.entranceDate);
    SetPosition(50,18);
    printf("%s",information.IDCard);
    SetPosition(50,20);
    printf("%s",information.pasword);
    SetColor(10, 0);

}
void Change_Teacher_Info_Menue()
{
    SetColor(10,0);
    Clear(20,13,99,34);
    SetPosition(43,12);
    int num;
    char filename[30];
    Person information;
    printf("请输入要修改的学号：");
    scanf("%d",&num);
    Get_Filename(filename,num);
    FILE * fp = fopen(filename,"r");


    if(fp == NULL)
    {
        SetPosition(43,15);
        printf("没有此用户：");

    }
    else
    {
         fscanf(fp,"%s %s %s %d %s %s %s %s",information.id,information.names,information.sex,&information.entranceDate,information.IDCard,information.major,information.Grade,information.pasword);
    }

    int X = 0,key;
    do{
       Draw_Change_Teacher_Info_Menue(X,information);
       SetPosition(55,32);
       printf("修改完成后按空格键返回");
        fflush(stdin);
        key = GetKey();
        if(key == 40 && X < 6 )
            X ++;

        else if(key == 38 && X > 0 )
        {
            X--;
        }
        else if(key == 13)
        {
            SetColor(4,15);
            SetPosition(50,10+(X+1)*2);
            printf("                                   ");
            SetPosition(50,10+(X+1)*2);
            if(X == 0)
            {
                scanf("%s",information.names);
            }
            else if(X == 1)
            {

                scanf("%s",information.sex);
            }
            else if(X == 2)
            {
                scanf("%s",information.Grade);

            }
            else if(X == 3)
            {
                scanf("%d",&information.entranceDate);
            }
            else if(X == 4)
            {
                scanf("%s",information.IDCard);

            }
            else if(X == 5)
            {
                scanf("%s",information.major);

            }
            else if(X == 6)
            {
                scanf("%lf",&information.chinese);

            }
            else if(X == 7)
            {
                scanf("%lf",&information.math);

            }
            else if(X == 8)
            {
                scanf("%lf",&information.english);

            }
            else if(X == 9)
            {
                scanf("%s",information.pasword);

            }
        }
        else if(key == 32)
        {
            Add_To_File(information);
            Dean_Office_Menue();
        }
    }while(1);

}
void Draw_Change_Teacher_Info_Menue(int X,Person information)
{
    SetColor(10,0);
    Clear(20,11,99,34);
    char menue[7][15] = {"姓名：","性别：","年级：","入学年份：","身份证号：","所授课程：","密码："};
    SetPosition(40,12);
    int Y = 12,i;
    for(i=0; i<7; i++)
    {
        if(X == i)
        {
            SetColor(4, 15);
        }
        else
        {
            SetColor(10, 0);
        }
            printf("%s",menue[i]);
            Y += 2;
            SetPosition(40,Y);
    }
    SetColor(10, 0);
    SetPosition(50,12);
    printf("%s",information.names);
    SetPosition(50,14);
    printf("%s",information.sex);
    SetPosition(50,16);
    printf("%s",information.Grade);
    SetPosition(50,18);
    printf("%d",information.entranceDate);
    SetPosition(50,20);
    printf("%s",information.IDCard);
    SetPosition(50,22);
    printf("%s",information.major);
    SetPosition(50,24);
    printf("%s",information.pasword);

    SetColor(10, 0);
}
