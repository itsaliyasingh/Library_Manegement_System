#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
using namespace std;
struct date
{int day;
int month;
int year;};
//class for book information  and student information
class bookinfo
	{int ISBN_No;
	 int Book_No;
	 char Title[80];
	 char Author[80];
	 char Subject[80];
	 int Price;
	 int token;
	public:
	 bookinfo(){token=0;}
	 void enter_bookinfo()
	 {cout<<"Enter ISBN No: ";
	 cin>>ISBN_No;
	 cout<<"Enter Book No: ";
	 cin>>Book_No;
	 cout<<"Enter Title: ";
	 gets(Title);
	 cout<<"Enter Author: ";
	 gets(Author);
	 cout<<"Enter Subject: ";
	 gets(Subject);
	 cout<<"Enter price: ";
	 cin>>Price;}
	 void display_bookinfo()
	 {cout<<"\nISBN No: "<<ISBN_No;
	 cout<<"\nBook No: "<<Book_No;
	 cout<<"\nTitle: "<<Title;
	 cout<<"\nAuthor: "<<Author;
	 cout<<"\nSubject: "<<Subject;
	 cout<<"\nPrice: "<<Price;
	 cout<<"\nBook Status: ";
	 Disp_token();
	 }
	 void modify_book()
	 {cout<<"Enter new Book No: ";
	 cin>>Book_No;
	 cout<<"Enter new Title: ";
	 cin>>Title;
	 cout<<"Enter new Price: ";
	 cin>>Price;}
	 void Disp_token()
	 {if(token==1)
		cout<<"Not Available";
	 else
		cout<<"Available";}
	 int ret_token()
	 {return token;}
	 void Add_token()
	 {token=1;}
	 void Remove_token()
	 {token=0;}
	 int ret_ISBNNo()
	 {return ISBN_No;}
	};
class student
	 {int Admi_no;
	  char student_name[80];
	  int CL;
	  char Sec;
	  int NOBT; //No Of Book Taken
	 public:
	  student(){NOBT=0;}
	  void enter_student()
	  {cout<<"Enter Admi_No: ";
	  cin>>Admi_no;
	  cout<<"Enter Student Name: ";
	  gets(student_name);
	  cout<<"Enter Class and Section: ";
	  cin>>CL>>Sec; }
	  void disp_student()
	  {cout<<"\nAdmi_No: "<<Admi_no;
	  cout<<"\nStudent Name: "<<student_name;
	  cout<<"\nClass and Section: "<<CL<<" '"<<Sec<<"' ";
	  cout<<"\nNo of book taken: "<<NOBT; }
	  void mod_student()
	  {cout<<"Enter new Student Name: ";
	  gets(student_name);
	  cout<<"Enter new Class and Section: ";
	  cin>>CL>>Sec;}
	  int ret_Admino()
	  {return Admi_no;}
	  void Add_NOBT()
	  {NOBT++;}
	  void Remove_NOBT()
	  {NOBT--;}
	  };
