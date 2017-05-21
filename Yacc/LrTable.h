#pragma once
#include "contextTb.h"
#include "LrState.h"
class LrTable
{
private:
	vector<LrState>	LRTbl;
public:
	contextTb				Tbl;												//��¼���ж���������
	vector<map<string, int>>					jumpMap;			//��¼LrTblÿ��״̬����ת������Goto����
	vector<map<string, pair<int, int>>> ActGoto_Tbl;		/*string��Ӧtoken����exprssion��pair�е�
																					һ��int��0����/1��Լ���ڶ���Ϊ��תĿ���
																					��Լ����*/
public:
	LrTable(contextTb conTb);		//���ù�����contextTb������ȱ�������LR��1����
	void createActGoto();				/*����GOTO��ͬʱ�Բ�������ı�ʶ������ע�������Լ��ͻ�Ĵ�
												��*/

	bool handleConflict(int i,string s);		//��i���ķ��͵�j���ķ������ȼ�/���ҽ���ж�,true��ʾ��Լ
	vector<string>		getToken();
	vector<string>		getExpr();
	void Output();
};