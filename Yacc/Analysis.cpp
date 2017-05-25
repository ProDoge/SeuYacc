#include "Analysis.h"
#include <fstream>
#include<string>
ofstream ofile;

int Analysis::FindNextstate(int state, string expression)        //����Goto���ƽ�����һ��״̬
{
	map<string, pair<int, int>>::iterator iter = ActGoto[state].begin();
	for (iter; iter != ActGoto[state].end(); iter++)
	{
		if (iter->first == expression)
		{
			return (iter->second).second;
		}
	}
	return -1;
}

int Analysis::istoken(string s)          //�жϵ�ǰ�ַ����ս��(����1)���Ƿ��ս��(����0)
{
	for (int i = 0; i<token.size(); i++)
	{
		if ( token[i]== s)
			return 1;
	}
	for (int i = 0; i<expression.size(); i++)
	{
		if (expression[i] == s)
			return 0;
	}
}

void Analysis::output()
{
	ofile.open(file, ios::out);              //���﷨�������������file��
	ofile << "char* Analysis(vector<string> program)\n";
	ofile << "{\n";
	ofile << "\tstack<int> state;\n";
	ofile << "\tstate.push(0);\n";
	ofile << "\tstack<string> symbol;\n";
	ofile << "\tsymbol.push(\"#\");\n\n";
	ofile << "\tint popstate = 0;\n";
	ofile << "\tint flag = 1;\n";
	ofile << "\tint point = 0;\n";
	ofile << "\tstring str = \"\";\n\n";
	ofile << "\twhile (flag)\n";
	ofile << "\t{\n";
	ofile << "\t\tpopstate = state.top();\n";
	ofile << "\t\tstr = program[point];\n";
	ofile << "\t\tswitch(popstate)\n";
	ofile << "\t\t{\n";
	for (int i = 0; i < ActGoto.size(); i++)
	{
		ofile << "\t\tcase " << i << ":\n";
		ofile << "\t\t{\n";
		if (ActGoto[i].size() == 0)
		{
			ofile << "\t\t\treturn \"error\";\n";
		}
		else
		{
			map<string, pair<int, int>>::iterator iter = ActGoto[i].begin();
			for (iter; iter != ActGoto[i].end(); iter++)
			{
				if (((iter->second).first == 0)&&istoken(iter->first))           //��ʾ�ƽ�
				{
					const char *A1 = (iter->first).c_str();
					ofile << "\t\t\tif (str == \"" << A1 << "\")\n";
					ofile << "\t\t\t{\n";
					ofile << "\t\t\t\tstate.push(" << (iter->second).second << ");\n";
					ofile << "\t\t\t\tsymbol.push(\"" << A1 << "\");\n";
					ofile << "\t\t\t\tpoint++;\n";
					ofile << "\t\t\t\tbreak;\n";
					ofile << "\t\t\t}\n";
				}
				if (((iter->second).first == 1) && istoken(iter->first))           //��ʾ��Լ
				{
					string A2 = (iter->first);
					ofile << "\t\t\tif (str == \"" << A2 << "\")\n";
					ofile << "\t\t\t{\n";
					ofile << "\t\t\t\tint n = " << Tbl.get((iter->second).second).getRight().size() << ";\n";
					ofile << "\t\t\t\tfor(int i = 0;i < n;i++)\n";
					ofile << "\t\t\t\t{\n";
					ofile << "\t\t\t\t\tstate.pop();\n";
					ofile << "\t\t\t\t\tsymbol.pop();\n";
					ofile << "\t\t\t\t}\n";
					string B = (Tbl.get((iter->second).second).getLeft());
					ofile << "\t\t\t\tsymbol.push(\"" << B<< "\");\n";
					ofile << "\t\t\t\tpopstate = state.top();\n";
					ofile << "\t\t\t\tif(nextstate(popstate,\"" << B << "\") != -1)\n";
					ofile << "\t\t\t\t{\n";
					ofile << "\t\t\t\t\tstate.push(nextstate(popstate,\"" << B << "\"));\n";
					ofile << "\t\t\t\t}\n";
					ofile << "\t\t\t\telse\n";
					ofile << "\t\t\t\t{\n";
					ofile << "\t\t\t\t\treturn \"error\";\n";
					ofile << "\t\t\t\t}\n";
					ofile << "\t\t\t\tbreak;\n";
					ofile << "\t\t\t}\n";
				}
				if (((iter->second).first == 2) && istoken(iter->first))              //��ʾ��ȷ
				{
					const char *A3 = (iter->first).c_str();
					ofile << "\t\t\tif (str == \"" << A3 << "\")\n";
					ofile << "\t\t\t{\n";
					ofile << "\t\t\t\tflag = 0;\n";
					ofile << "\t\t\t\treturn \"success\";\n";
					ofile << "\t\t\t}\n";
				}
			}
			ofile << "\t\t\telse\n";
			ofile << "\t\t\t{\n";
			ofile << "\t\t\t\treturn \"error\";\n";
			ofile << "\t\t\t}\n";
		}
		ofile << "\t\t}\n";
	}
	ofile << "\t\t}\n";
	ofile << "\t}\n";
	ofile << "}\n\n";


	ofile << "int nextstate(int state,string expression)\n";                    //Goto����ƽ�
	ofile << "{\n";
	ofile << "\tswitch(state)\n";
	ofile << "\t{\n";
	for (int i = 0; i < ActGoto.size(); i++)
	{
		ofile << "\tcase " << i << ":\n";
		ofile << "\t{\n";
		map<string, pair<int, int>>::iterator iter = ActGoto[i].begin();
		for (iter; iter != ActGoto[i].end(); iter++)
		{
			if (((iter->second).first == 0) && !istoken(iter->first))           //��ʾ�ƽ�
			{
				const char *A1 = (iter->first).c_str();
				ofile << "\t\tif ( expression == \"" << A1 << "\")\n";
				ofile << "\t\t{\n";
				if (FindNextstate(i, iter->first)>=0)
				{
					ofile << "\t\t\treturn " << FindNextstate(i, iter->first) << ";\n";
				}
				else
				{
					ofile << "\t\t\treturn -1;\n";
				}
				ofile << "\t\t}\n";
			}
		}
		ofile << "\t\treturn -1;\n";
		ofile << "\t}\n";
	}
	ofile << "\t}\n";
	ofile << "}\n";

	ofile.close();
}

