#include <iostream>
#include <string>
#include <cstdio>
#include "Parser.h"

int main(void)
{
	std::cout << "(c) 2014 https://github.com/SourceInsight" << std::endl;
	
	STATUS status = STATUS_OK;
	do 
	{
		std::cout<<"Please input your expression > ";
		std::string buf;
		std::getline(std::cin, buf);
		if (buf == "quit" || buf == "q")
		{
			break;
		}
		Parser parser(buf);
		parser.parse();
		std::cout<< "Result: " << parser.calculate()<<std::endl;
	} while (status != STATUS_QUIT);
	
	return 0;
}
