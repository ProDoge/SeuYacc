#pragma once
#include "contextTb.h"
#include "conFreeGram.h"
#include<map>
const string terminal = "$";
class LrState
{
private:
	vector<int> extend;									//��չ��flag
	vector<int> Dot;										//��ǰ���λ��
public:
	vector<conFreeGram> context;					//����ʱ��֤��conFreeGram��˳��
	vector<string> StateNext;							//״̬����һ����������п�����,contextNext�Ĳ���
	vector<vector<string>> Follow;					//Follow�ַ�
	map<string, vector<int>> contextNext;		//��һ�����������Ӧ�ı��ʽ�ļ���
public:
	LrState(LrState s, string input, contextTb tb);
	LrState(vector<conFreeGram>, contextTb tb);
	int size();
	int ContextSize(int id);
	int ifEnd(int id);											//�ж��ķ�[id]��Dot�Ƿ��ڽ�β
	void updateFollow(vector<string> s, int pos);//s��Follow[pos]�ϲ�
	void updateNext(contextTb tb);					//��contextNext��StateNext�ĸ���
	bool operator==(const LrState&);
};