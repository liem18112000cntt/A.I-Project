#pragma once
#include <iostream>
using namespace std;

/*
	Qui trinh thuc hien cua Program:

	1. Thong bao mo dua va Nhap lieu	| 1. void StartMessage() void Input()
	2. Kiem tra du lieu cua Nhap lieu	| 2. bool IsValid()
	3. Neu du lieu khong hop le :		| 
		i . Thong bao loi				| 3. void ErrorMessage()
		ii. Tro lai buoc 1				|	
	4. Xu ly yeu cau bai toan			| 4. void Process()
	5. Kiem tra lap lai xu ly			| 5. bool IsRepeatProcess()
		i. Neu repeat : tro lai buoc 5	|
		ii. Neu khong : tiep tuc		|
	6. Xuat ket qua ( neu co )			| 6. void OutPut()
	7. Hoi tiep tuc thuc hien			| 7. bool IsContinue()
	8. Neu tiep tuc chuong trinh:		|
		i . Tro lai buoc 1				|
	9. Ket thuc chuong trinh			|

	Phuong thuc khuon : void Run()

*/

class Program
{
	public:
		//Template method - Phuong thuc khuon
		void Run(ostream&, istream&);

	protected:

		//Polymophirms - Co che da hinh
		virtual void StartMessage(ostream&) const = 0;
		virtual void Input(ostream&, istream&) = 0;
		virtual bool IsValid() const = 0;
		virtual void Process(ostream&, istream&) = 0;
		virtual void OutputProcess(ostream&) const = 0;
		virtual void Output(ostream&) const = 0;

		//Invariant Source Code - Ma nguon bat bien
		virtual void ErrorMessage(ostream&) const;
		virtual bool IsRepeatProcess(ostream&, istream&) const;
		virtual bool IsContinue(ostream&, istream&) const;
};

