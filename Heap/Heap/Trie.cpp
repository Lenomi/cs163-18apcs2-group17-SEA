#include "header.h"

void File::insert_Node(string key, int ID)
{
	if (root2 == nullptr)
	{
		root2 = new TrieNode;
		root2->isEnd = false;
		for (int i = 0; i < ALPHABET_SIZE; i++)
			root2->children[i] = nullptr;
	}
	TrieNode* pCrawl = root2;
	for (int level = 0; level < key.length(); level++)
	{
		int index;
		if (find_slot(index, level, key)) {
			if (pCrawl->children[index] == nullptr)
			{
				pCrawl->children[index] = new TrieNode;
				pCrawl->children[index]->isEnd = false;
				for (int i = 0; i < ALPHABET_SIZE; i++)
					pCrawl->children[index]->children[i] = nullptr;
			}
			pCrawl = pCrawl->children[index];
		}
	}
	pCrawl->isEnd = true;
	pCrawl->file_ID.push_back(ID);
}

// searching a word 

bool File::search(const string key, vector<int>& ID, vector<int>& occu, int mode)
{
	int lenght = key.length();
	TrieNode *pCrawl = root2;
	for (int level = 0; level < lenght; level++)
	{
		int index;
		if (find_slot(index, level, key)) {
			if (pCrawl->children[index] == nullptr)
				return false;
			pCrawl = pCrawl->children[index];
		}
	}
	if (pCrawl != nullptr && pCrawl->isEnd) {
		int vec_size;
		int ID_size;
		int ID_loca;
		bool found;
		vector<int> ID_temp;
		vector<int> occu_temp;
		int temp_size;
		int temp_loca=0;
		switch (mode) {
		case(1):	//AND
			ID_size = ID.size();
			if (ID_size == 0)
				return false;
			found = false;
			vec_size = pCrawl->file_ID.size();
			for (int vec_loca = 0; vec_loca < vec_size; vec_loca++) {
				if (ID_temp.empty() || ID_temp.back() != pCrawl->file_ID[vec_loca]) {
					ID_temp.push_back(pCrawl->file_ID[vec_loca]);
					occu_temp.push_back(1);
				}
				else
				{
					occu_temp.back() += 1;
				}
			}
			temp_size = ID_temp.size();
			for (ID_loca = 0; ID_loca < ID_size; ID_loca++) {
				for (int j = temp_loca; j < temp_size; j++) {
					if (ID[ID_loca] == ID_temp[j]) {
						occu[ID_loca] = occu[ID_loca] * occu_temp[j];
						found = true;
						temp_loca = j + 1;
						break;
					}
				}
				if (found) {
					found = false;
				}
				else {
					ID.erase(ID.begin() + ID_loca);
					ID_size--;
					occu.erase(occu.begin() + ID_loca);
				}
			}

			





			/*found = false;
			vec_size = pCrawl->file_ID.size();
			ID_size = ID.size();
			if (ID_size == 0)
				return false;
			ID_loca = 0;
			for (int vec_loca = 0; vec_loca < vec_size; vec_loca++) {
				for (int j = ID_loca; j < ID_size; j++) {
					if (pCrawl->file_ID[vec_loca] == ID[j]) {
						occu[j]++;
						ID_loca = j;
						found = true;
						break;
					}
				}
			}
			if (!found) {
				ID.clear();
				occu.clear();
			}*/
			break;
		case(2):	//OR also find exact ????
			vec_size = pCrawl->file_ID.size();
			ID_size = ID.size();
			ID_loca = 0;
			for (int vec_loca = 0; vec_loca < vec_size; vec_loca++) {
				while (ID_loca < ID_size) {
					if (pCrawl->file_ID[vec_loca] == ID[ID_loca]) {
						occu[ID_loca]++;
						break;
					}
					else {
						ID_loca++;
					}
				}
				if (ID_loca >= ID_size) {
					if (ID.empty() || ID.back() != pCrawl->file_ID[vec_loca]) {
						ID.push_back(pCrawl->file_ID[vec_loca]);
						occu.push_back(1);
					}
					else
					{
						occu.back() += 1;
					}
				}
			}
			break;
		case(3):	//Dau -
			vec_size = pCrawl->file_ID.size();
			ID_size = ID.size();
			if (ID_size == 0)
				return true;
			ID_loca = 0;
			for (int vec_loca = 0; vec_loca < vec_size; vec_loca++) {
				if (vec_loca > 0 && pCrawl->file_ID[vec_loca] == pCrawl->file_ID[vec_loca - 1]) {
					continue;
				}
				for (int j = ID_loca; j < ID_size; j++) {
					if (pCrawl->file_ID[vec_loca] == ID[j]) {
						ID.erase(ID.begin()+j);
						occu.erase(occu.begin()+j);
						ID_loca = j;
						ID_size--;
						break;
					}
				}
			}
			break;
		}
		


		return true; // does it work ?
		//need more code to return
	}
}

