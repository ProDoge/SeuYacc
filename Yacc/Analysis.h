#include<vector>
#include<map>
#include<iostream>
#include "LrTable.h"
using namespace std;

class Analysis
{
public:
	contextTb Tbl;
	vector<map<string, pair<int, int>>> ActGoto;  /*actiongoto��string��Ӧtoken������expression
												  pair�е�һ��intΪ0��ʾ�ƽ���Ϊ1��ʾ��Լ,
												  �ڶ���Ϊ��תĿ������ǹ�Լ����*/
	vector<string> token;           
	vector<string> expression;                //���ս��S��T��
	int istoken(string);               //�жϵ�ǰ�ַ��ǲ����ս��
	string file;                                          //�﷨������������ļ�
	Analysis(vector<map<string, pair<int, int>>> A, vector<string> t, vector<string> e,string f,contextTb tb)
	{
		Tbl = tb;
		ActGoto = A;
		token = t;
		expression = e;
		file = f;
	};
	int FindNextstate(int, string);       //����ֵ��������ǰ״ֵ̬(int)��f���ս��(string),������һ��״̬����û�¸�״̬����-1��ʾerror
	void output();            //����﷨��������
};

