#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <string.h>
using namespace std; 

//全局数据，对象
double ManagerSalary;         //经理固定月薪
double SalesManagerSalary;      //销售经理固定月薪
double SalesManagerPercent;   //销售经理提成％
double SalesPercent;          //销售人员提成％
double WagePerHour;         //技术人员小时工资
int ID;                     //员工标识(要保证唯一)
/***********************员工类**********************/
class Person  
{
protected:
	int No;  //编号
    char Name[20];  //姓名
    int Duty;       //岗位
    double Earning; //收入
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
/************************经理类*******************/
class Manager:public Person  
{
public:
	Manager(char ID,char *Name,int Duty):Person(ID,Name,Duty){ }
    void CalcSalary(){Earning=ManagerSalary;}
    void Output()
    {
		CalcSalary();
		cout<<No<<"\t"<<Name<<"\t\t经理\t\t"<<Earning<<endl;
    }
};
/********************销售经理类********************/
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
		cout<<No<<"\t"<<Name<<"\t\t销售经理\t"<<Earning<<endl;
	}
};
/**************销售员类***************************/
class Sales:public Person  
{
private:
    double Amount;
public:
    Sales(char ID,char *Name,int Duty,double Amount):Person(ID,Name,Duty)
	{
		this->Amount=Amount;
	}
    double GetAmount()  //用于计算月销售总额sum
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
		cout<<No<<"\t"<<Name<<"\t\t销售员\t\t"<<Earning<<"\t\t"<<Amount<<endl;
	}
};
/***********************技术员类**********************/
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
		cout<<No<<"\t"<<Name<<"\t\t技术员\t\t"<<Earning<<"\t\t"<<t<<endl;
	}
};
/**************************公司类***********************/
class Company  
{
private:
	Person *Worker;  /*员工表*/ 
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
    void Add();     //增加人员
    void Delete();  //删除人员
    void Change();  //修改人员信息 
    void display();//显示本月工资和销售信息
    void Query();   //查询
    void Set();     //基础数据设置
    void Save();    //数据存盘(包括基础数据，人员数据)
    void Load();    //数据装入(包括基础数据，人员数据)
	void Rank();    //员工排名 
	void Bubblesort(Person *head);
};

void Company::Add()
{
    Person *p;  //新结点指针
    int Duty;  
    char Name[20];
    double Amount,T;

    cout<<"\n** 新增员工 **\n";    //输入员工信息
    ID++;
    cout<<"输入岗位(1-经理2-销售经理3-销售员4-技术员):";  cin>>Duty;
    cout<<"输入姓名:";  cin>>Name;
    if(Duty==3)
	{
		cout<<"本月销售额:";  cin>>Amount;
	}
    else if(Duty==4)
	{
		cout<<"本月工作小时数(0-168):";  
		cin>>T;
	}

    //创建新员工结点
    switch(Duty)
	{
		case 1:p=new Manager(ID,Name,Duty); break;
		case 2:p=new SalesManager(ID,Name,Duty);  break;
		case 3:p=new Sales(ID,Name,Duty,Amount);   break;
		case 4:p=new Technician(ID,Name,Duty,T);  break;
	}
	p->next=0;

    //员工结点加入链表
    if(Worker)  //若已经存在结点
	{
		Person *p2;
		p2=Worker;
		while(p2->next)  //查找尾结点
		{
			p2=p2->next;
		}
        p2->next=p;  //连接
	}
    else  //若不存在结点(表空)
	{
		Worker=p;  //连接
	}
}
/**************************删除*************************/
void Company::Delete()  //删除人员
{
    int No;
    cout<<"\n** 删除员工 **\n";
    cout<<"ID:";  cin>>No;

    //查找要删除的结点
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

    //删除结点
    if(p1!=NULL)//若找到结点，则删除
	{
		if(p1==Worker)  //若要删除的结点是第一个结点
		{
			Worker=p1->next;
			delete p1;
		}
        else  //若要删除的结点是后续结点
		{
			p2->next=p1->next;
			delete p1;
		}
		cout<<"找到并删除\n";
	}
    else  //未找到结点
		cout<<"未找到!\n";
}
void Company::Change()  //修改人员
{
    int No;
	double Amount;
    cout<<"\n** 修改员工信息 **\n";
    cout<<"ID:";  cin>>No;

    //查找要修改的结点
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
	    cout<<"输入修改姓名:";  cin>>p1->Name;
	    if(p1->Duty==3)
		{
			
			cout<<"本月销售额:";  cin>>p1->Amount;
		}
	    else if(p1->Duty==4)
		{
			cout<<"本月工作小时数(0-168):";  
			cin>>p1->t;
		}
		cout<<"修改成功"<<endl;
	}
	else{
		cout<<"修改失败"<<endl; 
	} 
	
}

