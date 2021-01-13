#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <string.h>
using namespace std; 

double ManagerSalary;         //����̶���н
double SalesManagerSalary;      //���۾���̶���н
double SalesManagerPercent;   //���۾�����ɣ�
double SalesPercent;          //������Ա��ɣ�
double WagePerHour;         //������ԱСʱ����
int ID;                     //Ա����ʶ
/***********************Ա����**********************/
class Person  
{
protected:
	int No;  //���
    char Name[20];  //����
    int Duty;       //��λ
    double Earning; //����
    double Amount,t;
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
	double SetAmount(double Amount){
		this->Amount=Amount;
	}
    double GetAmount()  
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
	double SetT(double T){
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
	Person *Worker;
	Person *sales; 
    Person *technicians;
public:
    Company()
	{
		Worker=NULL; 
		sales=NULL;
	    technicians=NULL;
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
    void Change();  //�޸���Ա��Ϣ 
    void display();//��ʾ���¹��ʺ�������Ϣ
    void Query();   //��ѯ
    void Set();     //������������
    void Save();    //���ݴ���(�����������ݣ���Ա����)
    void Load();    //����װ��(�����������ݣ���Ա����)
	void Rank();    //Ա������ 
	void Bubblesort(Person *head);
};

void Company::Add()
{
    Person *p;  
    int Duty;  
    char Name[20];
    double Amount,T;

    cout<<"\n** ����Ա�� **\n";   
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

    switch(Duty)
	{
		case 1:p=new Manager(ID,Name,Duty); break;
		case 2:p=new SalesManager(ID,Name,Duty);  break;
		case 3:p=new Sales(ID,Name,Duty,Amount);   break;
		case 4:p=new Technician(ID,Name,Duty,T);  break;
	}
	p->next=0;

    if(Worker) 
	{
		Person *p2;
		p2=Worker;
		while(p2->next)  
		{
			p2=p2->next;
		}
        p2->next=p; 
	}
    else 
	{
		Worker=p;  
	}
}
/**************************ɾ��*************************/
void Company::Delete()  //ɾ����Ա
{
    int No;
    cout<<"\n** ɾ��Ա�� **\n";
    cout<<"ID:";  cin>>No;

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

    if(p1!=NULL)
	{
		if(p1==Worker)  
		{
			Worker=p1->next;
			delete p1;
		}
        else  
		{
			p2->next=p1->next;
			delete p1;
		}
		cout<<"�ҵ���ɾ��\n";
	}
    else 
		cout<<"δ�ҵ�!\n";
}
void Company::Change()  //�޸���Ա
{
    int No;
	double Amount,t; 
    cout<<"\n** �޸�Ա����Ϣ **\n";
    cout<<"ID:";  cin>>No;

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
	if(p1!=NULL){
	    cout<<"�����޸ĺ������:";  cin>>p1->Name;
	    if(p1->Duty==3)
		{
			
			cout<<"�������۶�:";  cin>>Amount;
			((Sales *)p1)->SetAmount(Amount);
		}
	    else if(p1->Duty==4)
		{
			cout<<"���¹���Сʱ��(0-168):";  
			cin>>t;
			((Technician *)p1)->SetT(t);
		}
		
		cout<<"�޸ĳɹ�"<<endl;
	}
	else{
		cout<<"�޸�ʧ��"<<endl; 
	} 
	
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
    if(p->Duty==2)((SalesManager *)p)->SetAmount(sum); 
    p->Output();
    sum2+=p->Earning;
    p=p->next;
  }

  cout<<"����ӯ��:"<<sum*0.60-sum2<<"  (����40���������)"<<endl;

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
		while(p1)
		{
			if((strcmp(p1->Name,Name))==0)
				break;
			else
			{	
				p2=p1;	p1=p1->next;  
			}
		}
	}
	if(p1) p1->Output();
	else cout<<"δ�ҵ���Ӧ��Ա"<<endl;
}

