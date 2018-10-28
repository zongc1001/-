#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;
struct Opr
{
	char type;
	int prio;
	static int base;

	Opr(char type)
	{
		this->type = type;
		if (type == '=')
			prio = 1 + base;
		else if (type == '+' || type == '-')
			prio = 2 + base;
		else if (type == '*' || type == '/' || type == '%')
			prio = 3 + base;
		else if (type == '^')
			prio = 4 + base;
		else if (type == '(')
		{
			prio = 5 + base;
			base += 5;
		}
		else if (type == ')')
		{
			prio = 2 + base;
			base-=5;
		}
		else
			prio = 0;

	}
	bool operator>=(Opr obj)
	{
		return prio >= obj.prio;
	}
};
int Opr::base = 0;

struct Opn
{
	double num;
	bool isLeft;
	Opn(double num)
	{
		this->num = num;
	}
};
int main(int argc, char const *argv[])
{
	while(true)
	{
		stack<Opn> opnStk;
		stack<Opr> oprStk;
		oprStk.push(Opr('='));
		bool lastIsNum = false;

		double tempDouble;

		string tempString;
		string exp;
		getline(cin, exp);

		stringstream ss;
		int index = 0;  
		int len = exp.length();

		while (index < len)
		{
			// if (!opnStk.empty())
			// if (!oprStk.empty())
			if (exp[index] == ' ')
			{
				index++;
				continue;
			}
			int begin = 0;
			int end = 0;
			if (exp[index] >= '0' && exp[index] <= '9')
			{
				begin = index;
				while ((exp[index] >= '0' && exp[index] <= '9') || exp[index] == '.')
				{
					index++;
				}
				end = index;
				stringstream ss(exp.substr(begin, end));
				ss >> tempDouble;
				Opn tempOpn(tempDouble); 
				opnStk.push(tempOpn);
				lastIsNum = true;
				continue;
			}
			else if (exp[index] == '+'
				|| exp[index] == '-'
				|| exp[index] == '*'
				|| exp[index] == '/'
				|| exp[index] == '%'
				|| exp[index] == '^'
				|| exp[index] == '('
				|| exp[index] == ')'
				|| exp[index] == '='
				)
			{
				Opr opr(exp[index]);
				if (!lastIsNum && opr.type != '(')
				{
					Opn o(0);
					opnStk.push(o);
				}

				while (oprStk.top().type != '=' && oprStk.top() >= opr)
				{
					double right = opnStk.top().num;
					opnStk.pop();
					double left = opnStk.top().num;
					opnStk.pop();
					if (oprStk.top().type == '+')
					{
						Opn o(left + right);
						opnStk.push(o);
					}
					else if (oprStk.top().type == '-')
					{
						Opn o(left - right);
						opnStk.push(o);
					}
					else if (oprStk.top().type == '*')
					{
						Opn o(left * right);
						opnStk.push(o);
					}
					else if (oprStk.top().type == '/')
					{
						if (right == 0)
						{
							index = len;
							cout << "The divisor can't be zero!" << endl;
							break;
						}
						Opn o(left / right);
						opnStk.push(o);
					}
					else if (oprStk.top().type == '%')
					{
						Opn o((int)left % (int)right);
						opnStk.push(o);
					}
					else if (oprStk.top().type == '^')
					{
						Opn o(pow(left, right));
						opnStk.push(o);
					}
					oprStk.pop();

				}
				if (oprStk.top().type == '(' && opr.type == ')')
				{
					lastIsNum = true;
					oprStk.pop();
				}
				else if (oprStk.top().type == '=' && opr.type == '=')
				{
					lastIsNum = false;
					double temp = opnStk.top().num;
					opnStk.pop();
					if (opnStk.empty())
						cout << setprecision(20) << temp << endl;
					else
						cout << "Is yout expression legal? (Maybe there are redundant operands)" << endl;
				}
				else
				{
					oprStk.push(opr);
					lastIsNum = false;
				}
				
				index++;
			}
		}
	}
	return 0;
}