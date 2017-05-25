#ifndef INPUTFILEPROCESS_H
#define INPUTFILEPROCESS_H
#include<iostream>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "contextTb.h"
using namespace std;
#define ERROR -1//����ERROR��״̬���Ϊ-1
#define BEGIN 1//����BEGIN��״̬���Ϊ-1
#define END 2//����END��״̬���Ϊ-1
#define LAYER 3//����LAYER��״̬���Ϊ-1

class InputFileProcess
{
public:
	ifstream ifile;
	ofstream ofile;
	int state;//�������ͱ�����ʾ״̬���
	string InputFileName;
	string OutputFileName;
	vector <string> tokenTb;
	vector <pair<string, string>> paraTb;
	map < string, int> nonassocTb;
	map <string, int> leftTb;
	vector<pair<string, vector<string>>> ruleTb;
	void OpenInOutFile();//����������ļ�
	int check(char ch);//��⵱ǰλ�ڡ�%����ķ���������״̬���
	void DefinitionOutput(char &ch);//˵���������ݽ�������
	int StringCountCh(string &str, char ch);//�����ַ���str���ַ�ch���ֵĸ���
	contextTb RuleProcess();//�������ִ�����
	void UserProOutput(char &ch);//�û��ӳ��������������
};
#endif