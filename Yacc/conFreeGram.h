#pragma once
#include <vector>
#include <string>
using namespace std;
/*
	���ڴ洢һ�й�Լ����
*/
class conFreeGram
{
private:
	int Number;
	string left;
	vector<string> right;
public:
	conFreeGram();
	conFreeGram(string readL, string readR,int Num);
	string getLeft();										//��ȡ���
	vector<string> getRight();						//��ȡ�Ҳ�
	int getNumber();									//��ȡ���
	friend bool operator==(const conFreeGram&, const conFreeGram&);
	friend bool operator<(const conFreeGram&, const conFreeGram&);
	friend bool operator>(const conFreeGram&, const conFreeGram&);
};