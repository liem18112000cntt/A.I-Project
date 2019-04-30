# A.I-Project

Copyright @Liem Doan all right reserved
Version 1.5
Updated in 01/5/2019 - 01:39:53

		
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
	- 5 class : class Table(the hien trang thai ban co).
					    class Node(nut tren cay trang thai).
					    class PUZZLE_8(class chinh cua bai toan)
					    class AI_Program(Ke thua abstract class Program)
					    class abstract Program
	- 4 Hanh dong di chuyen : 
    + Tren, Duoi , Trai va Phai.
		+ Vat the di chuyen la o rong(thay vi quan co de gioi han so luong hanh dong)
	
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
			- So luong bao nhieu quan co dang o sai vi tri so voi ket qua.
			- Ham Heuristic : 
				+ Input : Trang thai hien tai, Trang thai cuoi
				+ Ouput : Tong vi tri sai lech tat ca cac quan co o vi tri hien tai so voi vi tri cuoi
			b. Tong Sai Vi lap sau dan
			- Uu diem so voi Tong Sai Vi:
				+ Tiet kiem bo nho dang ke.
				+ Tim nhanh voi dap an nam sau.
			- Nhuoc diem so voi Tong Sai Vi:
				+ Xet lai cac trang thai da xet trong cac loop truoc.
			c. Mahattan Distance
			- Khoang cach ve chieu truc x va y giua hai diem A, B : 
			Dist(A, B) = |Xa -Xb| + |Ya - Yb|
			- Ham Heuristic :
				+ Input : Trang thai hien tai, Trang thai cuoi
				+ Ouput : Tong khoang cach cua tat ca cac quan co o
				vi tri hien tai so voi vi tri cuoi
			d.  Mahattan Distance lap sau dan
			- Uu diem so voi Mahattan Distance:
				+ Tiet kiem bo nho dang ke.
				+ Tim nhanh voi dap an nam sau.
			- Nhuoc diem so voi Mahattan Distance:
				+ Xet lai cac trang thai da xet trong cac loop truoc.
        
IV. Function of my program:
		Input  : Trang thai dau, Trang thai can tim
		Output :| Cac buoc tuan tu de di chuyen o trong.
				| NULL(neu khong tim ra ket qua)

V. Potential:
		- Mo rong giai quyet bai toan PUZZLE N voi ban co 
		kich thuoc sqrt(N + 1) * sqrt(N + 1).
		- VD : PUZZLE 24 - kich thuoc ban co 5 x 5.



Qui trinh thuc hien cua class Program:

1. Thong bao mo dua va Nhap lieu	| 1. void StartMessage() void Input()
2. Kiem tra du lieu cua Nhap lieu	| 2. bool IsValid()
3. Neu du lieu khong hop le :		  | 
	i . Thong bao loi				        | 3. void ErrorMessage()
	ii. Tro lai buoc 1				      |	
4. Xu ly yeu cau bai toan			    | 4. void Process()
5. Xuat ket qua ( neu co )			  | 5. void OutPut()
6. Hoi tiep tuc thuc hien			    | 6. bool IsContinue()
7. Neu tiep tuc chuong trinh:		  |
	i . Tro lai buoc 1				      |
8. Ket thuc chuong trinh			    |

Phuong thuc khuon : void Run()

