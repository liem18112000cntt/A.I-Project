#pragma once
#include "c:\users\hp\desktop\school exercise\oop\program class template\ai_game_01_beta\program.h"
#include <string>
#include "PUZZLE_8.h"

class AI_Program :
	public Program
{
private:
	Table Start;
	Table Goal;
	int Search_choose;
	string Search_Name[100];
	double Time_Exe[100];
	int Node_Created[100];
	long Memory_Used[100];
	int Count_Process;

	void RandomMix(int a[][3], int n){
	PUZZLE_8 temp;
	Table v[10000];
	int size = 0;
	Table t(a);
	
	for(int i = 0; i < n; i++){

		do{
			int c = rand() % 4;
			t.Move(c);
		}while(!temp.IsNotVisited(t, v, size));
		
		v[size] = t;
		size++;
	}

	t.GetBoxes(a);
}

public:
	AI_Program(void){
		Count_Process = 0;
	}

	~AI_Program(void){}

	//Polymophirms - Co che da hinh
	virtual void StartMessage(ostream& out) const{
		out << "\n---------------PUZZLE 8 SOLVER--------------\n\n";
	}

	virtual void Input(ostream& out, istream& in){
		out << "---------------------INPUT-------------------:" << endl << endl;
		


		//Start Input
		out << "Caution : Only number from 0 to 8 are allowed!" << endl;
		out << "          Each input is unique number!" << endl;
		out << "Enter start status : " << endl;
		int arr[3][3];

		out << "Press 01 : Add Manually" << endl;
		out << "Press 02 : Add Automatically" << endl;

		int choose1;
		do{
			out << "Choose : "; in >> choose1;
		}while(choose1 != 1 && choose1 != 2);

		if(choose1 == 1){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					int num;
					out << "Table[ " << i + 1 << " ][ " << j + 1 << " ] : ";
					in >> num;
					if(num == 0)
						arr[i][j] = NULL;
					else
						arr[i][j] = num;
					
				}
			}
		}else{
			int count = 1;
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if(i == 2 && j == 2)
						arr[i][j] = NULL;
					else
						arr[i][j] = count;
					count++;
				}
			}
		}
		Start.SetBoxes(arr);
		out << "Check Start status : " << endl;
		Start.Print(out);
		out << endl;



		//Goal Input
		out << "Enter goal status : " << endl;
		out << "Warning : Enter goal status manually may make program "<< endl; 
		out << "	stuck forever as answer can not be found!!!" << endl;
		out << "Press 01 : Add Manually" << endl;
		out << "Press 02 : Add Randomly" << endl;
		int choose2;
		do{
			out << "Choose : "; in >> choose2;
		}while(choose2 != 1 && choose2 != 2);

		int arr1[3][3];
		if(choose2 == 1){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					int num1;
					out << "Table[ " << i + 1 << " ][ " << j + 1 << " ] : ";
					in >> num1;
					if(num1 == 0)
						arr1[i][j] = NULL;
					else
						arr1[i][j] = num1;
				}
			}
			Goal.SetBoxes(arr1);
		}else{
			int move;
			out << "Select max move(less than 60) : ";
			in >> move;
			if(move < 0)
				move = 0;
			else if(move > 60)
				move = 60;

			RandomMix(arr, move);
			Goal.SetBoxes(arr);
		}
		out << "Check Goal status : " << endl;
		Goal.Print(out);
		out << endl;

	}

	virtual bool IsValid() const{
		int arr[3][3], arr1[3][3];
		Start.GetBoxes(arr);
		Goal.GetBoxes(arr1);

		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++){

				if(arr[i][j] > 8 || arr[i][j] < 0)
					return false;

				if(arr1[i][j] > 8 || arr1[i][j] < 0)
					return false;

				for(int x = 0; x < 3; x++)
					for(int y = 0; y < 3; y++){
						if(i != x || j != y)
							if(arr[i][j] == arr[x][y])
								return false;

						if(arr[x][y] > 8 || arr[x][y] < 0)
							return false;
					}

				for(int x = 0; x < 3; x++)
					for(int y = 0; y < 3; y++){
						if(i != x || j != y)
							if(arr1[i][j] == arr1[x][y])
								return false;

						if(arr1[x][y] > 8 || arr1[x][y] < 0)
							return false;
					}
				
			}

		return true;
	}

	virtual void Process(ostream& out, istream& in){
		Node* p;
		int numOfNode = 0;
		int Mem = 0;
		clock_t begin, finish;

		//Choose stagegies
		out << "Choose stagegies : " << endl;
		out << "Press 01 : Using BFS - Breadth First Search. (The Worst) " << endl;
		out << "Press 02 : Using IDS - Iterative Deepening Search. (Fair)" << endl;
		out << "Press 03 : Using A* - Estimated Wrong Positions. (Good)" << endl;
		out << "Press 04 : Using IDA* - Iterative Deepening Wrong Positions. (Good)" << endl;
		out << "Press 05 : Using A* - Mahattan Distances. (Great)" << endl;
		out << "Press 06 : Using IDA* - Iterative Deepening Mahattan Distances.(Recommend)" << endl;


		do{
			out << "Choose : ";
			in >> Search_choose;
		}while(Search_choose < 1 || Search_choose > 6);

		PUZZLE_8 P(Start, Goal);

		begin = clock();

		switch(Search_choose){
		case 01:
			out << "Search BFS : " << endl;
			p = P.Search_BFS(numOfNode, Mem);
			Search_Name[Count_Process].append("BFS");
			break;

		case 02:
			out << "Search IDS : " << endl;
			p = P.Search_IDS(numOfNode);
			Search_Name[Count_Process].append("IDS");
			Mem = numOfNode;
			break;

		case 03:
			out << "Search A* Wrong Pos : " << endl;
			p = P.Search_A_Star_WrongPos(numOfNode, Mem);
			Search_Name[Count_Process].append("A* Wrong Pos Heuristic");
			break;

		case 04:
			out << "Search IDA* Wrong Pos : " << endl;
			p = P.Search_IDA_Star_WrongPos(numOfNode, Mem);
			Search_Name[Count_Process].append("Iterative Deepening A* Wrong Pos Heuristic");
			Mem = numOfNode;
			break;

		case 05:
			out << "Search A* Mahattan Dist : " << endl;
			p = P.Search_A_Star_Mahattan(numOfNode, Mem);
			Search_Name[Count_Process].append("A* Mahattan Distance Heuristic");
			break;

		case 06:
			out << "Search A* Mahattan Dist : " << endl;
			p = P.Search_IDA_Star_Mahattan(numOfNode, Mem);
			Search_Name[Count_Process].append("Iterative Deepening A* Mahattan Distance Heuristic");
			Mem = numOfNode;
			break;
		}

		if(p == NULL)
			out << "Answer is not found...!" << endl;
		else
			P.PrintAnswer(P.FindAnswer(p), P.FindMove(p), out);

		finish = clock();

		//Statitics Data
		Node_Created[Count_Process] = numOfNode;
		Time_Exe[Count_Process] = double(finish - begin) / CLOCKS_PER_SEC;
		Memory_Used[Count_Process] = long(Mem) * long(9 * sizeof(int));
		Count_Process++;
	}

	virtual void OutputProcess(ostream& out) const{
		out << "\n-----------------------------------------\n";
		out << "Time Execute : " << Time_Exe[Count_Process - 1] << " sec." << endl;
		out << "Node Compared : " << Node_Created[Count_Process - 1] << " (nodes)." << endl;
		out << "Node Created : " << Memory_Used[Count_Process - 1] / (9 * sizeof(int)) << " (nodes)." << endl;
		out << "Memory used : " << Memory_Used[Count_Process - 1] << " Byte" << endl;
		out << "              " << double(Memory_Used[Count_Process - 1]) / 1000.0 << " KB" << endl;
		out << "              " << double(Memory_Used[Count_Process - 1]) / 1000000.0 << " MB" << endl;
		out << "\n-----------------------------------------\n";
	}

	virtual void Output(ostream& out) const{
		out << "\n\n--------------------OUTPUT-------------------:" << endl << endl;

		out << "Start Status : " << endl << endl;
		Start.Print(out);

		out << "Goal Status : " << endl << endl;
		Goal.Print(out);

		for(int i = 0; i < Count_Process; i++){
			out << "\n-----------------------------------------\n";
			out << "\nStatitics Information of Trial " << i + 1 << " : " << endl;
			out << "Search Stagegy : " << Search_Name[i] << endl;
			out << "Time Execute : " << Time_Exe[i] << " sec." << endl;
			out << "Node Compared : " << Node_Created[i] << " (nodes)." << endl;
			out << "Node Created : " << Memory_Used[i] / (9 * sizeof(int)) << " (nodes)." << endl;
			out << "Memory used : " << Memory_Used[i] << " Byte" << endl;
			out << "              " << double(Memory_Used[i]) / 1000.0 << " KB" << endl;
			out << "              " << double(Memory_Used[i]) / 1000000.0 << " MB" << endl;
		}

		out << "\n-----------------------------------------\n";
	}

};

