#pragma once
#include "contextTb.h"
#include "LrState.h"
class LrTable
{
private:
	vector<LrState>	LRTbl;
	vector<string>		tokens;
	contextTb				ExprTbl;										//��¼��Լ����
public:
	vector<map<string, int>>					jumpMap;			//��¼LrTblÿ��״̬����ת������Goto����
	vector<map<string, pair<int, int>>> ActGoto_Tbl;		/*string��Ӧtoken����exprssion��pair�е�
																					һ��int��0��ת/1��Լ���ڶ���Ϊ��תĿ���
																					��Լ����*/
public:
	LrTable(contextTb conTb);		//���ù�����contextTb������ȱ�������LR��1����
	void createActGoto();				/*����GOTO��ͬʱ�Բ�������ı�ʶ������ע�������Լ��ͻ�Ĵ�
												��*/
};