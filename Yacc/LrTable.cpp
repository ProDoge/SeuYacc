#include "LrTable.h"

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
				/*if (LRTbl[k] == newState)
				{
					position = k;//�����ظ���Ͱ�ָ��ָ��ǰλ��
					break;
				}*/
			}
			if (position >= 0)//�����ظ���
				jumpM.insert(pair<string, int>(currS, position));
			else
			{
				LRTbl.push_back(newState);
				jumpM.insert(pair<string, int>(currS, LRTbl.size() - 1));
			}
		}
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
			if(LRTbl[i].ifEnd(j))										//��Լ
				newMap.insert(pair<string, pair<int, int>>(*(LRTbl[i].context[j].getRight().end()-1), 
					pair<int, int>(1, LRTbl[i].context[j].getNumber())));
		if (LRTbl[i].ifEnd(0) && Tbl.S == LRTbl[i].context)	//�ķ��Ѿ�����Ԥ���� S->S'
			newMap.insert(pair<string, pair<int, int>>(terminal, pair<int, int>(2, 0)));
		ActGoto_Tbl.push_back(newMap);
	}
}

vector<string> LrTable::getToken()
{
	return Tbl.getTokenTbl();
}

vector<string> LrTable::getExpr()
{
	return Tbl.getExprTbl();
}
