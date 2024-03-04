#include<iostream>
#include<string>
#include <time.h>
#include<fstream>//文件流工具类头文件
#define MAX 10000
using namespace std;

struct student{
string id;
string clas;
string name;
char ontime[5];
string pos;//记录使用机器位置
};

struct student s[MAX];
int machine[8][8]={0};//1表示使用中，0表示空闲

int count(){//计算文件行数，表示有几个人
    int n=0;
    ifstream ifs;
    ifs.open("reg.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"文件打开失败！"<<endl;
        exit(-1);
    }
    string buf;
    while(getline(ifs,buf))
        n++;
    return n;
}

void show(){//显示机房使用情况
    int sum=0;
    cout<<"1表示机器被使用"<<endl;
    cout<<"0表示机器空闲，新用户可选"<<endl;
    for(int i=1;i<=7;i++){
        for(int j=1;j<=7;j++){
            if(machine[i][j]==1)
                sum++;
            cout<<machine[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"空余机器"<<49-sum<<"台，已使用机器"<<sum<<"台。"<<endl;
}

void read(){
    int i=0;
    ifstream ifs;
    ifs.open("reg.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"文件打开失败！"<<endl;
        exit(-1);
    }
    string str[49][5];
    int n=count();
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            ifs>>str[i][j];
        }
    }
    for(int i=0;i<n;i++){
        s[i].id=str[i][0];
        s[i].clas=str[i][1];
        s[i].name=str[i][2];
        s[i].pos=str[i][4];
        machine[s[i].pos[1]-48][s[i].pos[3]-48]=1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<5;j++){
            s[i].ontime[j]=str[i][3][j];
        }
    }
    /*for(int j=0;j<n;j++){
        cout<<s[j].id<<","<<s[j].clas<<","<<s[j].name<<",";
        for(int k=0;k<5;k++)
            cout<<s[j].ontime[k];
        cout<<","<<s[j].pos<<endl;
    }*/
    //show();
    ifs.close();
}

void add(){
    read();
    show();
    ofstream ofs;
    string a,b,c,d,e;
    int p=count();
    if(p<49){
        ofs.open("reg.txt",ios::out|ios::app);
        cout<<"请输入用户id：";
        cin>>a;
        cout<<"请输入班级：";
        cin>>b;
        cout<<"请输入姓名：";
        cin>>c;
        cout<<"请输入上机时间：";
        cin>>d;
        cout<<"请输入选择机器的位置，例(x,y)：";
        cin>>e;
        s[p+1].id=a;
        s[p+1].clas=b;
        s[p+1].name=c;
        s[p+1].pos=e;
        machine[e[1]-48][e[3]-48]=1;
        int i=0;
        do{
            s[p+1].ontime[i]=d[i];
            i++;
        }while(i<sizeof(d));
        string str;
        str=a+" "+b+" "+c+" "+d+" "+e;
        ofs<<'\n';
        ofs<<str;
        cout<<"已录入信息！"<<endl;
        //cout<<str<<endl;
    }
    else
        cout<<"没有空闲机器，请等待其他用户离开..."<<endl;
    ofs.close();
}

void calculate(){
    int stu,stu1,stu2,sum,x=0;
    char len[5];
    string no;
    cout<<"请输入计算上机费用用户的学号：";
    cin>>no;
    for(int i=0;i<49;i++){
        if(s[i].id==no){
            stu=i;
            stu1=s[i].pos[1];
            stu2=s[i].pos[3];
            x++;
        }
    }
    if(x==0){
        cout<<"该用户不存在！"<<endl;
        exit(-1);
    }
    machine[stu1][stu2]=0;
    time_t timer=time(NULL);
    char *t;
    char t2[5];
    t=asctime(localtime(&timer));
    int i=0;
    for(int j=11;j<16;j++){
        t2[i++]=t[j];
    }
    if(t[11]<s[stu].ontime[0]){
        perror("Error time!");
    }
    if(t[15]>=s[stu].ontime[4]){
        len[4]=t[15]-s[stu].ontime[4];
    }
    else{
        t[14]=t[14]-1;
        len[4]=10-s[stu].ontime[4]+t[15];
    }
    if(t[14]>=s[stu].ontime[3]){
        len[3]=t[14]-s[stu].ontime[3];
    }
    else{
        t[12]=t2[12]-1;
        len[3]=6+t2[14]-s[stu].ontime[3];
    }
    len[2]=t[13];
    if(t[12]>=s[stu].ontime[1]){
        len[1]=t[12]-s[stu].ontime[1];
    }
    else{
        t[11]=t[11]-1;
        len[1]=10+t[12]-s[stu].ontime[1];
    }
    len[0]=t[11]-s[stu].ontime[0];
    if((int)len[3]==0&&(int)len[4]==0)
        sum=(int)(len[0])*10+(int)(len[1])*1;
    else
        sum=(int)(len[0])*10+(int)(len[1])*1+1;
    cout<<"用户学号："<<s[stu].id<<endl;
    cout<<"用户班级："<<s[stu].clas<<endl;
    cout<<"用户姓名："<<s[stu].name<<endl;
    cout<<"上机时间："<<s[stu].ontime<<endl;
    cout<<"下机时间：";
    for(int j=0;j<5;j++)
        cout<<t2[j];
    cout<<endl;
    cout<<"使用时间：";
    for(int i=0;i<2;i++){
        cout<<(int)len[i];
    }
    cout<<len[2];
    for(int i=3;i<5;i++){
        cout<<(int)len[i];
    }
    cout<<endl;
    cout<<"上机费用："<<sum<<endl;
    machine[s[stu].pos[1]][s[stu].pos[3]]=0;
    cout<<"位于("<<s[stu].pos[1]<<","<<s[stu].pos[3]<<")的机器已结束使用，再见！"<<endl;

}

