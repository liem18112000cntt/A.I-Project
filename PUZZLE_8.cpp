#include "PUZZLE_8.h"
#define MAX_TIME_EXE 20000

//Table-----------------------------------------------------------------------------------------------------------
Table::Table(){
	Size = 3;
}

Table::Table(int a[][3]){
	Size = 3;
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			Box[i][j] = a[i][j];
}

Table::Table(const Table& t){
	Size = t.GetSize();
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			Box[i][j] = t.GetBox(i, j);
}

//Get & Set
void Table::GetBoxes(int a[][3]) const{
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			a[i][j] = Box[i][j];
}

void Table::SetBoxes(int a[][3]){
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			Box[i][j] = a[i][j];
}

int Table::GetBox(int i, int j) const{
	return Box[i][j];
}

void Table::SetBox(int i, int j, int k){
	Box[i][j] = k;
}

int Table::GetSize() const{
	return 3;
}

//Print
void Table::Print(ostream& out) const{
	for(int i = 0; i < Size; i++){
		for(int j = 0; j < Size; j++){
			if(Box[i][j] == NULL)
				out << " \t";
			else
				out << Box[i][j] << "\t";
		}
		cout << endl << endl;
	}
}

//Check
bool Table::IsEmptyPos(int i, int j) const{
	return Box[i][j] == NULL;
}

//Main Operations
int Table::FindNull() const{
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			if(Box[i][j] == NULL)
				return i * Size + j;
	return -1;
}

bool Table::MoveUp(int i, int j){
	if(i == 0)
		return false;

	swap(Box[i][j], Box[i - 1][j]);
	return true;
}

bool Table::MoveDown(int i , int j){
	if(i == Size - 1)
		return false;

	swap(Box[i][j], Box[i + 1][j]);
	return true;
}

bool Table::MoveLeft(int i, int j){
	if(j == 0)
		return false;

	swap(Box[i][j], Box[i][j - 1]);
	return true;
}

bool Table::MoveRight(int i, int j){
	if(j == Size - 1)
		return false;

	swap(Box[i][j + 1], Box[i][j]);
	return true;
}

bool Table::Move(int c){
	int s = FindNull();
	int i = s / Size;
	int j = s % Size;

	switch(c){
		case 0:
			return MoveUp(i, j);

		case 1:
			return MoveDown(i, j);

		case 2:
			return MoveLeft(i, j);

		case 3:
			return MoveRight(i, j);

		default:
			break;
	}
	return false;
}

//Check Equality
bool Table::IsEqual(Table src) const {
	int arr[3][3];
	src.GetBoxes(arr);

	if(Size != src.GetSize())
		return false;

	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			if(Box[i][j] != arr[i][j])
				return false;
	
	return true;
}
//-----------------------------------------------------------------------------------------------------------


//Node-----------------------------------------------------------------------------------------------------------
Node::Node(Table src){
	int arr[3][3];
	src.GetBoxes(arr);

	int s = 3;

	for(int i = 0; i < s; i++)
		for(int j = 0; j < s; j++)
			this->t.SetBox(i, j, arr[i][j]);
	this->pFather = NULL;

	for(int i = 0; i < 4; i++)
		this->pMove[i] = NULL;

	this->Cost = 0;
	this->Depth = 0;
}

Node::Node(const Node*& src){
	int arr[3][3];
	src->GetTable().GetBoxes(arr);

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			this->t.SetBox(i, j, arr[i][j]);

	for(int i = 0; i < 4; i++)
		this->pMove[i] = src->GetP(i);

	this->Cost = src->GetCost();
	this->Depth = src->GetDepth();
}

//Set & Get
void Node::SetP(Table b, int c){
	if( c >= 0 && c <= 3){
		pMove[c] = new Node(b);
		pMove[c]->SetFather(this);
	}
}

Node* Node::GetP(int c) const{
	if( c >= 0 && c <= 3){
		return this->pMove[c];
	}
	return NULL;
}

