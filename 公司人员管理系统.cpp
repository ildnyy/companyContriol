#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <string.h>
using namespace std; 

//ȫ�����ݣ�����
double ManagerSalary;         //����̶���н
double SalesManagerSalary;      //���۾���̶���н
double SalesManagerPercent;   //���۾�����ɣ�
double SalesPercent;          //������Ա��ɣ�
double WagePerHour;         //������ԱСʱ����
int ID;                     //Ա����ʶ(Ҫ��֤Ψһ)
/***********************Ա����**********************/
class Person  
{
protected:
	int No;  //���
    char Name[20];  //����
    int Duty;       //��λ
    double Earning; //����
    Person *next;
public:
	Person(char ID,char *Name,int Duty)
	{
		this->Duty=Duty;
		strcpy(this->Name,Name);
		this->No=ID;
	}
    virtual void CalcSalary()=0; 
    virtual void Output()=0;
    friend class Company;
};
/************************������*******************/
class Manager:public Person  
{
public:
	Manager(char ID,char *Name,int Duty):Person(ID,Name,Duty){ }
    void CalcSalary(){Earning=ManagerSalary;}
    void Output()
    {
		CalcSalary();
		cout<<No<<"\t"<<Name<<"\t\t����\t\t"<<Earning<<endl;
    }
};
/********************���۾�����********************/
class SalesManager:public Person  
{
private:
    double Amount;
public:
    SalesManager(char ID,char *Name,int Duty):Person(ID,Name,Duty){}
    void SetAmount(double s)
	{
		Amount=s;
	}
    void CalcSalary()
	{
		Earning=SalesManagerSalary+Amount*SalesManagerPercent/100;
	}
    void Output()
	{
		CalcSalary();
		cout<<No<<"\t"<<Name<<"\t\t���۾���\t"<<Earning<<endl;
	}
};
/**************����Ա��***************************/
class Sales:public Person  
{
private:
    double Amount;
public:
    Sales(char ID,char *Name,int Duty,double Amount):Person(ID,Name,Duty)
	{
		this->Amount=Amount;
	}
    double GetAmount()  //���ڼ����������ܶ�sum
	{
		return Amount;
	} 
    void CalcSalary()
	{
		Earning=SalesPercent/100*Amount;
	}
    void Output()
	{
		CalcSalary();
		cout<<No<<"\t"<<Name<<"\t\t����Ա\t\t"<<Earning<<"\t\t"<<Amount<<endl;
	}
};
/***********************����Ա��**********************/
class Technician:public Person  
{
private:
    double t;
public:
    Technician(char ID,char *Name,int Duty,double T):Person(ID,Name,Duty)
	{
		this->t=T;
	}
    double GetT()
	{
		return t;
	}
    void CalcSalary()
	{
		Earning=WagePerHour*t;
	}
    void Output()
	{
		CalcSalary();
		cout<<No<<"\t"<<Name<<"\t\t����Ա\t\t"<<Earning<<"\t\t"<<t<<endl;
	}
};
/**************************��˾��***********************/
class Company  
{
private:
	Person *Worker;  /*Ա����*/ 
public:
    Company()
	{
		Worker=NULL;      
		Load();
	}
    ~Company()
	{
		Person *p;
		p=Worker;
		while(p)
		{
			p=p->next;
			delete Worker;
			Worker=p;
		}
        Worker=0;
	}
    void Add();     //������Ա
    void Delete();  //ɾ����Ա
    void display();//��ʾ���¹��ʺ�������Ϣ
    void Query();   //��ѯ
    void Set();     //������������
    void Save();    //���ݴ���(�����������ݣ���Ա����)
    void Load();    //����װ��(�����������ݣ���Ա����)
};

