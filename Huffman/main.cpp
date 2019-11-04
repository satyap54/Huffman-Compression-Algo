#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <bits/stdc++.h> 

using namespace std;

class Node{

	char ch;
	int freq;
	Node* left;//0 (left) subtree (NULL if empty)
	Node* right;//1 (right) subtree (NULL if empty)

	Node(){
		ch='$';
		freq=0;
		left=NULL;
		right=NULL;
	}
};

void buildFrequencyTable(unordered_map<char,int> &map){
	string file_path="";	
	cout<<"Enter path of file: ";
	getline(cin,file_path);

	ifstream ob;
	ob.open(file_path);
	//Execute if the file opened successfully
	try{
			if(!ob){
				throw 0;
		}
	}
	catch(...){
		cout<<"Error:Invalid file path/File doesn't exist"<<endl;
	}

	//If file opened 
	while(!ob.eof()) {
	    char c=ob.get();

	    //if character is not present in map, insert it
	    if(map.find(c)==map.end())
	    	map[c]=0;

	    //If character is already present then increment it's count by 1
	    map[c]++;
	}

	ob.close();

}

//Node* buildEncodingTree

//Functor to create min_heap
class Node_Compare{
public:
	bool operator()(Node a,Node b){
		return a.freq<b.freq;
	}
};

int main(int argc, char const *argv[])
{
	unordered_map<char,int> map;
	priority_queue<Node,vector<Node>,Node_Compare> pq;

	buildFrequencyTable(map);
	return 0;
}
