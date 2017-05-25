#include "LrTable.h"
#include <iostream>
#include <fstream>
using namespace std;
LrTable::LrTable(contextTb conTb)
{
	Tbl = conTb;
	LRTbl.push_back(LrState(conTb.S, conTb));
	map<string, int> jumpM;
	int maxID = 1;
	ofstream SaveFile("out.txt");
	ofstream SaveFile2("jumpout.txt");
	SaveFile.clear();
	SaveFile2.clear();
	for (int i = 0; i < LRTbl.size(); i++)//LRTbl��ѭ����sizeҲ�ڲ��ϵĸ���
	{
		SaveFile << "State:  " << i << endl;

		for (int j = 0; j < LRTbl[i].context.size(); j++)
		{
			SaveFile<< LRTbl[i].Dot[j] << '\t';
			for (int k = 0; k < LRTbl[i].Follow[j].size(); k++)
				SaveFile << LRTbl[i].Follow[j][k] << "  ";
			SaveFile << endl;
			SaveFile << LRTbl[i].context[j] << endl;
		}
		SaveFile << endl;
		SaveFile << endl;
		SaveFile << endl;

		jumpM.clear();
		//������ȱ���
		for (int j = 0; j < LRTbl[i].StateNext.size(); j++)
		{
			string currS = LRTbl[i].StateNext[j];
			int position = -1;
			LrState newState(LRTbl[i], currS, conTb);
			for (int k = 0; k < LRTbl.size(); k++)
			{
				if (LRTbl[k] == newState)
				{
					position = k;//�����ظ���Ͱ�ָ��ָ��ǰλ��
					break;
				}
			}
			if (position >= 0)//�����ظ���
				jumpM.insert(pair<string, int>(currS, position));
			else
			{
				LRTbl.push_back(newState);
				jumpM.insert(pair<string, int>(currS, LRTbl.size() - 1));
			}
		}
		jumpMap.push_back(jumpM);
	}
	SaveFile.close();
	createActGoto();
	map<string, int>::iterator it;
	for (int i = 0; i < jumpMap.size();i++)
	{
		SaveFile2 << "State:   " << i << endl;
		for (it = jumpMap[i].begin(); it != jumpMap[i].end(); it++)
		{
			SaveFile2 << (*it).first << "    " << (*it).second<<endl;
		}
		SaveFile2 << endl << endl << endl;
	}
	SaveFile2.close();
}

void LrTable::createActGoto()
{
	map<string, pair<int, int>> newMap;
	for (int i = 0; i < jumpMap.size(); i++)
	{
		newMap.clear();
		map<string, int>::iterator it = jumpMap[i].begin();
		for(;it!=jumpMap[i].end();it++)						//����
			newMap.insert(pair<string, pair<int, int>>(it->first, pair<int, int>(0, it->second)));
		for(int j=0;j<LRTbl[i].size();j++)					//LR i �ĵ� j ������,����������һ��ǰ��
			if (LRTbl[i].ifEnd(j))										//��Լ
			{
				for (int k = 0; k < LRTbl[i].Follow[j].size(); k++)
					if (newMap.count(LRTbl[i].Follow[j][k]) > 0)//�����Լ��ͻ����
					{
						if (handleConflict(LRTbl[i].context[j].getNumber(), LRTbl[i].Follow[j][k]))
							newMap[LRTbl[i].Follow[j][k]] = pair<int, int>(1, LRTbl[i].context[j].getNumber());
					}
					else
						newMap.insert(pair<string, pair<int, int>>(LRTbl[i].Follow[j][k], pair<int, int>(1, LRTbl[i].context[j].getNumber())));
			}
		if (LRTbl[i].ifEnd(0) && Tbl.S[0] == LRTbl[i].context[0])
		{
			if (newMap.count(terminal) == 0)
				newMap.insert(pair<string, pair<int, int>>(terminal, pair<int, int>(2, 0)));
			else
				newMap[terminal] = pair<int, int>(2, 0);
		}
		ActGoto_Tbl.push_back(newMap);
	}
}

bool LrTable::handleConflict(int i, string s)
{
	pair<int, int> x1, x2;
	x1 = Tbl.getAssociation(i);
	x2 = Tbl.getAssociation(s);
	if (x1.first != x2.first)
	{
		cout << "context " << i << "  and  string " << s << "  cannot be compared"<<endl;
		return true;
	}
	if (x1.first == 2)//����
		return x1 > x2 ? true : (x1 == x2 ? true:false);
	else if (x1.first == 1)//�����
		return x1 > x2 ? true : false;
	return true;
}

vector<string> LrTable::getToken()
{
	return Tbl.getTokenTbl();
}

vector<string> LrTable::getExpr()
{
	return Tbl.getExprTbl();
}

void LrTable::Output()
{
	for (int i = 0; i < LRTbl.size(); i++)
	{
		cout << "state " << i << endl;
		for (int j = 0; j < LRTbl[i].context.size(); j++)
		{
			cout << LRTbl[i].Dot[j]<<'\t';
			for (int k = 0; k < LRTbl[i].Follow[j].size(); k++)
				cout << LRTbl[i].Follow[j][k] << "  ";
			cout << endl;
			cout << LRTbl[i].context[j] << endl;
		}
		cout << endl;
		cout << endl;
	}
}
