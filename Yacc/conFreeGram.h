#pragma
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
	conFreeGram(string readL, string readR,int Num);
	string getLeft();										//��ȡ���
	vector<string> getRight();						//��ȡ�Ҳ�
	int getNumber();									//��ȡ���
	bool operator==(const conFreeGram&);
	bool operator<(const conFreeGram&);
	bool operator>(const conFreeGram&);
};