void Node::SetTable(Table b){
	this->t = b;
}

Table Node::GetTable() const{
	return this->t;
}

int Node::GetCost() const{
	return this->Cost;
}

int Node::GetDepth() const{
	return this->Depth;
}

void Node::SetCost(int c){
	this->Cost = c;
}

void Node::SetDepth(int d){
	this->Depth = d;
}

void Node::SetFather(Node* p){
	this->pFather = p;
}

Node* Node::GetFather() const {
	return this->pFather;
}

//Print
void Node::Print(ostream& out) const{
	this->t.Print(out);
}

//Main Operations
bool Node::Move(int c){
	if( c >= 0 && c <= 3){
		return Move(c);
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------

//Puzzle_8-----------------------------------------------------------------------------------------------------------
PUZZLE_8::PUZZLE_8(void){
	pStart = NULL;
	pGoal = NULL;

}

PUZZLE_8::PUZZLE_8(Table s, Table g){
	pStart = new Node(s);
	pGoal = new Node(g);
}

//Print
void PUZZLE_8::PrintStart(ostream& out){
	pStart->Print(out);
}

void PUZZLE_8::PrintGoal(ostream& out){
	pGoal->Print(out);
}


//Check
bool PUZZLE_8::IsEqual(Node* p) const{
	return p->GetTable().IsEqual(pGoal->GetTable());
}

bool PUZZLE_8::IsNotVisited(Table t, Table v[], int size) const{
	for(int i = 0; i < size; i++)
		if(t.IsEqual(v[i]))
			return false;
	return true;
}

//Answer
stack<Table> PUZZLE_8::FindAnswer(Node* p){
	stack<Table> temp;
	Node* pCur = p;
	while(pCur != pStart){
		temp.push(pCur->GetTable());
		pCur = pCur->GetFather();
	}

	return temp;
}

stack<int> PUZZLE_8::FindMove(Node* p){
	stack<int> temp;
	Node* pCur = p;
	while(pCur != pStart){
		Node* pF = pCur->GetFather();
		for(int i = 0; i < 4; i++){
			if(pF->GetP(i) == pCur)
				temp.push(i);
		}
		pCur = pCur->GetFather();
	}

	return temp;
}

void PUZZLE_8::PrintAnswer(stack<Table> s, stack<int> m, ostream& out){
	int i = 1;
	while(!s.empty()){
		Table ta = s.top();
		out << "Step " << i << " : ";

		int move = m.top();
		switch(move){
			case 0:
				out << "Move Up";
				break;
			case 1:
				out << "Move Down";
				break;
			case 2:
				out << "Move Left";
				break;
			case 3:
				out << "Move Right";
				break;
		}

		out << endl << endl;

		ta.Print(out);

		out << endl;

		s.pop();
		m.pop();

		i++;
	}
}

//BFS : O( b ^ (d + 1) )
Node* PUZZLE_8::Search_BFS(int& numOfNode, int& memory){
	queue<Node*> Q;
	Table t[MAX_TIME_EXE];
	int size = 0;
	Node* pNode = pStart;
	Q.push(pNode);
	int time = MAX_TIME_EXE;

	//Main Loop
	while(!Q.empty() && time != 0){
		Node* p = Q.front();
		Q.pop();

		t[size] = p->GetTable();
		size++;
		
		if(IsEqual(p)){
			memory = size + Q.size();
			numOfNode = size;
			return p;
		}

		Expand(Q, p, t, size);

		time--;
	}

	memory = size + Q.size();
	numOfNode = size;
	return NULL;

}

void PUZZLE_8::Expand(queue<Node*> &Q, Node* &p, Table t[], int size){
	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, t, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(temp->GetCost() + 1);
			temp->SetDepth(temp->GetDepth() + 1);
			Q.push(temp);
		}
	}
}

