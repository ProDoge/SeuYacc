#include "LrTable.h"
#include <iostream>
using namespace std;
LrTable::LrTable(contextTb conTb)
{
	Tbl = conTb;
	LRTbl.push_back(LrState(conTb.S, conTb));
	map<string, int> jumpM;
	int maxID = 1;
	for (int i = 0; i < LRTbl.size(); i++)//LRTbl��ѭ����sizeҲ�ڲ��ϵĸ���
	{
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
	createActGoto();
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
		if (LRTbl[i].ifEnd(0) && Tbl.S == LRTbl[i].context)	//�ķ��Ѿ�����Ԥ���� S->S'
			if (newMap.count(terminal) == 0)
				newMap.insert(pair<string, pair<int, int>>(terminal, pair<int, int>(2, 0)));
			else
				newMap[terminal] = pair<int, int>(2, 0);
		ActGoto_Tbl.push_back(newMap);
	}
}

bool LrTable::handleConflict(int i, string s)
{
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
