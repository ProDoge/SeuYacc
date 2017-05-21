#include "LrState.h"
#include <algorithm>
#include <numeric>
#include <iostream>

LrState::LrState(LrState s, string input, contextTb tb)
{
	if (s.contextNext.count(input) > 0)
	{
		vector<int> num = s.contextNext[input];
		for (int i = 0; i < num.size(); i++)
		{
			Follow.push_back(s.Follow[num[i]]);
			context.push_back(s.context[num[i]]);
			Dot.push_back(s.Dot[num[i]]+1);
			extend.push_back(0);
		}
		//�˴����հ���չ����
		int size = 0;
		while ((size != context.size()) || accumulate(extend.begin(), extend.end(), 0) < extend.size())
		{
			size = context.size();
			for (int i = 0; i < context.size(); i++)
			{
				if (extend[i] == 0&& context[i].getRight().size()>Dot[i])
				{
					string Left = context[i].getRight()[Dot[i]];				//Left�ǵ�ǰDot����ַ���
					vector<string> follow;
					if (context[i].getRight().size() - 1 > Dot[i])				//������滹���ַ����Ļ����õ������ַ���First
						follow = tb.getFisrt(context[i].getRight()[Dot[i] + 1]);
					else																		//�������û���ַ����Ļ���follow�������������Follow
						follow = Follow[i];
					//���Left����token���Ƿ��ս���Ļ�
					if (tb.judgeTorE(Left) == 1)
					{
						vector<int> TblNum = tb.exprMap[Left];				//���Left��Ӧ�����й���
						for (int j = 0; j < TblNum.size(); j++)					//��Left�ĵ�j������
						{
							bool flag = true;												//�����Ƿ�Ի�õĹ�������˲���
							for (int k = 0; k < context.size(); k++)			//�˶Ե�ǰ״̬���Ƿ�����ͬ��ת�����򣬲�����Number���뵽��Ӧλ��
							{
								if (tb.get(TblNum[j]) > context[k])
									continue;
								else if (tb.get(TblNum[j]) == context[k] && Dot[k] == 0)//���ظ�������չ�ĺϲ�
								{
									flag = false;
									updateFollow(follow, k);
									break;
								}
								else if (tb.get(TblNum[j]) < context[k])
								{
									i++;
									flag = false;
									Follow.insert(Follow.begin() + k, follow);
									context.insert(context.begin() + k, tb.get(TblNum[j]));
									Dot.insert(Dot.begin() + k, 0);
									extend.insert(extend.begin() + k, 0);
									break;
								}
							}
							if (flag)//��û���������뵽���
							{
								Follow.push_back(follow);
								context.push_back(tb.get(TblNum[j]));
								Dot.push_back(0);
								extend.push_back(0);
							}
						}
					}
				}
				extend[i] = 1;
			}
		}
		updateNext(tb);
	}
	else
	{
		std::cout << "error in create LrState, State not have input: " << input << endl;
		exit(1);
	}
}

LrState::LrState(vector<conFreeGram> con, contextTb tb)
{
	context = con;
	for (int i = 0; i < context.size(); i++)
	{
		vector<string> s;
		s.push_back(terminal);
		Follow.push_back((s));
		Dot.push_back(0);
		extend.push_back(0);
	}

	int size = 0;
	//�˴����հ���չ����
	while (size != context.size())
	{
		size = context.size();
		for (int i = 0; i < context.size(); i++)
		{
			if (extend[i] == 0)
			{
				string Left = context[i].getRight()[Dot[i]];
				vector<string> follow;
				if (context[i].getRight().size() - 1 > Dot[i])
					follow = tb.getFisrt(context[i].getRight()[Dot[i] + 1]);
				else
					follow.push_back(terminal);
				//�������token
				if (tb.judgeTorE(Left) == 1)
				{
					vector<int> TblNum = tb.exprMap[Left];
					for (int j = 0; j < TblNum.size(); j++)
					{
						for (int k = 0; k < context.size(); k++)
						{
							if (tb.get(TblNum[j]) > context[k]&&k!= context.size()-1)
								continue;
							else if (tb.get(TblNum[j]) == context[k] && Dot[k] == 0)//���ظ�������չ�ĺϲ�
							{
								updateFollow(follow, k);
								break;
							}
							else if (tb.get(TblNum[j]) < context[k]|| k == context.size() - 1)
							{
								if (k == context.size() - 1)
									k++;
								else
									i++;
								Follow.insert(Follow.begin() + k, follow);
								context.insert(context.begin() + k, tb.get(TblNum[j]));
								Dot.insert(Dot.begin() + k, 0);
								extend.insert(extend.begin() + k, 0);
								break;
							}
						}
					}
				}
				extend[i] = 1;
			}
		}
	}
	updateNext(tb);
}

int LrState::size()
{
	return context.size();
}

int LrState::ContextSize(int id)
{
	return context[id].getRight().size();
}

int LrState::ifEnd(int id)
{
	if (ContextSize(id) <=	Dot[id])
		return 1;
	else
		return 0;
}

void LrState::
updateFollow(vector<string> s, int pos)
{
	vector<string> newFollow;
	sort(s.begin(), s.end());
	set_union(s.begin(), s.end(), Follow[pos].begin(), Follow[pos].end(), back_inserter(newFollow));
	sort(newFollow.begin(), newFollow.end());
	Follow[pos] = newFollow;
}

void LrState::updateNext(contextTb tb)
{
	for (int i = 0; i < context.size(); i++)
	{
		vector<string> slist;
		if (Dot[i] < context[i].getRight().size())
		{//LrState�ڵ�i�����������string
			string currString = context[i].getRight()[Dot[i]];
			slist.push_back(currString);
		}
		for (int j = 0; j < slist.size(); j++)
		{
			if (contextNext.count(slist[j]) > 0)
				contextNext[slist[j]].push_back(i);
			else
			{
				//����StateNext
				StateNext.push_back(slist[j]);
				vector<int> newNext;
				newNext.push_back(i);
				contextNext.insert(pair<string, vector<int>>(slist[j], newNext));
			}
		}
	}
}

bool operator==(const LrState &l, const LrState &r)
{
	if (l.context.size() != r.context.size())
		return false;
	bool flag = true;
	for (int i = 0; i <min( l.context.size(),r.context.size()); i++)
	{
		if (l.Dot[i] == r.Dot[i] && l.context[i] == r.context[i] );
		else
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		for (int i = 0; i < l.Follow.size(); i++)
		{
			if (l.Follow[i] == r.Follow[i]);
			else
			{
				flag = false;
				break;
			}
		}
	}
	return flag;
}