//issue return function
void Issue()
{student s;
bookinfo b;
int temp1=0, temp2=0;
fstream fs("student.dat",ios::in|ios::out|ios::binary);
fstream fb("book.dat",ios::in|ios::out|ios::binary);
int isbn,adno;
cout<<"Enter ISBN No: ";
cin>>isbn;
cout<<"Enter Admission No of student wanted book: ";
cin>>adno;
while(fb.read((char*)&b,sizeof(b)) && temp1==0)
{if(b.ret_ISBNNo()==isbn)
{temp1=1;
if(b.ret_token()==1)
	cout<<"Book not Avalible: ";
else
	{
	b.Add_token();
	int pos=-1*sizeof(b);
	fb.seekp(pos,ios::cur);
	fb.write((char*)&b,sizeof(b));
	while(fs.read((char*)&s,sizeof(s)) && temp2==0)
	if(s.ret_Admino()==adno)
	{temp2=1;
	s.Add_NOBT();
	int pos1=-1*sizeof(s);
	fs.seekp(pos1,ios::cur);
	fs.write((char*)&s,sizeof(s));
	cout<<"Book Sucessfully issued \n Please return the book before 15 days";  } }}
}}
void ret_book()
{student s;
bookinfo b;
fstream fb("book.dat",ios::in|ios::out|ios::binary);
fstream fs("student.dat",ios::in|ios::out|ios::binary);
int isbn,adno;
int temp1=0,temp2=0;
cout<<"Enter ISBN No: ";
cin>>isbn;
cout<<"Enter Admission No of student wanted to return book: ";
cin>>adno;
while(fb.read((char*)&b,sizeof(b)) && temp1==0)
{if(b.ret_ISBNNo()==isbn)
{temp1=1;
if(b.ret_token()==0)
	cout<<"Book not taken ";
else
	 {b.Remove_token();
	 int pos=-1*sizeof(b);
	 fb.seekg(pos,ios::cur);
	 fb.write((char*)&b,sizeof(b));
	 while(fs.read((char*)&s,sizeof(s)) && temp2==0)
	 if(s.ret_Admino()==adno)
	 {temp2=1;
	 s.Remove_NOBT();
	 int pos=-1*sizeof(s);
	 fs.seekg(pos,ios::cur);
	 fs.write((char*)&s,sizeof(s));
	 cout<<"Book returned sucessfully ";}  } }
}}
//functions related to book
void disp_allbook()
{fstream fin("book.dat",ios::in|ios::out|ios::binary);
bookinfo B;
while(fin.read((char*)&B,sizeof(B)))
{B.display_bookinfo();}
}
void disp_spbook()
{fstream fin("book.dat",ios::in|ios::out|ios::binary);
bookinfo B;
int isbn;
int temp=0;
cout<<"Enter ISBN No: ";
cin>>isbn;
while(fin.read((char*)&B,sizeof(B)))
if(B.ret_ISBNNo()==isbn)
	{B.display_bookinfo();
	temp=1;}
if(temp==0)
	cout<<"Book of ISBN No "<<isbn<<" does not exist";
}
void mod_book()
{fstream fin("book.dat",ios::in|ios::app|ios::out|ios::binary);
bookinfo B;
int isbn;
cout<<"Enter ISBN No: ";
cin>>isbn;
while(fin.read((char*)&B,sizeof(B)))
if(B.ret_ISBNNo()==isbn)
	{B.modify_book();
	int pos=-1*sizeof(B);
	fin.seekg(pos,ios::cur);
	fin.write((char*)&B,sizeof(B));}
else
	cout<<"Book of ISBN No "<<isbn<<" does not exist";
}
void enter_book()
{fstream fout("book.dat",ios::out|ios::app|ios::binary);
bookinfo B;
char ch='Y';
do
{B.enter_bookinfo();
fout.write((char*)&B,sizeof(B));
cout<<"Do you want to Add more new book record (Y/N): ";
cin>>ch;}
while(ch=='Y'||ch=='y');
}
//functions related to students
void disp_allstudent()
{fstream fin("student.dat",ios::in|ios::out|ios::binary);
student s;
while(fin.read((char*)&s,sizeof(s)))
{s.disp_student();}
}
void disp_spstudent()
{fstream fin("student.dat",ios::in|ios::out|ios::binary);
student s;
int temp=0;
int adno;
cout<<"Enter ISBN No: ";
cin>>adno;
while(fin.read((char*)&s,sizeof(s)))
if(s.ret_Admino()==adno)
	{
	s.disp_student();
	temp=1;
	}
if(temp==0)
	cout<<"Student of Admission No "<<adno<<" does not exist";
}
void enter_student()
{fstream fout("student.dat",ios::out|ios::app|ios::binary);
student s;
char ch='Y';
do
{s.enter_student();
fout.write((char*)&s,sizeof(s));
cout<<"Do you want to Add more new student record (Y/N): ";
cin>>ch;}
while(ch=='Y'||ch=='y');
}
void mod_stud()
{fstream f("student.dat",ios::in|ios::out|ios::app|ios::binary);
student s;
bookinfo B;
int adno;
cout<<"Enter Admission No: ";
cin>>adno;
while(f.read((char*)&s,sizeof(s)))
if(s.ret_Admino()==adno)
	{s.mod_student();
	int pos=-1*sizeof(s);
	f.seekp(pos,ios::cur);
	f.write((char*)&s,sizeof(s));}
else
	cout<<"Book of Admission No "<<adno<<" does not exist";
}
//menu function of book details
void Book_details()
{int i;
cout<<"\nPress 1 for viewing all Book Details: ";
cout<<"\nPress 2 for viewing specific book details: ";
cout<<"\nPress 3 for writting new record: ";
cout<<"\nPress 4 for modifying specific record: ";
cout<<"\nPress 5 to exit\n";
cin>>i;
switch(i)
{case 1:disp_allbook();break;
case 2: disp_spbook();break;
case 3: enter_book();break;
case 4: mod_book();break;
case 5: break; }
}
//menu function of students details
void student_details()
{int i;  student s;
cout<<"\nPress 1 for viewing all Student Details: ";
cout<<"\nPress 2 for viewing specific student details: ";
cout<<"\nPress 3 for writting new record: ";
cout<<"\nPress 4 for modifying specific record: ";
cout<<"\nPress 5 to exit\n";
cin>>i;
switch(i)
{case 1: disp_allstudent();break;
case 2: disp_spstudent();break;
case 3: enter_student();break;
case 4: mod_stud();break;
case 5: break;}
}
//menu library function
void library()
{int i;
cout<<"\nPress 1 to issue a book: ";
cout<<"\nPress 2 to return issued book: ";
cout<<"\nPress 5 to exit\n";
cin>>i;
switch(i)
{case 1: Issue();break;
case 2: ret_book();break;
case 5: break;}
}
//main menu
int main()
{
int i;
cout<<"\n                   Main Menu             ";
cout<<"\nPress 1 for writting or knowing book details ";
cout<<"\nPress 2 for writing or knowing student details ";
cout<<"\nPress 3 for issuing or taking return the issued book ";
cout<<"\nPress 5 to exit\n";
cin>>i;
switch(i)
{case 1:Book_details() ;break;
case 2: student_details() ;break;
case 3: library();break;
case 5: break;}
return 0;
}