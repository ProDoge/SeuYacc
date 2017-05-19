#include "conFreeGram.h"

conFreeGram::conFreeGram(string readL, string readR,int Num)
{
	Number = Num;
	/*�޸�����д�����*/
	left = readL;

	/*�޸�����д���ұ�*/
	int size = 0, start = 0;
	for (int i = 0; i < readR.length(); i++)
	{
		if (readR[i] == ' ')
		{
			if(size!=0)
				right.push_back(readR.substr(start, size));
			size = 0;
			start = i + 1;
		}
		else
			size++;
	}
}

string conFreeGram::getLeft()
{
	return left;
}

vector<string> conFreeGram::getRight()
{
	return right;
}

bool conFreeGram::operator==(const conFreeGram &x)
{
	if (x.Number == Number)
		return true;
	else
		return false;
}

bool conFreeGram::operator<(const conFreeGram &x)
{
	if (x.Number < Number)
		return true;
	else
		return false;
}

bool conFreeGram::operator>(const conFreeGram &x)
{
	if (x.Number > Number)
		return true;
	else
		return false;
}
