#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <unordered_map>
using namespace std;

class Record {
public:
    int id, manager_id;
    std::string bio, name;
	Record(int num){
		id = -1;
        name = "-1";
        bio = "-1";
        manager_id = -1;
	}

    Record(vector<std::string> fields) {
        id = stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = stoi(fields[3]);
    }

    void print() {
        cout << "\tID: " << id << "\n";
        cout << "\tNAME: " << name << "\n";
        cout << "\tBIO: " << bio << "\n";
        cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class Block{
	public:
	vector <Record> record;
};

class LinearHashIndex {

private:
    const int PAGE_SIZE = 4096;
    int numBlocks; // n
    int i;
    int numRecords; // Records in index
    int nextFreePage; // Next page to write to
	int block_size;
	string fName;
	int hash;

    // Insert new record into index

	int hashfucnction(int n){
		return n%2*hash;
	}

	

public:
    LinearHashIndex(string indexFileName) {
        numBlocks = 0;
        i = 0;
        numRecords = 0;
        block_size = 0;
        fName = indexFileName;
		hash=2;
    }
	Block *pageDirectory;	
	unordered_map<int,Block> Page;
	//vector <Record> record;

	vector<std::string> Grab_Record(fstream &record) {
	string line, word;
	vector<std::string> fields;
    // grab entire line
    if (getline(record, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        fields.push_back(word);
        getline(s, word, ',');
        fields.push_back(word);
        getline(s, word, ',');
        fields.push_back(word);
        getline(s, word, ',');
        fields.push_back(word);
        return fields;
    } else {
        fields.push_back("-1");
		fields.push_back("-1");
		fields.push_back("-1");
		fields.push_back("-1");
        return fields;
    }
}
	int Increasehash(){
		pageDirectory = (Block *)malloc(PAGE_SIZE);
	}
	
	void insertRecordLinerar(Record record){
		int persentage= (numRecords/(8*hash))*100;//here i took 8 because 4096/516 ~ 8, the block should have 8 records
		if(persentage < 80){
			Page[hashfucnction(record.id)].record.push_back(record);
			numRecords++;
		}
		else{//if max size reached then increase the hash and
			hash++;
			rebuild();
			Page[hashfucnction(record.id)].record.push_back(record);
			numRecords++;
		}
		
	}

	void rebuild(){
		unordered_map<int,Block> tmp;
		for(auto x : Page){
			auto k=x.second.record;
			cout<<"\nRebuild\n";
			for (auto i = (x.second.record).cbegin(); i != (x.second.record).cend(); ++i){
				Record r(-1);
				r.id=(*i).id;
				r.name=(*i).name;
				r.bio=(*i).bio;
				r.manager_id=(*i).manager_id;
				tmp[hashfucnction(r.id)].record.push_back(r);
			}
		}
		Page=tmp;
	}

	void display(){
		
		for(auto x : Page){
			auto k=x.second.record;
			cout<<"\nDisplay\n";
			for (auto i = (x.second.record).cbegin(); i != (x.second.record).cend(); i++){
				cout<<"\nDisplay\n";
				cout << "\tID: " << (*i).id << "\n";
				cout << "\tNAME: " << (*i).name << "\n";
				cout << "\tBIO: " << (*i).bio << "\n";
				cout << "\tMANAGER_ID: " << (*i).manager_id << "\n";
			}
		}
		cout<<hash<<"\n";
	}
	
    // Read csv file and add records to the index
    void createFromFile(string csvFName) {
	fstream input_file;
	input_file.open(csvFName, ios::in);
	Increasehash();
	while(true){
		Record  single_EmpRecord(Grab_Record(input_file));
		//cout<<single_EmpRecord.id;
		if(single_EmpRecord.id == -1) break;
		//single_EmpRecord.print();
		insertRecordLinerar(single_EmpRecord); 
		}
		display();
		input_file.close();
    }


    // Given an ID, find the relevant record and print it
    void findRecordById(int id) {
		auto b=Page[hashfucnction(id)];
		for (auto i = (b.record).cbegin(); i != (b.record).cend(); i++){
			if((*i).id==id){
				cout << "\tID: " << (*i).id << "\n";
				cout << "\tNAME: " << (*i).name << "\n";
				cout << "\tBIO: " << (*i).bio << "\n";
				cout << "\tMANAGER_ID: " << (*i).manager_id << "\n";
				break;
			}
		}
    }
};