void Company::Add()
{
    Person *p;  //�½��ָ��
    int Duty;  
    char Name[20];
    double Amount,T;

    cout<<"\n** ����Ա�� **\n";    //����Ա����Ϣ
    ID++;
    cout<<"�����λ(1-����2-���۾���3-����Ա4-����Ա):";  cin>>Duty;
    cout<<"��������:";  cin>>Name;
    if(Duty==3)
	{
		cout<<"�������۶�:";  cin>>Amount;
	}
    else if(Duty==4)
	{
		cout<<"���¹���Сʱ��(0-168):";  
		cin>>T;
	}

    //������Ա�����
    switch(Duty)
	{
		case 1:p=new Manager(ID,Name,Duty); break;
		case 2:p=new SalesManager(ID,Name,Duty);  break;
		case 3:p=new Sales(ID,Name,Duty,Amount);   break;
		case 4:p=new Technician(ID,Name,Duty,T);  break;
	}
	p->next=0;

    //Ա������������
    if(Worker)  //���Ѿ����ڽ��
	{
		Person *p2;
		p2=Worker;
		while(p2->next)  //����β���
		{
			p2=p2->next;
		}
        p2->next=p;  //����
	}
    else  //�������ڽ��(���)
	{
		Worker=p;  //����
	}
}
/**************************ɾ��*************************/
void Company::Delete()  //ɾ����Ա
{
    int No;
    cout<<"\n** ɾ��Ա�� **\n";
    cout<<"ID:";  cin>>No;

    //����Ҫɾ���Ľ��
    Person *p1,*p2;  p1=Worker;
    while(p1)
	{
		if(p1->No==No)
        break;
        else
		{
			p2=p1;
			p1=p1->next;
		}
	}

    //ɾ�����
    if(p1!=NULL)//���ҵ���㣬��ɾ��
	{
		if(p1==Worker)  //��Ҫɾ���Ľ���ǵ�һ�����
		{
			Worker=p1->next;
			delete p1;
		}
        else  //��Ҫɾ���Ľ���Ǻ������
		{
			p2->next=p1->next;
			delete p1;
		}
		cout<<"�ҵ���ɾ��\n";
	}
    else  //δ�ҵ����
		cout<<"δ�ҵ�!\n";
}

/********************��ʾ**************************/
void Company::display()
{
  cout<<"\n**************** ��˾��Ա���¹��ʺ�������Ϣ *********************\n";
  cout<<"���\t����\t\tְλ\t\t�¹���\t\t���۶����ʱ��"<<endl;
  double sum=0;   //���۶��ܺ�
  Person *p=Worker;
  while(p)
  {
    if(p->Duty==3)
		sum+=((Sales *)p)->GetAmount();
    p=p->next;
  }

  p=Worker;
  double sum2=0;  //�����ܺ�
  while(p)
  {
    if(p->Duty==2)((SalesManager *)p)->SetAmount(sum); //sum��sum2����ֿ�����
    p->Output();
    sum2+=p->Earning;
    p=p->next;
  }

  cout<<"����ӯ��:"<<sum*0.20-sum2<<"  (����20���������)"<<endl;

}
/***********************���û�������**************************/
void Company::Set()
{
	cout<<"\n** ���û������� **\n";
	cout<<"����̶���н["<<ManagerSalary<<"Ԫ]:";
	cin>>ManagerSalary; 
	cout<<"���۾���̶���н["<<SalesManagerSalary<<"Ԫ]:"; 
	cin>>SalesManagerSalary;  
	cout<<"���۾������["<<SalesManagerPercent<<"��]:";
	cin>>SalesManagerPercent; 
	cout<<"������Ա���["<<SalesPercent<<"��]:";
	cin>>SalesPercent;
	cout<<"������ԱСʱ����["<<WagePerHour<<"(Ԫ/Сʱ)]:"; 
	cin>>WagePerHour;
	cout<<"Ա����ʶ[>="<<ID<<"]:";
	cin>>ID;
}
/***********************����**************************/
void Company:: Query()
{
	int No,a;
    char Name[20]; 
	Person *p1,*p2;  p1=Worker; 
	cout<<"\n*************************����Ա��***********************\n";
    cout<<"��ѡ����ҷ�ʽ��1 ����Ų���  2 ����������"<<endl;
    cin>>a;
    if(a==1)
	{
       cout<<"ID:";  cin>>No;
		//����Ҫ�޸ĵĽ��
	   while(p1)
	   {
			if(p1->No==No)
			break;
			else
			{
				p2=p1;
				p1=p1->next;
			}
		}
	 }
	else 
	{
		cout<<"����:";  cin>>Name;

		//����Ҫ�޸ĵĽ��
		Person *p1,*p2;  p1=Worker;
		while(p1)
		{
			if((strcmp(p1->Name,Name))==0)
			break;
			else
			{	p2=p1;	p1=p1->next;  }
		}
	}
	if(p1) p1->Output();
	else cout<<"δ�ҵ���Ӧ��Ա"<<endl;
}
/***************************����******************************/
void Company::Save()  //���ݴ���(�����������ݣ���Ա����),�������ı��ļ�
{
	ofstream fPerson,fBase;    //�����ļ����������
	char c;
	cout<<"\n������Ա�ͻ�������,�Ƿ����?[Y/N]:";  cin>>c;
	if(c!='Y'&&c!='y')return;

	//������Ա��š���������λ
	fPerson.open("person.txt",ios::out);  
	Person *p=Worker;
	while(p)
	{
		fPerson<<p->No<<"\t"<<p->Name<<"\t"<<p->Duty<<"\t";
		if(p->Duty==3)
		fPerson<<((Sales*)p)->GetAmount()<<"\t";
		else if(p->Duty==4)
			fPerson<<((Technician *)p)->GetT()<<"\t";
		fPerson<<endl;
		p=p->next;
	}
	fPerson.close();

	//�����������
	fBase.open("base.txt",ios::out);
	fBase<<"����̶���н\t"<<ManagerSalary<<endl;  
	fBase<<"���۾���̶���н\t"<<SalesManagerSalary<<endl;  
	fBase<<"���۾�����ɣ�\t"<<SalesManagerPercent<<endl; 
	fBase<<"������Ա��ɣ�\t"<<SalesPercent<<endl;        
	fBase<<"������ԱСʱ����\t"<<WagePerHour<<endl;       
	fBase<<"ID\t"<<ID<<endl;
	fPerson.close();

	cout<<"\n������Ա�ͻ��������Ѿ����...\n";
}

