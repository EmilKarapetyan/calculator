#include<iostream>
#include<fstream>
#include<assert.h>
#include<stack>
#include<string>
#include<sstream>

#ifndef CONVERTER_H
#define CONVERTER_H

class Convert
{

public:
	Convert() = default;
	static double eval_postfix(const std::string&);
	static double perform_operation(const char, double, double);
	static bool areParanthesisBalanced(const std::string &);
	static std::string to_postfix(const std::string&);

	static bool is_par(const char);
	static bool is_operand(const char);
	static bool is_operator(const char);
	static int priority(const char);

};

#endif // !CONVERTER_H

