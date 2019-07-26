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

vector<int> File::search(const string key)
{
	vector<int> ID;
	vector<int> occu;
	int lenght = key.length();
	TrieNode *pCrawl = root2;
	for (int level = 0; level < lenght; level++)
	{
		int index;
		if (find_slot(index, level, key)) {
			if (pCrawl->children[index] == nullptr)
				return occu;
			pCrawl = pCrawl->children[index];
		}
	}
	if (pCrawl != nullptr && pCrawl->isEnd) {
		int vec_size = pCrawl->file_ID.size();
		for (int i = 0; i < vec_size; i++) {
			if (ID.empty() || ID.back() != pCrawl->file_ID[i]) {
				ID.push_back(pCrawl->file_ID[i]);
				occu.push_back(1);
			}
			else
			{
				occu.back() += 1;
			}
		}
	}
	int arr_size = ID.size();
	mergeSort(occu, ID, 0, arr_size - 1);
	return occu; // does it work ?
	//need more code to return





}

bool File::isLastNode(TrieNode* root2)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root2->children[i] != nullptr)
			return 0;
	return 1;
}

void File::suggestionsRec(TrieNode * root2,string currPrefix) {
	if (root2->isEnd)
	{
		cout << currPrefix << endl;
		cout << endl;
	}
	if (isLastNode(root2))
	{
		return;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root2->children[i])
		{
			currPrefix.push_back(97 + i);
			suggestionsRec(root2->children[i], currPrefix);
		}
	}
}

int File::AutoSuggestions(string query)
{
	TrieNode *pCrawl = root2;
	int lenght = query.length();
	for (int level = 0; level < lenght; level++)
	{
		int index;
		if (find_slot(index, level, query) && !pCrawl->children[index])//problem ?
		{
			return 0;
		}
		pCrawl = pCrawl->children[index];
	}



	bool isWord = (pCrawl->isEnd == true);
	bool isEnd = isLastNode(pCrawl);

	if (isWord && isEnd)
	{
		cout << query << endl;
		return -1;
	}
	if (!isEnd)
	{

		suggestionsRec(pCrawl, query);
		return 1;
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
	return false;
}

string File::convert_word(string key) {
	int leng = key.length;
	string done;
	int index;
	for (int i = 0; i < leng; i++) {
		if (find_slot(index, i, key)) {
			done += char(index);
		}
	}
	return done;
}

void File::merge(vector<int>arr,vector<int> ID, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int* L = new int[n1];
	int* L_ID = new int[n1];
	int* R = new int[n2];
	int* R_ID = new int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++) {
		L[i] = arr[l + i];
		L_ID[i] = ID[l + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = arr[m + 1 + j];
		R_ID[j] = ID[m + 1 + j];
	}

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] >= R[j])
		{
			arr[k] = L[i];
			ID[k] = L_ID[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			ID[k] = R_ID[i];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		ID[k] = L_ID[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		ID[k] = R_ID[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void File::mergeSort(vector<int>arr, vector<int> ID, int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr,ID, l, m);
		mergeSort(arr,ID, m + 1, r);

		merge(arr,ID, l, m, r);
	}
}