void Company:: Bubblesort(Person *head)//���������bubble sort
{
    Person *pre, *p,*tail;
    tail = NULL;
    while (head->next != tail)
    {
        pre = head;
        p = head->next;
        while (p->next!=tail)
        {
        	if(p->Duty==3){
        		double c=((Sales *)p)->GetAmount();
        	    double d=((Sales *)p->next)->GetAmount();
	            if (c > d)
	            {
	                pre->next = p->next;
	                p->next = pre->next->next;
	                pre->next->next = p;
	            }
	            else
                	p = p->next;
			}
			else{
        		double c=((Technician *)p)->GetT();
        	    double d=((Technician *)p->next)->GetT();
	            if (c > d)
	            {
	                pre->next = p->next;
	                p->next = pre->next->next;
	                pre->next->next = p;
	            }
	            else
                	p = p->next;
			}
            pre = pre->next;
        }
        tail = p;
    }
}
void Company:: Rank()
{
  cout<<"\n**************** ��˾������Ա�ͼ�����Ա���±������� *********************\n";
  cout<<"���\t����\t\tְλ\t\t�¹���\t\t���۶����ʱ��"<<endl;
  Person *p=Worker;
  while(p)
  {
    if(p->Duty==3){
    	Person *p1;
    	p1=new Sales(p->No,p->Name,p->Duty,((Sales *)p)->GetAmount());
    	p1->next=0;
		if(sales)  
		{
			Person *p2;
			p2=sales;
			while(p2->next)  
			{
				p2=p2->next;
			}
	        p2->next=p1;  
		}
	    else  
		{
			sales=p1;  
		}
	}
	if(p->Duty==4){
		Person *p1;
		p1=new Technician(p->No,p->Name,p->Duty,((Technician *)p)->GetT());
		p1->next=0;
		if(technicians)  
		{
			Person *p2;
			p2=technicians;
			while(p2->next) 
			{
				p2=p2->next;
			}
	        p2->next=p1; 
		}
	    else  
		{
			technicians=p1; 
		}
	}
    p=p->next;
  }
  Bubblesort(sales);
  Bubblesort(technicians);
  cout<<"������Ա������"<<endl;
  while(sales)
  {
  	sales->Output();
    sales=sales->next;
  }
  cout<<"������Ա������"<<endl;
  while(technicians)
  {
  	technicians->Output();
    technicians=technicians->next;
  }
}

void Company::Save()  //���ݴ���(�����������ݣ���Ա����),�������ı��ļ�
{
	ofstream fPerson,fBase;    
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
	ifstream fBase;   
	char buf[80];  
	fBase.open("base.txt",ios::in);
	fBase>>buf>>ManagerSalary;      
	fBase>>buf>>SalesManagerSalary;  
	fBase>>buf>>SalesManagerPercent; 
	fBase>>buf>>SalesPercent;        
	fBase>>buf>>WagePerHour;         
	fBase>>buf>>ID;                 
	fBase.close();  
 
	ifstream fPerson;
	Person *p=Worker;
	int No;  char Name[20];  int Duty;
	double Amount,T;
	fPerson.open("person.txt",ios::in);
	fPerson>>No>>Name>>Duty;
	if(Duty==3)fPerson>>Amount;
	else if(Duty==4)fPerson>>T;

	while(fPerson.good())
	{
		switch(Duty)
		{
			case 1:p=new Manager(No,Name,Duty);  break;
			case 2:p=new SalesManager(No,Name,Duty);  break;
			case 3:p=new Sales(No,Name,Duty,Amount);  break;
			case 4:p=new Technician(No,Name,Duty,T);  break;
		}
		p->next=0;
		if(Worker)  
		{
			Person *p2;
			p2=Worker;
			while(p2->next)  
			{
				p2=p2->next;
			}
			p2->next=p;  
		}
		else 
		{
			Worker=p;  
		}	  
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
		cout<<"\t\t\t3���޸���Ա��Ϣ\n";
		cout<<"\t\t\t4����ʾ���¾�Ӫ��Ϣ\n";
		cout<<"\t\t\t5��������Ա�ͼ�����Ա����\n";
		cout<<"\t\t\t6��������������\n";
		cout<<"\t\t\t7����ѯ\n";
		cout<<"\t\t\t8������\n";
		cout<<"\t\t\t9���˳�\t��ѡ��(1-9):";
		cin>>c;
		switch(c)
		{
			case '1':  a.Add();   system("pause");break;
			case '2':  a.Delete();system("pause");break;
			case '3':  a.Change();system("pause");break;
			case '4':  a.display(); system("pause");break;
			case '5':  a.Rank(); system("pause");break;
			case '6':  a.Set();   system("pause");break;
			case '7':  a.Query();  system("pause");break;
			case '8':  a.Save();  system("pause");break;
		}
	}while(c!='9');
	return 0;
}
