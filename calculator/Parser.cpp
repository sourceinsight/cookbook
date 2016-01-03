#include "Parser.h"
#include "Node.h"

#include <cassert>
#include <iostream>
#include <functional>

Parser::Parser(const std::string& buf) 
		: scanner_(buf), tree_(0)
{
}

void Parser::parse()
{
	tree_ = expr();
}

Node* Parser::expr()
{
	Node* node = term();
	EToken token = scanner_.token();
	if (token == TOKEN_PLUS)
	{
		scanner_.accept();
		Node* nodeRight = expr();
		node = new BinaryNode<std::plus<double> >(node, nodeRight);
	}
	else if (token == TOKEN_MINUS)
	{
		scanner_.accept();
		Node* nodeRight = expr();
		node = new BinaryNode<std::minus<double> >(node, nodeRight);
	}
	return node;
}

Node* Parser::term()
{
	Node* node = factor();
	EToken token = scanner_.token();
	if (token == TOKEN_MULTIPLY)
	{
		scanner_.accept();
		Node* nodeRight = term();
		node = new BinaryNode<std::multiplies<double> >(node, nodeRight);
	}
	else if (token == TOKEN_DIVIDE)
	{
		scanner_.accept();
		Node* nodeRight = term();
		node = new BinaryNode<std::divides<double> >(node, nodeRight);
	}
	return node;
}

Node* Parser::factor()
{
	Node* node = 0;
	EToken token = scanner_.token();
	if (token == TOKEN_LPARENTHESIS)
	{
		scanner_.accept();		// accept '('
		node = expr();
		if (scanner_.token() == TOKEN_RPARENTHESIS)
		{
			scanner_.accept();	// accept ')'
		}
		else
		{
			status_ = STATUS_ERROR;
			std::cout<<"missing parenthesis"<<std::endl;
			node = 0;
		}
	}
	else if (token == TOKEN_NUMBER)
	{
		node = new numberNode(scanner_.number());
		scanner_.accept();
	}
	else if (token == TOKEN_MINUS)
	{
		scanner_.accept();		// accept minus
		node = new UMinusNode(factor());
	}
	else
	{
		status_ = STATUS_ERROR;
		std::cout<<"not a valid expression"<<std::endl;
		node = 0;
	}
	return node;
}

double Parser::calculate() const
{
	assert(tree_ != 0);
	return tree_->calc();
}
