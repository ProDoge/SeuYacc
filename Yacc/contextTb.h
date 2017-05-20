#pragma once
#include <map>
#include "conFreeGram.h"
/*
用于存储整张语法表
*/
class contextTb
{
private:
	vector<conFreeGram> Table;					//记录所有表达式规则
	vector<string> tokenTbl;						//记录所有的token
	vector<string> exprTbl;							//记录所有expression
private:
	vector<string> getFirst4Update(string);	//更新FirstMap时使用的getFirst
public:
	vector<conFreeGram>			S;				//文法最高层
	map<string, vector<int>>		exprMap;	//string在Left的表达式序号集合
	map<string,vector<string>>	FirstMap;	//获得所有Left对应的First
public:
	contextTb();
	contextTb(vector<string> tokens);
	conFreeGram get(int id);							//获取规约规则
	vector<string> getTokenTbl();
	vector<string> getExprTbl();
	vector<string> getFisrt(string);				//FirstMap外部接口
	void updateFirstMap();
	void insert(string L, string R);
	void createFirstTb();
	int	 judgeTorE(string s);							//判断是Token(返还0)还是Expression(返还1),error(-1)
};