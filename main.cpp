﻿#include<iostream>
#include <string>
#include"converter.h"
#include"assembler.h"

int main()
{
	std::string input = " ";

	while (input.size())
	{
		std::cout << "Input your Expression :\n\n";
		getline(std::cin, input);

		std::string output = Convert::to_postfix(input);
		std::cout << std::endl << Convert::eval_postfix(output) << std::endl << std::endl;

	}

	system("pause");
	return 0;
}
