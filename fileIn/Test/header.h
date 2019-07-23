#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<cctype>
const int ALPHABET_SIZE = 36;

using namespace std;
struct Node
{
	int id, height;
	string data;
	Node* left, *right;
};
struct TrieNode
{
	TrieNode *children[ALPHABET_SIZE];
	bool isEnd;
	string key;
};
class File
{
private:
	Node* root;
	TrieNode* root2;
public:
	//AVL
	File() { root = nullptr; root2 = nullptr;}
	void Insert(int k, string a, Node*& root);
	int height(Node* a);
	int Balance(Node *a);
	void leftRotate(Node *&x);
	void rightRotate(Node *&x);
	Node* search(Node* root, int k);
	void openFiles(vector<string>& vec_fileNames);
	void loadFileNames(vector<string>& vec_fileNames);
	//trie
	void insert_Node(string key);
	bool search(const string key);
	bool isLastNode(TrieNode* root2);
	void suggestionsRec(TrieNode * root2, string currPrefix);
	int AutoSuggestions(string query);
	bool find_slot(int &index, int level, string key);
};

