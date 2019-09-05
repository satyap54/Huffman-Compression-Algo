#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>


using namespace std;

class Node{
public:
    char ch;
    int freq;
    Node *left;
    Node *right;
    string huff_code;

    Node(){
        ch=' ';freq=0;left=NULL;right=NULL;
    }
};

class Node_Compare{
public:
    bool operator()(Node* a,Node* b){
        return (a->freq)<(b->freq);
    }
};

//Use this function only to view to view if the map is created properly or not;
//don't include in actual code
void print_map(unordered_map<char,string> m){
    unordered_map<char,string>:: iterator itr;
    for(itr=m.begin();itr!=m.end();itr++)
        cout<<itr->first<<" "<<itr->second<<endl;
}

void create_Nodes(unordered_map<char,int> m,Node* arr[]){
    int l=m.size();

    int i=0;
    unordered_map<char,int>:: iterator itr;
    for(itr=m.begin();itr!=m.end();itr++){
        arr[i]->ch=itr->first;arr[i++]->freq=itr->second;
    }
}

void create_map(unordered_map<char,int> &map){
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

void create_pq(priority_queue<Node*,vector<Node*>,Node_Compare> &pq,Node* arr[],int l){
    for(int i=0;i<l;i++){
        //cout<<&arr[i]<<endl;
        pq.push(arr[i]);
    }
}

Node* create_tree(priority_queue<Node*,vector<Node*>,Node_Compare> &pq){
	while(pq.size()>1){
		cout<<"Pushing..."<<pq.size()<<endl;
		Node* par=new Node();

		Node* l=pq.top();pq.pop();//cout<<pq.size()<<endl;
		Node* r=pq.top();pq.pop();//cout<<pq.size()<<endl;
		par->freq=(l->freq)+(r->freq);par->left=l;par->right=r;

		pq.push(par);//cout<<pq.size()<<endl;
	}
	Node* res=pq.top();pq.pop();
	return res;
}

void tree_traverse(Node* node){
	if(node==NULL)
		return;
	tree_traverse(node->left);
	cout<<node->freq<<endl;
	tree_traverse(node->right);
}

void create_Huff_codes(Node *node,unordered_map<char,string> &huffman_codes,string h){

	if(node->right==NULL && node->left==NULL){
		huffman_codes[node->ch]=h;
		node->huff_code=h;
		cout<<"Huf!"<<endl;
		return;
	}

	if(node->left!=NULL){
		create_Huff_codes(node->left,huffman_codes,"0");
	}

	if(node->right!=NULL){
		create_Huff_codes(node->right,huffman_codes,"1");	
	}
}


int main(int argc, char const *argv[])
{
    unordered_map<char,int> map;
    create_map(map);int l=map.size();

    Node* arr[l];
    for(int i=0;i<l;i++)
        arr[i]=new Node();
    create_Nodes(map,arr);

    for(int i=0;i<l;i++)
     cout<<arr[i]<<" "<<arr[i]->ch<<" "<<arr[i]->freq<<endl;

    priority_queue<Node*,vector<Node*>,Node_Compare> pq;
    create_pq(pq,arr,l);
    Node* root=create_tree(pq);
    tree_traverse(root);

    map.clear();
    unordered_map<char,string> huffman_codes;string s="";
    create_Huff_codes(root,huffman_codes,s);cout<<endl;
    print_map(huffman_codes);

    return 0;
}