/********************显示**************************/
void Company::display()
{
  cout<<"\n**************** 公司人员本月工资和销售信息 *********************\n";
  cout<<"编号\t姓名\t\t职位\t\t月工资\t\t销售额或工作时间"<<endl;
  double sum=0;   //销售额总和
  Person *p=Worker;
  while(p)
  {
    if(p->Duty==3)
		sum+=((Sales *)p)->GetAmount();
    p=p->next;
  }

  p=Worker;
  double sum2=0;  //工资总和
  while(p)
  {
    if(p->Duty==2)((SalesManager *)p)->SetAmount(sum); //sum和sum2必须分开计算
    p->Output();
    sum2+=p->Earning;
    p=p->next;
  }

  cout<<"本月盈利:"<<sum*0.40-sum2<<"  (按照40％利润计算)"<<endl;

}
/***********************设置基础数据**************************/
void Company::Set()
{
	cout<<"\n** 设置基础数据 **\n";
	cout<<"经理固定月薪["<<ManagerSalary<<"元]:";
	cin>>ManagerSalary; 
	cout<<"销售经理固定月薪["<<SalesManagerSalary<<"元]:"; 
	cin>>SalesManagerSalary;  
	cout<<"销售经理提成["<<SalesManagerPercent<<"％]:";
	cin>>SalesManagerPercent; 
	cout<<"销售人员提成["<<SalesPercent<<"％]:";
	cin>>SalesPercent;
	cout<<"技术人员小时工资["<<WagePerHour<<"(元/小时)]:"; 
	cin>>WagePerHour;
	cout<<"员工标识[>="<<ID<<"]:";
	cin>>ID;
}
/***********************查找**************************/
void Company:: Query()
{
	int No,a;
    char Name[20]; 
	Person *p1,*p2;  p1=Worker; 
	cout<<"\n*************************查找员工***********************\n";
    cout<<"请选择查找方式：1 按编号查找  2 按姓名查找"<<endl;
    cin>>a;
    if(a==1)
	{
       cout<<"ID:";  cin>>No;
		//查找要修改的结点
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
		cout<<"姓名:";  cin>>Name;

		//查找要修改的结点
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
	else cout<<"未找到对应人员"<<endl;
}

//void Company:: Bubblesort(Person *head)
//{
//    Person *cur = head;
//    Person *tail = head;
//    Person *p = head;
//    double a,b;
//    int length = 0;
//    int flag = 0;
//    while (tail != NULL)
//    {
//        tail = tail->next;
//    }
//    while (p->next!=tail)
//    {
//        flag = 0;
//        cur = head;
//        while (cur->next != tail)
//        {
//        	if(cur->Duty==3){
//        		double c=((Sales *)cur)->GetAmount();
//        	    double d=((Sales *)cur->next)->GetAmount();
//	            if (c > d)
//	            {
//	            	cout<<"11";
//	                //前后交换
//	                a = c;
//	                c = d;
//	                d = a;
//	                flag = 1;
//	            }
//			}
//			else{
//				if (cur->t > cur->next->t)
//	            {
//	            	cout<<"22";
//	                //前后交换
//	                b = cur->t;
//	                cur->t = cur->next->t;
//	                cur->next->t = b;
//	                flag = 1;
//	            }
//			}
//            cur = cur->next;
//        }
//        //尾指针向前移动
//        tail = cur;
//        //若为1，则证明链表已经有序
//        if (flag == 0)
//        {
//            return;
//        }
//    }
//}
void Company:: Bubblesort(Person *head)//对链表进行bubble sort
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
	            	cout<<"11";
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
  cout<<"\n**************** 公司销售人员和技术人员本月表现排名 *********************\n";
  cout<<"编号\t姓名\t\t职位\t\t月工资\t\t销售额或工作时间"<<endl;
  Person *p=Worker;
//  Person *sales; 
//  Person *technicians;
  while(p)
  {
    if(p->Duty==3){
    	Person *p1;
    	p1=new Sales(p->No,p->Name,p->Duty,((Sales *)p)->GetAmount());
    	p1->next=0;
		if(sales)  //若已经存在结点
		{
			Person *p2;
			p2=sales;
			while(p2->next)  //查找尾结点
			{
				p2=p2->next;
			}
	        p2->next=p1;  //连接
		}
	    else  //若不存在结点(表空)
		{
			sales=p1;  //连接
		}
	}
	if(p->Duty==4){
		Person *p1;
		p1=new Technician(p->No,p->Name,p->Duty,((Technician *)p)->GetT());
		p1->next=0;
		if(technicians)  //若已经存在结点
		{
			Person *p2;
			p2=technicians;
			while(p2->next)  //查找尾结点
			{
				p2=p2->next;
			}
	        p2->next=p1;  //连接
		}
	    else  //若不存在结点(表空)
		{
			technicians=p1;  //连接
		}
	}
    p=p->next;
  }
  Bubblesort(sales);
  Bubblesort(technicians);
  cout<<"销售人员排名："<<endl;
  while(sales)
  {
  	sales->Output();
    sales=sales->next;
  }
  cout<<"技术人员排名："<<endl;
  while(technicians)
  {
  	technicians->Output();
    technicians=technicians->next;
  }
}
/***************************保存******************************/
void Company::Save()  //数据存盘(包括基础数据，人员数据),均采用文本文件
{
	ofstream fPerson,fBase;    //定义文件输出流对象
	char c;
	cout<<"\n保存人员和基础数据,是否继续?[Y/N]:";  cin>>c;
	if(c!='Y'&&c!='y')return;

	//保存人员编号、姓名、岗位
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

	//保存基础数据
	fBase.open("base.txt",ios::out);
	fBase<<"经理固定月薪\t"<<ManagerSalary<<endl;  
	fBase<<"销售经理固定月薪\t"<<SalesManagerSalary<<endl;  
	fBase<<"销售经理提成％\t"<<SalesManagerPercent<<endl; 
	fBase<<"销售人员提成％\t"<<SalesPercent<<endl;        
	fBase<<"技术人员小时工资\t"<<WagePerHour<<endl;       
	fBase<<"ID\t"<<ID<<endl;
	fPerson.close();

	cout<<"\n保存人员和基础数据已经完成...\n";
}

