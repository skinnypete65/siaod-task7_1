﻿#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

Node* getNode(char ch, int freq, Node* left, Node* right);
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);
void decode(Node* root, int& index, string str);
void buildHuffmanTree(string text);


int main()
{
	setlocale(LC_ALL, "Russian");
	string text = "Эне, бене, лики, паки, Цуль, буль - буль, Калики - цваки, Эусбеус, кликмадеус, бокс..";

	cout << "Задание 3:\n";
	buildHuffmanTree(text);

	return 0;
}

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

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

void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text)
{
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nИсходный текст:\n" << text << '\n';

	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nЗакодированная строка:\n" << str << '\n';

	int index = -1;
	cout << "\nДекодированная строка:\n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}