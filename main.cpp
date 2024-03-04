#include<iostream>
#include<string>
#include <time.h>
#include<fstream>//�ļ���������ͷ�ļ�
#define MAX 10000
using namespace std;

struct student{
string id;
string clas;
string name;
char ontime[5];
string pos;//��¼ʹ�û���λ��
};

struct student s[MAX];
int machine[8][8]={0};//1��ʾʹ���У�0��ʾ����

int count(){//�����ļ���������ʾ�м�����
    int n=0;
    ifstream ifs;
    ifs.open("reg.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"�ļ���ʧ�ܣ�"<<endl;
        exit(-1);
    }
    string buf;
    while(getline(ifs,buf))
        n++;
    return n;
}

void show(){//��ʾ����ʹ�����
    int sum=0;
    cout<<"1��ʾ������ʹ��"<<endl;
    cout<<"0��ʾ�������У����û���ѡ"<<endl;
    for(int i=1;i<=7;i++){
        for(int j=1;j<=7;j++){
            if(machine[i][j]==1)
                sum++;
            cout<<machine[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"�������"<<49-sum<<"̨����ʹ�û���"<<sum<<"̨��"<<endl;
}

void read(){
    int i=0;
    ifstream ifs;
    ifs.open("reg.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"�ļ���ʧ�ܣ�"<<endl;
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
        cout<<"�������û�id��";
        cin>>a;
        cout<<"������༶��";
        cin>>b;
        cout<<"������������";
        cin>>c;
        cout<<"�������ϻ�ʱ�䣺";
        cin>>d;
        cout<<"������ѡ�������λ�ã���(x,y)��";
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
        cout<<"��¼����Ϣ��"<<endl;
        //cout<<str<<endl;
    }
    else
        cout<<"û�п��л�������ȴ������û��뿪..."<<endl;
    ofs.close();
}

void calculate(){
    int stu,stu1,stu2,sum,x=0;
    char len[5];
    string no;
    cout<<"����������ϻ������û���ѧ�ţ�";
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
        cout<<"���û������ڣ�"<<endl;
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
    cout<<"�û�ѧ�ţ�"<<s[stu].id<<endl;
    cout<<"�û��༶��"<<s[stu].clas<<endl;
    cout<<"�û�������"<<s[stu].name<<endl;
    cout<<"�ϻ�ʱ�䣺"<<s[stu].ontime<<endl;
    cout<<"�»�ʱ�䣺";
    for(int j=0;j<5;j++)
        cout<<t2[j];
    cout<<endl;
    cout<<"ʹ��ʱ�䣺";
    for(int i=0;i<2;i++){
        cout<<(int)len[i];
    }
    cout<<len[2];
    for(int i=3;i<5;i++){
        cout<<(int)len[i];
    }
    cout<<endl;
    cout<<"�ϻ����ã�"<<sum<<endl;
    machine[s[stu].pos[1]][s[stu].pos[3]]=0;
    cout<<"λ��("<<s[stu].pos[1]<<","<<s[stu].pos[3]<<")�Ļ����ѽ���ʹ�ã��ټ���"<<endl;

}

void selectmenu(){
    cout<<"��ѡ���ѯ���ݣ�"<<endl;
    cout<<"1.��ѯ�û��ϻ�ʱ��    "<<"2.��ѯ����ʹ�����    "<<endl;
}

void condition(){
    cout<<"��ѡ���ѯ������"<<endl;
    cout<<"1.ѧ��   "<<"2.�༶   "<<"3.����   "<<endl;
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
                    cout<<"������Ҫ��ѯ��ѧ�ţ�";
                    cin>>sel_id;
                    cout<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].id==sel_id){
                            x1++;
                            cout<<"�û�ѧ�ţ�"<<s[i].id<<"       �û��༶��"<<s[i].clas<<endl;
                            cout<<"�û�������"<<s[i].name<<"       �û��ϻ�ʱ�䣺";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                        }
                    }
                    if(x1==0)
                        cout<<"���û������ڣ�"<<endl;
                    goto A;
                case 2:
                    cout<<"������Ҫ��ѯ�İ༶";
                    cin>>sel_clas;
                    cout<<endl<<"�༶Ϊ"<<sel_clas<<"���û���Ϣ��"<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].clas==sel_clas){
                            x2++;
                            cout<<"�û�ѧ�ţ�"<<s[i].id<<"       �û��༶��"<<s[i].clas<<endl;
                            cout<<"�û�������"<<s[i].name<<"       �û��ϻ�ʱ�䣺";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                        }
                    }
                    if(x2==0)
                        cout<<"���û������ڣ�"<<endl;
                    cout<<"��ѯ������"<<endl;
                    goto A;
                case 3:
                    cout<<"������Ҫ��ѯ���û�����";
                    cin>>sel_name;
                    cout<<endl;
                    for(int i=0;i<49;i++){
                        if(s[i].name==sel_name){
                            x3++;
                            cout<<"�û�ѧ�ţ�"<<s[i].id<<"       �û��༶��"<<s[i].clas<<endl;
                            cout<<"�û�������"<<s[i].name<<"       �û��ϻ�ʱ�䣺";
                            for(int j=0;j<5;j++)
                                cout<<s[i].ontime[j];
                            cout<<endl;
                            break;
                        }
                    }
                    if(x3==0)
                        cout<<"���û������ڣ�"<<endl;
                    goto A;
            }
            A:cout<<"\n1.����\n0.������һ��"<<endl;
            cin>>in;
            }while(in);
            goto B;
        case 2:
            cout<<"����ʹ�������"<<endl;
            for(int i=1;i<=7;i++){
                    for(int j=1;j<=7;j++){
                        if(machine[i][j]==0)
                            cout<<"����  ";
                        else
                            cout<<"ʹ��  ";
                    }
                    cout<<endl;
            }
            goto B;
    }
    B:cout<<"\n1.����ѡ���ѯ����\n0.�������˵�"<<endl;
    cin>>in2;
    }while(in2);
}

void menu(){
    cout<<"*****************��ӭ��������շѹ���ϵͳ*****************"<<endl;
    cout<<"        1.¼�빦��                  2.���㹦��            "<<endl;
    cout<<"        3.��ѯ����                  4.�˳�ϵͳ            "<<endl;
    cout<<"����������ѡ��";
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
            cout<<"***�����˳�,ллʹ�ñ�ϵͳ���´��ټ���***"<<endl;
            exit(0);
        default:
            break;
    }
    return 0;
}
