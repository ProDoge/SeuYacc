#include "InputFileProcess.h"
#include "conFreeGram.h"
#include "contextTb.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void InputFileProcess::OpenInOutFile()//����������ļ�
{
	ifile.open(InputFileName, ios::in);
	ofile.open(OutputFileName, ios::out);
	if (!ifile) {//�����ļ����ܴ�
		cerr << "Input file could not be opened" << endl;
		exit(1);
	}
	if (!ofile) {//�����ļ����ܴ�
		cerr << "Output file could not be opened" << endl;
		exit(1);
	}
}

int InputFileProcess::check(char ch)//��⵱ǰλ�ڡ�%����ķ���������״̬���
{
	if (ch == '{') {//�ǡ�{������ʾBEGIN
		return BEGIN;
	}
	else if (ch == '}') {//�ǡ�%}������ʾEND
		return END;
	}
	else if (ch == '%') {//�ǡ�%������ʾ���
		return LAYER;
	}
	else //�����������ž�������
	{
		ifile.seekg(-1, ios::cur);//���ļ��Ķ�ָ�뵹��һ��
	}
}

void InputFileProcess::DefinitionOutput(char &ch)//˵���������ݽ�������
{
	cout << "˵�����������ʼ!" << endl;
	//���ȰѸ������岿�����뵽�ļ���
	ch = ifile.get();//�������ļ�����һ���ַ�
	if (ch != '%') {//�����ļ����ַ����ǡ�%�����ţ�����ʾ�����ļ��ĸ�ʽ����ȷ
		cerr << "Input File don't have the correct format!" << endl;
		state = ERROR;//״̬ΪERROR����Ϊ-1
		exit(1);//�˳���ǰmain����
	}
	else {//�����ļ����ַ�Ϊ��%��
		ch = ifile.get();//��ȡ�����ļ�����һ���ַ�
		state = check(ch);//���ݵ�ǰ��ȡ���ַ�������state
		if (state != 1) {//���state����ʾBEGIN
			cerr << "Input File don't have the correct format!" << endl;
			state = ERROR;//״̬ΪERROR����Ϊ-1
			exit(1);//�˳���ǰmain����
		}
		else;
	}
	while (!ifile.eof() && state != 2) {//�����ļ�û�ж�����β����state������2����Ϊ��ΪEND״̬��%}��
		ch = ifile.get();//��ȡ�����ļ�����һ���ַ�
		if (ch == '%') {//��ǰ������ַ�Ϊ��%��
			char nextch = ifile.get();//��ȡ�����ļ�����һ���ַ�
			state = check(nextch);//���ݵ�ǰ��ȡ���ַ�������state
		}
		else ofile.put(ch);//����ȡ���ַ���������ļ���
	}
	string line;
	int offset;
	int level = 0;
	int priority = 0;
	getline(ifile, line);
	while (line != "%%")
	{
		if (line.length() == 0)
		{
			line.clear();
			getline(ifile, line);
		}
		else
		{
			if (line[0] == '%')
			{
				if (line[1] == 'u')//�������岿��
				{
					for (int i = 1; i < line.length(); i++)
					{
						ofile.put(line[i]);
					}
					line.clear();
					getline(ifile, line);
				}
				else if (line[1] == 't'&&line[2] == 'o')//����token����
				{//����%token��������
					string str;
					str.clear();
					for (int i = 7; i < line.length(); i++)
					{

						if (line[i] == ' ')
						{
							tokenTb.push_back(str);
							str.clear();
						}
						else if (i == line.length() - 1)
						{
							str.append(1, line[i]);
							tokenTb.push_back(str);
						}
						else
						{
							str.append(1, line[i]);
						}
					}
					line.clear();
					getline(ifile, line);
				}
				else if (line[1] == 't'&&line[2] == 'y')//����type����
				{//����%type��������
					string str, temp;
					str = line.substr(6, line.length() - 6);
					string typevar;
					offset = str.find_first_of('\t');//Ѱ���״γ��ֵĿո�
					typevar = str.substr(1, offset - 2);
					while (str[offset] == '\t') offset++;
					temp = str.substr(offset, str.length() - offset);
					str = temp;
					while (true)
					{
						offset = str.find_first_of(" ", 1);//Ѱ���״γ��ֵĿո�
						if (offset < 0) break;
						if (offset == str.length() - 1)
						{
							str = str.substr(0, str.length() - 1);
							break;
						}
						else
						{
							paraTb.push_back(pair<string, string>(str.substr(0, offset), typevar));
							temp = str.substr(offset + 1, str.length() - offset);
							str = temp;
						}
					}
					paraTb.push_back(pair<string, string>(str, typevar));
					typevar.clear();
					str.clear();
					line.clear();
					getline(ifile, line);
				}
				else if (line[1] == 'n')//�����޽���Ե������nonassoc
				{
					offset = line.find_first_of('\t');//Ѱ���״γ��ֵĿո�
					while (line[offset] == ' ') offset++;
					nonassocTb.insert(pair<string, int>(line.substr(offset + 1, line.length() - offset),level));
					level++;
					offset = 0;
					line.clear();
					getline(ifile, line);
				}
				else if (line[1] == 'l')//���������Ե������left����
				{
					offset = line.find_first_of('\t');//Ѱ���״γ��ֵĿո�
					while (line[offset] == '\t') offset++;
					string op, temp;
					op = line.substr(offset, line.length() - offset);
					while (true)
					{
						offset = op.find_first_of('\t');//Ѱ���״γ��ֵĿո�
						if (offset < 0) break;
						if (offset == op.length() - 1)
						{
							op = op.substr(0, op.length() - 1);
							break;
						}
						else
						{
							temp = op.substr(0, offset);
							leftTb.insert(pair<string, int>(temp, priority));
							while (line[offset] == ' ') offset++;
							op = op.substr(offset + 1, op.length() - offset);
						}
					}
					leftTb.insert(pair<string, int>(op, priority));
					priority++;
					offset = 0;
					temp.clear();
					op.clear();
					line.clear();
					getline(ifile, line);
				}
				else//��%�����治�Ƕ�����ַ���ֱ�����������ļ���ȥ
				{
					for (int i = 0; i < line.length(); i++)
					{
						ofile.put(line[i]);
					}
					ofile.put('\n');
					line.clear();
					getline(ifile, line);
				}
			}
			else//��һ���ַ����ǡ�%����ֱ�����������ļ���
			{
				for (int j = 0; j < line.length(); j++)
				{
					ofile.put(line[j]);
				}
				ofile.put('\n');
				line.clear();
				getline(ifile, line);
			}
		}
	}
	cout << "˵������������!" << endl;
}