//IDS :
int PUZZLE_8::TDG(Node *p, int d, Table v[], int& size, Node* &Answer){
	bool Divide = false;

	if(IsEqual(p)){
		Answer = p;
		return 1;
	}else if(p->GetDepth() == d){
		return 0;
	}

	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, v, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(p->GetCost() + 1);
			temp->SetDepth(p->GetDepth() + 1);

			v[size] = temp->GetTable();
			size++;

			int result = TDG(temp, d, v, size, Answer);

			if(result == 0)
				Divide = true;
			else if(result != -1)
				return result;
		}
		
	}

	if(Divide == true)
		return 0;
	return -1;
}

Node* PUZZLE_8::Search_IDS(int& numOfNode){
	for(int d = 1; d < 30; d++){
		Node* p = NULL;
		Table v[MAX_TIME_EXE];
		int size = 0;
		int result = TDG(pStart, d, v, size, p);
		numOfNode = size;
		if(result != 0)
			return p;
	}

	return NULL;
}


//Heuristic Functions

//Total Mahattan Distance
int PUZZLE_8::Mahattan_Distance(int a, int b, int c, int d) const{
	return abs(a - c) + abs(b - d);
}

int PUZZLE_8::Equal_Pos(Table t, int k) const{
	int Size = t.GetSize();
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++)
			if(k == t.GetBox(i, j))
				return Size * i + j;
	return -1;
}

int PUZZLE_8::Heuristic_Mahattan(Table tCur, Table tGoal) const{
	int Size = tCur.GetSize();
	int S = 0;
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++){
			int k = tCur.GetBox(i, j);
			if(k != NULL){
				int x = Equal_Pos(tGoal, k) / Size;
				int y = Equal_Pos(tGoal, k) % Size;
				S += Mahattan_Distance(i, j, x, y);
			}
		}

	return S;
}

void PUZZLE_8::Expand_Mahattan(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> &PQ, Node* &p, Table t[], int size){
	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, t, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(p->GetCost() + 1);
			temp->SetDepth(p->GetDepth() + 1);
			pair<int, Node*> Pair;
			Pair.second = temp;
			Pair.first = temp->GetDepth() + Heuristic_Mahattan(temp->GetTable(), pGoal->GetTable());
			PQ.push(Pair);
		}
	}
}

Node* PUZZLE_8::Search_A_Star_Mahattan(int& numOfNode, int& memory){
	priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> PQ;
	pair<int, Node*> Pair;
	Pair.second = pStart; 
	Pair.first = pStart->GetDepth() + Heuristic_Mahattan(pStart->GetTable(), pGoal->GetTable());
	PQ.push(Pair);
	Table t[MAX_TIME_EXE];
	int size = 0;

	while(!PQ.empty() && size <= MAX_TIME_EXE){
		pair<int, Node*> P1;
		P1 = PQ.top();

		PQ.pop();
		t[size] = P1.second->GetTable();
		size++;

		if(IsEqual(P1.second)){
			memory = size + PQ.size();
			numOfNode = size;
			return P1.second;
		}

		Expand_Mahattan(PQ, P1.second, t, size);
	}

	return NULL;
}

//IDS + Total Mahattan Distance => IDA*_Mahattan
int PUZZLE_8::IDA_Mahattan(Node *p, int cost, Table v[], int& size, Node* &Answer){
	bool Divide = false;

	if(IsEqual(p)){
		Answer = p;
		return 1;
	}else if(p->GetDepth() + Heuristic_Mahattan(p->GetTable(), pGoal->GetTable()) > cost){
		return 0;
	}

	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, v, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(p->GetCost() + 1);
			temp->SetDepth(p->GetDepth() + 1);

			v[size] = temp->GetTable();
			size++;

			int result = IDA_Mahattan(temp, cost, v, size, Answer);

			if(result == 0)
				Divide = true;
			else if(result != -1)
				return result;
		}
		
	}

	if(Divide == true)
		return 0;
	return -1;
}

