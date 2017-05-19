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
	}
	createActGoto();
}

void LrTable::createActGoto()
{

}

vector<string> LrTable::getToken()
{
	return Tbl.getTokenTbl();
}

vector<string> LrTable::getExpr()
{
	return Tbl.getExprTbl();
}