int InputFileProcess::StringCountCh(string &str, char ch)//�����ַ���str���ַ�ch���ֵĸ���
{
	int count = 0;
	for (int n = 0; n < str.length(); n++)
	{
		if (str[n] == ch)
			count++;
	}
	return count;
}

contextTb InputFileProcess::RuleProcess()//�������ִ�����
{
	cout << "�������ֿ�ʼ!" << endl;
	contextTb conTb(tokenTb);
	string rule, temp, left, t;
	int offset;
	getline(ifile, rule);
	while (rule != "%%")
	{
		if (rule.find_first_of(':') == (rule.length() - 1))//ɨ�赽��ð�ŵ�һ��
		{
			//��ʱtempֵΪÿһ������
			offset = temp.find_first_of(':') - 1;
			int i = temp.find_first_of(':') + 1;
			while (temp[offset] == '\t') offset--;
			while (temp[i] == '\t') i++;
			left = temp.substr(0, offset + 1);//leftΪð����ߵ�����
			temp = temp.substr(i, temp.length() - 1 - i);
			int turn = StringCountCh(temp, '|');
			while (turn)
			{
				offset = temp.find_first_of('|') - 1;
				i = temp.find_first_of('|') + 1;
				while (temp[offset] == '\t') offset--;
				while (temp[i] == '\t') i++;
				t = temp.substr(0, offset + 1);//tΪtemp��ǰ��һ����|������ǰ����ַ���
				temp = temp.substr(i, temp.length() - 1 - i);//��tempΪ��temp��ǰ��һ����|�����ź�����ַ���
			    //����t
				conTb.insert(left, t);
				turn--;//��|������-1
				t.clear();
			}
			//��ʱ�������һ�����ߺ��������
			offset = temp.length() - 1;
			while (temp[offset] == ';' || temp[offset] == '\t') offset--;
			temp = temp.substr(0, offset + 1);
			if (temp[0] == '/'&&temp[1]=='*')
			{
				temp.clear();
				temp.append("", 1);
			}
			conTb.insert(left, temp);
			temp.clear();
			left.clear();
			t.clear();
			temp += rule;
		}
		else
		{
			temp += rule;
		}
		getline(ifile, rule);
	}
	//��ʱ��temp��ֵΪ���򲿷ֵ����һ������
	offset = temp.find_first_of(':') - 1;
	int i = temp.find_first_of(':') + 1;
	while (temp[offset] == '\t') offset--;
	while (temp[i] == '\t') i++;
	left = temp.substr(0, offset + 1);//leftΪð����ߵ�����
	temp = temp.substr(i, temp.length() - 1 - i);
	int turn = StringCountCh(temp, '|');
	while (turn)
	{
		offset = temp.find_first_of('|') - 1;
		i = temp.find_first_of('|') + 1;
		while (temp[offset] == '\t') offset--;
		while (temp[i] == '\t') i++;
		t = temp.substr(0, offset + 1);
		temp = temp.substr(i, temp.length() - 1 - i);
		//����t
		conTb.insert(left, t);
		turn--;
		t.clear();
	}
	//��ʱ�������һ�����ߺ��������
	offset = temp.length() - 1;
	while (temp[offset] == ';' || temp[offset] == '\t') offset--;
	temp = temp.substr(0, offset + 1);
	conTb.insert(left, temp);
	t.clear();
	temp.clear();
	left.clear();
	t.clear();
	cout << "�������ֽ���!" << endl;
	return conTb;
}

void InputFileProcess::UserProOutput(char &ch)//�û��ӳ��������������
{
	cout << "�û��ӳ��򲿷������ʼ!" << endl;
	//��������û��ӳ��򲿷�����
	while (!ifile.eof())//���ļ�����δ����ʱ
	{
		ch = ifile.get();//��ȡ�ַ�
		ofile.put(ch);//����ȡ���ַ���������ļ���
	}
	cout << "�û��ӳ��򲿷��������!" << endl;
}