#pragma once
#include "contextTb.h"
#include "conFreeGram.h"
#include<map>
const string terminal = "$";
class LrState
{
private:
	vector<int> extend;									//��չ��flag
	vector<conFreeGram> context;					//����ʱ��֤��conFreeGram��˳��
	vector<int> Dot;										//��ǰ���λ��
public:
	vector<string> StateNext;							//״̬����һ����������п�����,contextNext�Ĳ���
	vector<vector<string>> Follow;					//Follow�ַ�
	map<string, vector<int>> contextNext;		//��һ�����������Ӧ�ı��ʽ�ļ���
public:
	LrState(LrState s, string input, contextTb tb);
	LrState(vector<conFreeGram>, contextTb tb);
	void updateFollow(vector<string> s, int pos);//s��Follow[pos]�ϲ�
	void updateNext(contextTb tb);					//��contextNext��StateNext�ĸ���
	bool operator==(const LrState&);
};