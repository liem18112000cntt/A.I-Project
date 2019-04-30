#include "Program.h"

void Program::ErrorMessage(ostream& out) const{
	out << "Input data is INVALID...!" << endl;
	out << "Please try again...!" <<endl;
}

bool Program::IsContinue(ostream& out, istream& in) const{
	int i;
	out << "Press 1 to repeat PROGRAM or any key to end : ";
	in >> i;

	if(i == 1)
		return true;
	return false;
}

bool Program::IsRepeatProcess(ostream& out, istream& in) const{
	int i;
	out << "Warning : Program would re-use your Input" << endl;
	out << "Press 1 to repeat PROCESS or any key to end : ";
	in >> i;

	if(i == 1)
		return true;
	return false;
}

//Main operation
void Program::Run(ostream& out, istream& in){

	//Main loop
	do{
		//Step 1:
		StartMessage(out);

		//Valid Loop
		do{

			//Step 2:
			Input(out, in);

			//Step 3:
			if(!IsValid())
				ErrorMessage(out);
			
		}while(!IsValid());

		out << "Enter input successfully...!" << endl << endl;
		
		//Process Loop
		do{

			//Step 4:
			Process(out, in);
			OutputProcess(out);

		}while(IsRepeatProcess(out, in));// Step 5

		//Step 6: 
		Output(out);

	}while(IsContinue(out, in));// Step 7 + 8

	out << "Terminate program successfully...!" << endl << endl;
}