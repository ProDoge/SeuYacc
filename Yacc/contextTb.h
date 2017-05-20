#pragma once
#include <map>
#include "conFreeGram.h"
/*
���ڴ洢�����﷨��
*/
class contextTb
{
private:
	vector<conFreeGram> Table;					//��¼���б��ʽ����
	vector<string> tokenTbl;						//��¼���е�token
	vector<string> exprTbl;							//��¼����expression
private:
	vector<string> getFirst4Update(string);	//����FirstMapʱʹ�õ�getFirst
public:
	vector<conFreeGram>			S;				//�ķ���߲�
	map<string, vector<int>>		exprMap;	//string��Left�ı��ʽ��ż���
	map<string,vector<string>>	FirstMap;	//�������Left��Ӧ��First
public:
	contextTb();
	contextTb(vector<string> tokens);
	conFreeGram get(int id);							//��ȡ��Լ����
	vector<string> getTokenTbl();
	vector<string> getExprTbl();
	vector<string> getFisrt(string);				//FirstMap�ⲿ�ӿ�
	void updateFirstMap();
	void insert(string L, string R);
	void createFirstTb();
	int	 judgeTorE(string s);							//�ж���Token(����0)����Expression(����1),error(-1)
};