Node* PUZZLE_8::Search_IDA_Star_Mahattan(int& numOfNode, int& memory){
	int cost = pStart->GetDepth() + Heuristic_Mahattan(pStart->GetTable(), pGoal->GetTable());
	for(int d = cost; d < 35; d++){
		Node* p = NULL;
		Table v[MAX_TIME_EXE];
		int size = 0;
		int result = IDA_Mahattan(pStart, d, v, size, p);
		numOfNode = size;
		if(result != 0)
			return p;
	}

	return NULL;
}

//Fixed Wrong Position
int PUZZLE_8::Heuristic_WrongPos(Table tCur, Table tGoal) const{
	int count = 0;
	int Size = tCur.GetSize();
	for(int i = 0; i < Size; i++)
		for(int j = 0; j < Size; j++){
			int x = tCur.GetBox(i, j);
			int y = tGoal.GetBox(i, j);
			if(x != y)
				count++;
		}
	return count;
}

void PUZZLE_8::Expand_WrongPos(priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>>& PQ, Node*&p, Table t[], int size){
	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, t, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(p->GetCost() + 1);
			temp->SetDepth(p->GetDepth() + 1);
			pair<int, Node*> Pair;
			Pair.second = temp;
			Pair.first = temp->GetDepth() + Heuristic_WrongPos(temp->GetTable(), pGoal->GetTable());
			PQ.push(Pair);
		}
	}
}

Node* PUZZLE_8::Search_A_Star_WrongPos(int& numOfNode, int& memory){
	priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> PQ;
	pair<int, Node*> Pair;
	Pair.second = pStart; 
	Pair.first = pStart->GetDepth() + Heuristic_WrongPos(pStart->GetTable(), pGoal->GetTable());
	PQ.push(Pair);
	Table t[MAX_TIME_EXE];
	int size = 0;

	while(!PQ.empty() && size <= MAX_TIME_EXE){
		pair<int, Node*> P1;
		P1 = PQ.top();

		PQ.pop();
		t[size] = P1.second->GetTable();
		size++;

		if(IsEqual(P1.second)){
			numOfNode = size;
			memory = size + PQ.size();
			return P1.second;
		}

		Expand_WrongPos(PQ, P1.second, t, size);
	}

	return NULL;
}

//IDS + Wrong Position Sum => IDA*_WrongPos
int PUZZLE_8::IDA_WrongPos(Node *p, int cost, Table v[], int& size, Node* &Answer){
	bool Divide = false;

	if(IsEqual(p)){
		Answer = p;
		return 1;
	}else if(p->GetDepth() + Heuristic_WrongPos(p->GetTable(), pGoal->GetTable()) > cost){
		return 0;
	}

	for(int i = 0; i < 4; i++){
		Table b = p->GetTable();
		if(b.Move(i) && IsNotVisited(b, v, size)){
			p->SetP(b, i);
			Node* temp = p->GetP(i);
			temp->SetFather(p);
			temp->SetCost(p->GetCost() + 1);
			temp->SetDepth(p->GetDepth() + 1);

			v[size] = temp->GetTable();
			size++;

			int result = IDA_WrongPos(temp, cost, v, size, Answer);

			if(result == 0)
				Divide = true;
			else if(result != -1)
				return result;
		}
		
	}

	if(Divide == true)
		return 0;
	return -1;
}

Node* PUZZLE_8::Search_IDA_Star_WrongPos(int& numOfNode, int& memory){
	int cost = pStart->GetDepth() + Heuristic_WrongPos(pStart->GetTable(), pGoal->GetTable());
	for(int d = cost; d < 35; d++){
		Node* p = NULL;
		Table v[MAX_TIME_EXE];
		int size = 0;
		int result = IDA_WrongPos(pStart, d, v, size, p);
		numOfNode = size;
		if(result != 0)
			return p;
	}

	return NULL;
}

