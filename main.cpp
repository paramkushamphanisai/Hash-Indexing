/*
Skeleton code for linear hash indexing
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"
using namespace std;



vector <Record> record;


int main(int argc, char* const argv[]) {

    // Create the index
	fstream input_file;
	//input_file.open("Employee.csv", ios::in);
	LinearHashIndex linear("EmpIndex");
	linear.createFromFile("Employee.csv");
	/*while(true){
		Record  single_EmpRecord(Grab_Record(input_file));
		//cout<<single_EmpRecord.id;
		if(single_EmpRecord.id == -1) break;
		single_EmpRecord.print();
		linear.insertRecord(single_EmpRecord); 
		record.push_back(single_EmpRecord);
	}*/
	int id;
	cout<<"\n Give the emp Id "<<stoi(argv[1])<<"\n";
	//cin>>id;
	linear.findRecordById(stoi(argv[1]));

	//input_file.close();
    return 0;
}
