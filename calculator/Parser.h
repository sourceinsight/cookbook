#ifndef _PARSER_H_
#define _PARSER_H_

#include "Scanner.h"
#include <string>


class Node;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT
};

class Parser
{
public:
	Parser(const std::string& buf);
	void parse();
	Node* expr();
	Node* term();
	Node* factor();
	double calculate() const;
private:
	Scanner scanner_;
	Node* tree_;
	STATUS status_;
};

#endif 