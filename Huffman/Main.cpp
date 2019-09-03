#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <bits/stdc++.h> 

using namespace std;

class Node{
public:
	char ch;
	int freq;
	Node(char ch,int freq){
		this->freq=freq;
		this->ch=ch;
	}

	Node(){
		ch=' ';freq=0;
	}
};

class Node_Compare{
public:
	bool operator()(Node a,Node b){
		return a.freq<b.freq;
	}
};

//Use this function only to view to view if the map is created properly or not;
//don't include in actual code
void print_map(unordered_map<char,int> m){
	unordered_map<char,int>:: iterator itr;
	for(itr=m.begin();itr!=m.end();itr++)
		cout<<itr->first<<" "<<itr->second<<endl;
}

void create_Nodes(unordered_map<char,int> m,Node* arr){
	int l=m.size();

	int i=0;
	unordered_map<char,int>:: iterator itr;
	for(itr=m.begin();itr!=m.end();itr++){
		arr[i].ch=itr->first;arr[i++].freq=itr->second;
	}

	//return arr;
}

void create_map(std::unordered_map<char,int> &map){
	string file_path="";	
	cout<<"Enter path of file: ";
	getline(cin,file_path);

	ifstream ob;
	ob.open(file_path);
	//Execute if the file opened successfully
	if(!ob){
		cout<<"File couldn't be opened!"<<endl;
		return ;
	}

	//If file opened 
	while(!ob.eof()) {
	    /* code */
	    char c=ob.get();

	    //if character is not present in map, insert it
	    if(map.find(c)==map.end())
	    	map[c]=0;

	    //If character is already present then increment it's count by 1
	    map[c]++;
	}

	ob.close();

}

void create_pq(std::priority_queue<Node,vector<Node>,Node_Compare> &pq,Node* arr,int l){
	for(int i=0;i<l;i++)
		pq.push(arr[i]);
}

int main(int argc, char const *argv[])
{
	unordered_map<char,int> map;
	create_map(map);
	//print_map(*map);

	Node arr[map.size()];
	create_Nodes(map,arr);

	for(Node n : arr)
		cout<<n.ch<<" "<<n.freq<<endl;

	int l=map.size();
	priority_queue<Node,vector<Node>,Node_Compare> pq;
	create_pq(pq,arr,l);

	return 0;
}
