#include "Node.h"
#include <cmath>
#include <iostream>

double numberNode::calc() const
{
	return number_;
}

UnaryNode::~UnaryNode()
{
	delete child_;
}

double UMinusNode::calc() const
{
	return - child_->calc();
}