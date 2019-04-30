#pragma once
#include <iostream>
#include <time.h>
using namespace std;

#include <cmath>
#include <stack>
#include <queue>
#include <vector>

class Table{
private:
	int Box[3][3];
	int Size;

public:
	Table();
	Table(const Table&);
	Table(int a[][3]);

	//Get & Set
	void GetBoxes(int [][3]) const;
	void SetBoxes(int [][3]);
	int GetBox(int, int) const;
	void SetBox(int, int, int); 
	int GetSize() const;

	//Print
	void Print(ostream&) const;

	//Check
	bool IsEmptyPos(int, int) const;
	bool IsEqual(Table b) const;

	//Main Operations
	int FindNull() const;
	bool Move(int); //Up - Down - Left - Right
	bool MoveUp(int, int);
	bool MoveDown(int, int);
	bool MoveLeft(int, int);
	bool MoveRight(int, int);

};

class Node{
private:
	Table t;
	int Depth;
	int Cost;
	Node *pMove[4]; //Up - Down - Left - Right
	Node *pFather;

public:
	Node(Table);
	Node(const Node*&);

	//Set & Get
	Table GetTable() const;
	void SetTable(Table);
	Node* GetP(int) const;
	void SetP(Table ,int);
	Node* GetFather() const;
	void SetFather(Node*);
	int GetCost() const;
	void SetCost(int);
	int GetDepth() const;
	void SetDepth(int);

	//Print
	void Print(ostream&) const;

	//Main Operations
	bool Move(int);

};

class PUZZLE_8
{
private:
	Node* pStart;
	Node* pGoal;
	

public:
	PUZZLE_8(void);
	PUZZLE_8(Table, Table);

	//Print
	void PrintStart(ostream&);
	void PrintGoal(ostream&);

//Main Process

/*
Terms :
	b : Do chia nhanh trung binh
	d : Do sau 
*/
	//Answer
	stack<Table> FindAnswer(Node*);
	void PrintAnswer(stack<Table>, stack<int>, ostream&);
	stack<int> FindMove(Node*);

	//Check 
	bool IsEqual(Node*) const;
	bool IsNotVisited(Table, Table[], int) const;

	//BFS : O( b ^ (d + 1) )
	void Expand(queue<Node*>&, Node*&, Table[], int);
	Node* Search_BFS(int&, int&);

	//IDS
	int TDG(Node*, int, Table[], int&, Node*&);
	Node* Search_IDS(int&);

//Heuristic Functions
	//Wrong Position Sum
	int  Heuristic_WrongPos(Table, Table) const;
	void Expand_WrongPos(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>>&, Node*&, Table[], int);
	Node* Search_A_Star_WrongPos(int&, int&);

	//Total Mahattan Distance
	int Mahattan_Distance(int, int, int, int) const;
	int Equal_Pos(Table, int) const;
	int Heuristic_Mahattan(Table, Table) const;
	void Expand_Mahattan(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>>&, Node*&, Table[], int);
	Node* Search_A_Star_Mahattan(int&, int&);

	//IDS + Wrong Position Sum => IDA*_WrongPos
	int IDA_WrongPos(Node*, int, Table[], int&, Node*&);
	Node* Search_IDA_Star_WrongPos(int&, int&);

	//IDS + Total Mahattan Distance => IDA*_Mahattan
	int IDA_Mahattan(Node*, int, Table[], int&, Node*&);
	Node* Search_IDA_Star_Mahattan(int&, int&);

};

