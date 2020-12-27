#define Margin_First_X 18
#define Margin_Second_X 99
#define Margin_First_Y 5
#define Margin_Second_Y 10
#define Margin_Third_Y 30


typedef struct _person{
    char id[10]; //学号
    char names[10]; //姓名
    int entranceDate; //入学年份
    char  IDCard[20];  //身份证号码
    char sex[3]; //性别
    char major[20]; //专业
    char Grade[10]; //年级
    double math; //数学成绩
    double english; //英语成绩
    double chinese;  //语文成绩
    char pasword[16]; //密码
    struct _person * node;
}Person;

void DrawLineX(int count, int X, int Y, char c);
void DrawLineY(int count, int X, int Y, char c);
void SetConsoleWindowSize(int width, int height);
void SetPosition(int x, int y);
void SetColor(int ForeColor, int BackGroundColor);
void Clear(int X, int Y,int endX,int endY);
void  Password_Input(char * password);
int  Login_Verify();
void SetTitle(char * title);

void Login_Menue();
int GetKey();
void Draw_Login_Menue(int X);
void Person_Login(int status);

void Teacher_Menue();
void Student_Menue();
void Root_Menue();


void Dean_Office_Menue();
void Draw_Dean_Office_Menue(int X);
void Add_user_Menue();
void Draw_Add_user_Menue(int );
void Add_Student_Menue();
void Add_Teacher_Menue();
void Draw_Add_Teacher_Menue(int X);
void Add_Teacher_Menue();
void Draw_Add_Student_Menue(int page);
void Draw_Add_user_Menue(int X);
void Add_Student_Menue();
void Add_A_User(int);
void Add_Many_User(int );

void SHow_User_Menue();
void Draw_SHow_User_Menue(int );
void Draw_Student_Info_Table(int X);
void Show_Student_Info(int);

void Draw_Teacher_Info_Table(int X);
void  Show_Teacher_Info(int page);
void Draw_Teacher_Info_Menue(int X);


void Dean_Info_Query();




void Password_Modify(int );
void Draw_Student_Menue(int X);
void Draw_Root_Dean_Office_Menue(int X);
void Student_Info_Query();
void DrawLogin();
void Student_Score_Query();


void Get_Filename(char *filename, int n);
int Get_Person_Identity(int n);
void Add_Dean_Office_User();
int Judge_User(int);
void Add_Dean_Office_User_Again(Person);
void Search_File(char dir[20]);

void Search_User();
void Delete();
void Recover();
void Change_Menue();
void Draw_Change_Menue(int X);
void Change_Student_Info_Menue();
void Change_Teacher_Info_Menue();
void Draw_Change_Student_Info_Menue(int X,Person);
void Change_Teacher_Info_Menue();
void Draw_Change_Teacher_Info_Menue(int X,Person information);

void Teacher_Info_Query();

char **Creat_FileName_arry(char file_path[30]);
void Person_Login(int status);
void Draw_Teacher_Menue(int X);
void Teacher_Menue();
void Draw_Student_Score_Table(int X);
void Draw_Student_Score_Menue(int X);
void Show_Student_Score_Info(int page);
void Draw_Dean_Office_Info_Menue(int X);
void Show_Dean_Office_Info(int page);
void Draw_Dean_Office_Info_Table(int X);

void Draw_Root_Menue(int X);
void  Init_Person(int id);
void Draw_Student_Info_Menue(int X);
void Change_Dean_Office_Info_Menue();
void Root_Dean_Office_Menue();
