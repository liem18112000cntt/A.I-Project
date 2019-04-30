#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

#include "AI_Program.h"

//#include "PUZZLE_8.h"

/*
 
		Copyright @Liem Doan all right reserved
		Version 1.4
		Updated in 30/4/2019 - 04:36:53

		
	I. Question :
			-Puzzle 8 la mot tro choi trong 1 ban co kich thuoc 3x3
		. Co 8 quan co duoc danh so tu 1 den 8 dat vao 8 o bat ki va
		co 1 o rong. Chi co the di chuyen quan co len tren, xuong duoi,
		qua trai va qua phai 1 buoc. Luu y, moi o chi chua 1 quan co
		duy nhat.
			VD: di chuyen quan co 1 qua phai 
		| 1 |   | 2	|		    |   | 1 | 2 |
		-------------		    -------------
		| 3 | 4 | 5 |    ==>    | 3 | 4 | 5 |
		-------------		    -------------
		| 6 | 7 | 8 |		    | 6 | 7 | 8 |
	
	II. Stagegies (chien thuat giai bai toan) :
		- Lap trinh huong doi tuong OOP(basic)
		
		- Xay dung cac trang thai cua ban co thanh 4-ary tree(cay tu phan)
		voi Height khong biet truoc(tuy tham so bai toan)
	
		- 5 class :  class Table(the hien trang thai ban co).
					 class Node(nut tren cay trang thai).
					 class PUZZLE_8(class chinh cua bai toan)
					 class AI_Program(Ke thua abstract class Program)
					 class abstract Program
	
		- 4 Hanh dong di chuyen : + Tren, Duoi , Trai va Phai.
								  + Vat the di chuyen la o rong(
								thay vi quan co de gioi han so
								luong hanh dong)
	
	III. Method to Sovles:
		
		1.Tim kiem khong co thong tin:

		- Breadth First Search : Duyet theo chieu rong( O(b ^ d))
								 b - Do phan nhanh(b = 2.67)
								 d - Do sau cay( d < 30 )

		- Iterative Deepening Search: Tim kiem lap sau dan, 1 loi
		giai kha toi uu cho bai toan.
								 
		2.Tim kiem co thong tin:

		-A* Search :

			a. Tong Sai Vi
			- So luong bao nhieu quan co ?ang dung sai vi tri.

			-Ham Heuristic : 
				+ Input : Trang thai hien tai, Trang thai cuoi
				+ Ouput : Tong vi tri sai lech tat ca cac quan co o
				vi tri hien tai so voi vi tri cuoi

			b. Mahattan Distance
			- Khoang cach ve chieu truc x va y giua hai diem A, B : 
			Dist(A, B) = |Xa -Xb| + |Ya - Yb|

			- Ham Heuristic :
				+ Input : Trang thai hien tai, Trang thai cuoi
				+ Ouput : Tong khoang cach cua tat ca cac quan co o
				vi tri hien tai so voi vi tri cuoi
		
	IV. Function of my program:
		Input  : Trang thai dau, Trang thai can tim
		Output :| Cac buoc tuan tu de di chuyen o trong.
				| NULL(neu khong tim ra ket qua)

	V. Potential:
		- Mo rong giai quyet bai toan PUZZLE N voi ban co 
		kich thuoc sqrt(N + 1) * sqrt(N + 1).
		- VD : PUZZLE 24 - kich thuoc ban co 5 x 5.

*/

/*
	Qui trinh thuc hien cua class Program:

	1. Thong bao mo dua va Nhap lieu	| 1. void StartMessage() void Input()
	2. Kiem tra du lieu cua Nhap lieu	| 2. bool IsValid()
	3. Neu du lieu khong hop le :		| 
		i . Thong bao loi				| 3. void ErrorMessage()
		ii. Tro lai buoc 1				|	
	4. Xu ly yeu cau bai toan			| 4. void Process()
	5. Xuat ket qua ( neu co )			| 5. void OutPut()
	6. Hoi tiep tuc thuc hien			| 6. bool IsContinue()
	7. Neu tiep tuc chuong trinh:		|
		i . Tro lai buoc 1				|
	8. Ket thuc chuong trinh			|

	Phuong thuc khuon : void Run()

*/

int main(){

	/*clock_t begin, finish;
	int numOfNode = 0, memory = 0;

	int start[3][3] = {1, 2, 3,
					   4, 5, 6,
					   7, 8, NULL};

	int goal[3][3]  =  {3, 6, 5,
						2, 1, 8,
						4, NULL, 7};

	int ex[3][3] = {1, 2, 3,
					5, NULL, 6,
					4, 7, 8};

	Table t1(start);

	Table t2(goal);
	
	PUZZLE_8 P(t1, t2);
	
	cout << "Start Status : " << endl;

	P.PrintStart(cout);

	cout << "\n--------------------------------\n";

	cout << endl;



	begin = clock();

	Node* p = P.Search_IDA_Star_WrongPos(numOfNode, memory);

	if(p == NULL)
		cout << "Answer is not found" << endl;
	else
		P.PrintAnswer(P.FindAnswer(p), P.FindMove(p), cout);
		

	finish = clock();

	

	cout << endl;

	cout << "\n--------------------------------\n";

	cout << "Goal Status : " << endl;

	P.PrintGoal(cout);

	cout << "\nStatitics : " << endl;

	cout << "Number of Node Compared : " << numOfNode << endl;

	cout << "Number of Node Created : " << memory << endl;

	cout <<"\nTime Executed : " << double(finish - begin) / CLOCKS_PER_SEC << " seconds." << endl;*/

	AI_Program AI;

	AI.Run(cout, cin);

	system("pause");

	return 0;
}