bool File::isLastNode(TrieNode* root2)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root2->children[i] != nullptr)
			return 0;
	return 1;
}

bool File::suggestionsRec(TrieNode * root2,string currPrefix,string &ans) {
	if (root2->isEnd)
	{
		cout << currPrefix << endl;
		cout << endl;
		ans = currPrefix;
		return true;
	}
	if (isLastNode(root2))
	{
		ans = currPrefix;
		return true;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root2->children[i])
		{
			currPrefix.push_back(97 + i);
			if(suggestionsRec(root2->children[i], currPrefix,ans)) return true;
		}
	}
	return false;
}

string File::AutoSuggestions(string query)
{

	TrieNode *pCrawl = root2;
	int lenght = query.length();
	for (int level = 0; level < lenght; level++)
	{
		int index;
		if (find_slot(index, level, query) && !pCrawl->children[index])//problem ?
		{
			return query;
		}
		pCrawl = pCrawl->children[index];
	}



	bool isWord = pCrawl->isEnd;
	bool isEnd = isLastNode(pCrawl);

	if (isWord) {
		return query;
	}
	if (isWord && isEnd)
	{
		cout << query << endl;
		return query;
	}
	if (!isEnd)
	{
		string ans;
		if (suggestionsRec(pCrawl, query,ans))
			return ans;
	}


}

bool File::find_slot(int &index, int level, string key) {
	if (key[level] >= 97 && key[level] <= 122) {
		index = key[level] - 'a';
		return true;
	}
	else if (key[level] >= 65 && key[level] <= 90) {
		index = key[level] - 'A';
		return true;
	}
	else if (key[level] <= 57 && key[level] >= 48) {
		index = key[level] - 22;
		return true;
	}
	else if (key[level] == 35 || key[level] == 36) {
		index = key[level] + 2;
		return true;
	}
	return false;
}

string File::convert_word(string key) {
	int leng = key.length();
	string done;
	int index;
	for (int i = 0; i < leng; i++) {
		if (find_slot(index, i, key)) {
			done += char(index);
		}
	}
	return done;
}


// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void File::heapify(vector<int> &occu, vector<int> &ID, int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && occu[l] > occu[largest]) {
		largest = l;
	}

	// If right child is larger than largest so far 
	if (r < n && occu[r] > occu[largest]) {
		largest = r;
	}

	// If largest is not root 
	if (largest != i)
	{
		swap(occu[i], occu[largest]);
		swap(ID[i], ID[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(occu, ID,n, largest);
	}
}

// main function to do heap sort 
void File::heapSort(vector<int> &occu,vector<int> &ID, int n)
{
	// Build heap (reoccuange occuay) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(occu,ID, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(occu[0], occu[i]);
		swap(ID[0], ID[i]);

		// call max heapify on the reduced heap 
		heapify(occu,ID, i, 0);
	}
}