void selectmenu(){
    cout<<"请选择查询内容："<<endl;
    cout<<"1.查询用户上机时间    "<<"2.查询机器使用情况    "<<endl;
}

void condition(){
    cout<<"请选择查询条件："<<endl;
    cout<<"1.学号   "<<"2.班级   "<<"3.姓名   "<<endl;
}

void select(){

    int exp1,exp2;
    string sel_id;
    string sel_clas;
    string sel_name;
    int x1=0,x2=0,x3=0;
    int in,in2;
    do{
    selectmenu();
    cin>>exp1;
    switch(exp1){
        case 1:
            do{
            condition();
            cin>>exp2;
            switch(exp2){
                case 1:
                    cout<<"请输入要查询的学号：";
                    cin>>sel_id;
                    cout<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].id==sel_id){
                            x1++;
                            cout<<"用户学号："<<s[i].id<<"       用户班级："<<s[i].clas<<endl;
                            cout<<"用户姓名："<<s[i].name<<"       用户上机时间：";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                        }
                    }
                    if(x1==0)
                        cout<<"该用户不存在！"<<endl;
                    goto A;
                case 2:
                    cout<<"请输入要查询的班级";
                    cin>>sel_clas;
                    cout<<endl<<"班级为"<<sel_clas<<"的用户信息："<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].clas==sel_clas){
                            x2++;
                            cout<<"用户学号："<<s[i].id<<"       用户班级："<<s[i].clas<<endl;
                            cout<<"用户姓名："<<s[i].name<<"       用户上机时间：";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                        }
                    }
                    if(x2==0)
                        cout<<"该用户不存在！"<<endl;
                    cout<<"查询结束！"<<endl;
                    goto A;
                case 3:
                    cout<<"请输入要查询的用户姓名";
                    cin>>sel_name;
                    cout<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].name==sel_name){
                            x3++;
                            cout<<"用户学号："<<s[i].id<<"       用户班级："<<s[i].clas<<endl;
                            cout<<"用户姓名："<<s[i].name<<"       用户上机时间：";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                            break;
                        }
                    }
                    if(x3==0)
                        cout<<"该用户不存在！"<<endl;
                    goto A;
            }
            A:cout<<"\n1.继续\n0.返回上一层"<<endl;
            cin>>in;
            }while(in);
            goto B;
        case 2:
            cout<<"机器使用情况："<<endl;
            for(int i=1;i<=7;i++){
                    for(int j=1;j<=7;j++){
                        if(machine[i][j]==0)
                            cout<<"空闲  ";
                        else
                            cout<<"使用  ";
                    }
                    cout<<endl;
            }
            goto B;
    }
    B:cout<<"\n1.继续选择查询内容\n0.返回主菜单"<<endl;
    cin>>in2;
    }while(in2);
}

void menu(){
    cout<<"*****************欢迎进入机房收费管理系统*****************"<<endl;
    cout<<"        1.录入功能                  2.计算功能            "<<endl;
    cout<<"        3.查询功能                  4.退出系统            "<<endl;
    cout<<"请输入您的选择：";
}

int main()
{
    int fun;
    read();
    C:menu();
    cin>>fun;
    switch(fun){
        case 1:
            add();
            goto C;
        case 2:
            calculate();
            goto C;
        case 3:
            select();
            goto C;
        case 4:
            cout<<"***正在退出,谢谢使用本系统，下次再见！***"<<endl;
            exit(0);
        default:
            break;
    }
    return 0;
}