void Company::Load()  //����װ��(�����������ݣ���Ա����)
{
	//��������װ��
	ifstream fBase;   //�����ļ�����������
	char buf[80];  //buf���ڱ��������ļ��е�ע���ַ���
	fBase.open("base.txt",ios::in);
	fBase>>buf>>ManagerSalary;       //����̶���н
	fBase>>buf>>SalesManagerSalary;  //���۾���̶���н
	fBase>>buf>>SalesManagerPercent; //���۾�����ɣ�
	fBase>>buf>>SalesPercent;        //������Ա��ɣ�
	fBase>>buf>>WagePerHour;         //������ԱСʱ����
	fBase>>buf>>ID;                  //Ա����ʶ
	fBase.close();  
 
	//��Ա��������װ��
	ifstream fPerson;
	Person *p=Worker;
	int No;  char Name[20];  int Duty;
	double Amount,T;
	fPerson.open("person.txt",ios::in);
	//��һ����¼
	fPerson>>No>>Name>>Duty;
	if(Duty==3)fPerson>>Amount;
	else if(Duty==4)fPerson>>T;

	while(fPerson.good())
	{
		//����Ա�����
		switch(Duty)
		{
			case 1:p=new Manager(No,Name,Duty);  break;
			case 2:p=new SalesManager(No,Name,Duty);  break;
			case 3:p=new Sales(No,Name,Duty,Amount);  break;
			case 4:p=new Technician(No,Name,Duty,T);  break;
		}
		p->next=0;

		//Ա������������
		if(Worker)  //���Ѿ����ڽ��
		{
			Person *p2;
			p2=Worker;
			while(p2->next)  //����β���
			{
				p2=p2->next;
			}
			p2->next=p;  //����
		}
		else  //�������ڽ��(���)
		{
			Worker=p;  //����
		}	  
		//����һ����¼
		fPerson>>No>>Name>>Duty;
		if(Duty==3)fPerson>>Amount;
		else if(Duty==4)fPerson>>T;
	}
    fPerson.close();
    cout<<"\n��Ա�ͻ��������Ѿ�װ��...\n";
}

int main()
{
	char c;
	Company a;
	do
	{
		system("cls");
		cout<<"\n\t\t*********** ��˾��Ա����ϵͳ ***********\n";
		cout<<"\t\t\t1��������Ա\n";
		cout<<"\t\t\t2��ɾ����Ա\n";
		cout<<"\t\t\t3����ʾ���¾�Ӫ��Ϣ\n";
		cout<<"\t\t\t4��������������\n";
		cout<<"\t\t\t5����ѯ\n";
		cout<<"\t\t\t6������\n";
		cout<<"\t\t\t7���˳�\t��ѡ��(1-7):";
		cin>>c;
		switch(c)
		{
			case '1':  a.Add();   system("pause");break;
			case '2':  a.Delete();system("pause");break;
			case '3':  a.display(); system("pause");break;
			case '4':  a.Set();   system("pause");break;
			case '5':  a.Query();  system("pause");break;
			case '6':  a.Save();  system("pause");break;
		}
	}while(c!='7');
	return 0;
}
