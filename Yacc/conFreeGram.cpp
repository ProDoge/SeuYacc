#include "conFreeGram.h"

conFreeGram::conFreeGram(string readL, string readR, int Num)
{
	Number = Num;
	/*�޸�����д�����*/
	left = readL;
	/*�޸�����д���ұ�*/
	while (true)
	{
		int offset = readR.find_first_of('\t');//Ѱ���״γ��ֵĿո�
		if (offset < 0) break;//�Ҳ����ո�
		while (offset == 0)//���ַ�Ϊ�ո�ѭ���ҵ���һ����Ϊ�ո���ַ�
		{
			readR = readR.substr(offset + 1, readR.length() - offset);
			offset = readR.find_first_of('\t');
		}
		if (offset == readR.length() - 1)//���һ���ַ�Ϊ�ո�
		{
			readR = readR.substr(0, readR.length() - 1);
			break;
		}
		else//�ҵ���һ���ո񣬽��ַ����Դ˿ո�Ϊ���޷ֿ�
		{
			right.push_back(readR.substr(0, offset));
			while (readR[offset] == '\t') offset++;
			readR = readR.substr(offset, readR.length() - offset);
		}
	}
	right.push_back(readR);
}

string conFreeGram::getLeft()
{
	return left;
}

vector<string> conFreeGram::getRight()
{
	return right;
}

int conFreeGram::getNumber()
{
	return Number;
}

bool operator==(const conFreeGram &l, const conFreeGram &r)
{
	return l.Number==r.Number;
}

bool operator<(const conFreeGram &l, const conFreeGram &r)
{
	return  l.Number < r.Number;
}

bool operator>(const conFreeGram &l, const conFreeGram &r)
{
	return  l.Number > r.Number;
}

ostream & operator<<(ostream & out, const conFreeGram & con)
{
	// TODO: �ڴ˴����� return ���
	out << con.left << " -> ";
	for (int i = 0; i < con.right.size(); i++)
		out << con.right[i]<<'\t';
	return out;
}