void Company::Load()  //数据装入(包括基础数据，人员数据)
{
	//基础数据装入
	ifstream fBase;   //建立文件输入流对象
	char buf[80];  //buf用于保存数据文件中的注释字符串
	fBase.open("base.txt",ios::in);
	fBase>>buf>>ManagerSalary;       //经理固定月薪
	fBase>>buf>>SalesManagerSalary;  //销售经理固定月薪
	fBase>>buf>>SalesManagerPercent; //销售经理提成％
	fBase>>buf>>SalesPercent;        //销售人员提成％
	fBase>>buf>>WagePerHour;         //技术人员小时工资
	fBase>>buf>>ID;                  //员工标识
	fBase.close();  
 
	//人员数据数据装入
	ifstream fPerson;
	Person *p=Worker;
	int No;  char Name[20];  int Duty;
	double Amount,T;
	fPerson.open("person.txt",ios::in);
	//读一条记录
	fPerson>>No>>Name>>Duty;
	if(Duty==3)fPerson>>Amount;
	else if(Duty==4)fPerson>>T;

	while(fPerson.good())
	{
		//创建员工结点
		switch(Duty)
		{
			case 1:p=new Manager(No,Name,Duty);  break;
			case 2:p=new SalesManager(No,Name,Duty);  break;
			case 3:p=new Sales(No,Name,Duty,Amount);  break;
			case 4:p=new Technician(No,Name,Duty,T);  break;
		}
		p->next=0;

		//员工结点加入链表
		if(Worker)  //若已经存在结点
		{
			Person *p2;
			p2=Worker;
			while(p2->next)  //查找尾结点
			{
				p2=p2->next;
			}
			p2->next=p;  //连接
		}
		else  //若不存在结点(表空)
		{
			Worker=p;  //连接
		}	  
		//读下一条记录
		fPerson>>No>>Name>>Duty;
		if(Duty==3)fPerson>>Amount;
		else if(Duty==4)fPerson>>T;
	}
    fPerson.close();
    cout<<"\n人员和基础数据已经装入...\n";
}

int main()
{
	char c;
	Company a;
	do
	{
		system("cls");
		cout<<"\n\t\t*********** 公司人员管理系统 ***********\n";
		cout<<"\t\t\t1－增加人员\n";
		cout<<"\t\t\t2－删除人员\n";
		cout<<"\t\t\t3－修改人员信息\n";
		cout<<"\t\t\t4－显示本月经营信息\n";
		cout<<"\t\t\t5－销售人员和技术人员排名\n";
		cout<<"\t\t\t6－基础数据设置\n";
		cout<<"\t\t\t7－查询\n";
		cout<<"\t\t\t8－保存\n";
		cout<<"\t\t\t9－退出\t请选择(1-9):";
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
