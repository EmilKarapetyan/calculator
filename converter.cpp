#include"converter.h"

double Convert::eval_postfix(const std::string& in)
{
	std::stack<double> Stack;
	int i = 0;

	while (i < in.size())
	{
		if (is_operand(in[i]) || (in[i] == '-' && (i == 1 || i > 0 && in[i-1] ==',' && i < in.size() - 1 && is_operand(in[i+1]))))
		{
			std::string dig = "";

			if (in[i] == '-')
			{
				dig += '-';
				i++;
			}
			
			while (i < in.size() && is_operand(in[i]))
				dig += in[i++];
	
			Stack.push(stod(dig));
			i--;
		}
		else if (is_operator(in[i]))
		{
			double ope2 = Stack.top(); Stack.pop();
			double ope1 = Stack.top(); Stack.pop();

			Stack.push(perform_operation(in[i], ope1, ope2));
		}
		
		i++;
	}

	return Stack.top();
}

double Convert::perform_operation(const char op, double operand1, double operand2)
{
	if (op == '/')
		try {
		if (operand2)
			return (operand1 / operand2);
		throw "Division by zero condition!";
	}
	catch (const char* msg) {
		std::cerr << "Caught an exception! " << std::endl;
		std::cerr << msg << std::endl;
		assert(false);
	}
	switch (op)
	{
	case '+': return (operand1 + operand2);
	case '-': return (operand1 - operand2);
	case '*': return (operand1 * operand2);
	case '^': return pow(operand1, operand2);
	default:
		assert(false);
		break;
	}
}

std::string Convert::to_postfix(const std::string& in)
{
	std::string out = "";
	bool min_sign = false;
	std::stack<char> Stack;
	
	if (!areParanthesisBalanced(in))
	{
		std::cout << "Your brackets are not closed :\n";
		assert(false);
	}

	int i = 0;
	while (i < in.size())
	{
		if (in[i] == ' ')
		{
			i++;
			continue;
		}

		if (in[i] == '-' && (i == 0 || (i > 0 && in[i-1] == '(')))
			min_sign = true;

		if (is_operand(in[i]) || min_sign)
		{
			out += ",";

			if (min_sign)
			{
				i++;
				out += '-';
				min_sign = false;
			}
		
			while (i < in.size() && is_operand(in[i]))
				out += in[i++];

			i--;
		}
		else if (is_operator(in[i]))
		{
			while (!Stack.empty() && is_operator(in[i]) && is_operator(Stack.top()) && priority(Stack.top()) >= priority(in[i]))
			{
				out += Stack.top();
				Stack.pop();
			}
			
			Stack.push(in[i]);
		}
		else if (is_par(in[i]))
		{
			// in the rigth side of ')' bracket must be operator or bracket
			// in the ledt side of ')' bracket must be operand or bracket
			//is cannot be the first element of expression
			//
			// in the rigth side of '(' bracket must be operator or bracket
			// in the ledt side of ')' bracket must be operand or bracket
			//is cannot be the first element of expression
			
			if (in[i] == ')' && ((i == in.size() - 1 && (is_par(in[i - 1]) || is_operand(in[i - 1]))) || (i > 0 && i < in.size() - 1 && ((is_par(in[i - 1]) || is_operand(in[i - 1])) && ( is_operator(in[i + 1]) || is_par(in[i + 1]))))))
			{
				while (Stack.top() != '(')
				{
					out += Stack.top(); Stack.pop();
				}
				Stack.pop();
			}
			else if(in[i] == '(' && ((i == 0 && (in[i + 1] == '-' || is_par(in[i + 1]) || is_operand(in[i + 1]))) || (i > 0 && i < in.size() - 1 && ((is_par(in[i - 1]) || is_operator(in[i - 1])) && (in[i + 1] == '-' || is_operand(in[i + 1]) || is_par(in[i + 1]))))))
			{
				Stack.push(in[i]);
			}
			else
			{
				assert("Wrong sequence of parenthases");
			}
		}
		else
		{
			assert("Wrong sequence of character :\n");
		}
	
		i++;
	}
	while (!Stack.empty())
	{
		out += Stack.top(); Stack.pop();
	}

	return out;
}

bool Convert::is_par(const char c)
{
	return (c == '(' || c == ')');
}

bool Convert::is_operand(const char c)
{
	return (!is_operator(c) && !is_par(c) && (isdigit(c) || isalpha(c)) || c == '.');
}

bool Convert::is_operator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' );
}

int Convert::priority(const char c)
{
	switch (c)
	{
	case '-':
	case '+':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		std::cout << "Undefined operator \n";
		assert(false);
		break;
	}
}

bool Convert::areParanthesisBalanced(const std::string &exp)
{

	int count = 0;
	for (int i = 0; i < exp.length(); i++)
		if (exp[i] == '(')
			count++;
		else if (exp[i] == ')')
			count--;
		else
			continue;
	
	return !count;
}
