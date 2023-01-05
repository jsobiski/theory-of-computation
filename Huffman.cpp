#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node
{
	char ch;
	int freq;
	Node* left;
	Node* right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void HuffmanCode(string text)
{
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> queue;

	for (auto leaf : freq) {
		queue.push(getNode(leaf.first, leaf.second, nullptr, nullptr));
	}

	while (queue.size() != 1)
	{
		Node* left = queue.top(); queue.pop();
		Node* right = queue.top();	queue.pop();

		int sum = left->freq + right->freq;
		queue.push(getNode('0', sum, left, right));
	}

	Node* root = queue.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	
	char order[100][100];

	ofstream output;
	output.open("codetable.txt");
	
	for (auto leaf : huffmanCode) {
		output << leaf.first << " = " << leaf.second << endl;
	}
	
	output.close();
}

int main()
{
	ifstream input;
	input.open("freq.txt");
	
	string text;
	string read;
	
	while (getline(input, read))
		text += read;

	input.close();

	HuffmanCode(text);

	return 0;
}