void File::ranking(vector<string>& vec_fileNames, string query1, vector<int>& ID) {
	string l = query1;
	vector<string> query;
	string word = "";
	for (auto x : l)
	{
		if (x == ' ')
		{
			query.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	query.push_back(word);

	vector<int> occu;
	int mode = 0;
	int query_size = query.size(), a = 0;
	bool *searched = new bool[query_size];
	for (int i = 0; i < query_size; i++) {
		searched[i] = false;
	}
	// phan tich cu phap o day ....

	// synosysms
	for (int i = 0; i < query_size; i++)
	{
		if (query[i][0] == '~')
		{
			query[i].erase(0,1);
			string z;
			string word1 = "";
			if (search_synonyms(query[i], z))
			{
				query[i].erase(0);
				query.pop_back();
				for (auto x : z)
				{
					if (x == ' ')
					{
						query.push_back(word1);
						word1 = "";
					}
					else
					{
						word1 = word1 + x;
					}
				}
				query.push_back(word1);
				query_size = query.size(), a = 0;
				searched = new bool[query_size];
				for (int i = 0; i < query_size; i++) {
					searched[i] = false;
				}
			}

		}
	}

	/*for (int i = 0; i < query_size; i++) // &200..$400
	{
		if (query[i] == "..")
		{
			a++;
			int pos = std::string::npos;
			while ((pos = query[i].find("&")) != std::string::npos)
			{
				query[i].erase(pos,1);
			}
			int pos1 = query[i].find("..");
			string sub = query[i].substr(0,pos1-1);
			string sub1 = query[i].substr(pos1+2);
			int l = std::stoi(sub);
			int r = std::stoi(sub1);
			// day no se chay tu 200 toi 400 de xem cai nao co
			for (int i = l; l <= r; l++)
			{
				string b = to_string(i);
				string a="&";
				a += b;
				search(a, ID, occu, 2); // Tai khuc nay lam cho no search theo kieu OR di
			}
			
		}
	}
	// The * in the world
	// phan nay t can m t se chi tung buoc


	*/
	for (int i = 0; i < query_size; i++)
	{
		if (query[i].find("intitle:") != string::npos)
		{
			int pos = query[i].find(":"), j = 0, l=-1;
			string sub = query[i].substr(pos + 1);
			for (int i = 0; i < vec_fileNames.size(); i++)
			{
				if (vec_fileNames[i] == sub)
				{
					ID.push_back(i+1);
					occu.push_back(50);
					l = i; //can use bool but whatever
					j = 1;
					break;
				}
			}
			for (int i = 0; i < vec_fileNames.size(); i++)
			{
				if (vec_fileNames[i].find(sub) != string::npos)
				{
					if (i != l) {
						ID.push_back(i + 1);
						occu.push_back(50);
					}
					j++;
				}
				if (j == 6) break;
			}
			searched[i] = true;
		}
		else if (query[i].find("filetype:txt") != string::npos)
		{
			for (int i = 0; i < 5; i++)
			{
				int k = rand() % 75 + 1; //change this
				ID.push_back(k);
				occu.push_back(1);
			}
			searched[i] = true;
		}
	}
	for (int i = 0; i < query_size; i++) {
		if (query[i] == "OR") {
			a++;
			searched[i] = true;
			if (!searched[i - 1] && query[i-1][0] != '-') {
				search(query[i-1], ID, occu, 2);
				searched[i - 1] = true;
			}
			if (!searched[i + 1] && query[i+1][0] != '-') {
				search(query[i+1], ID, occu, 2);
				searched[i + 1] = true;
			}
		}
	}
	for (int i = 0; i < query_size; i++) {
		if (query[i] == "AND" || query[i] == "+") {
			a++;
			searched[i] = true;
			if (!searched[i - 1] && !searched[i + 1]) {
				search(query[i - 1], ID, occu, 2);
				searched[i - 1] = true;
				search(query[i + 1], ID, occu, 1);
				searched[i + 1] = true;
			}
			else if (!searched[i - 1] || !searched[i + 1]) {
				if (!searched[i - 1]) {
					search(query[i - 1], ID, occu, 1);
					searched[i - 1] = true;
				}
				if (!searched[i + 1]) {
					search(query[i + 1], ID, occu, 1);
					searched[i + 1] = true;
				}
			}
		}
	}
	for (int i = 0; i < query_size; i++) {
		if (!searched[i] && query[i][0] != '-') {
			if (!a) {
				query[i] = AutoSuggestions(query[i]);
			}
			searched[i] = true;
			search(query[i], ID, occu, 2);
		}
	}
	for (int i = 0; i < query_size; i++) {
		if (query[i][0] == '-') {
			a++;
			searched[i] = true;
			search(query[i], ID, occu, 3);
		}
	}

	int arr_size = ID.size();// sap xep sau khi da tim xong
	heapSort(occu, ID,arr_size); //heap sort cho nhanh




}