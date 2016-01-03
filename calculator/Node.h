#ifndef _NODE_H_
#define _NODE_H_


class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}
private:
	Noncopyable(const Noncopyable&);
	const Noncopyable& operator=(const Noncopyable&);
};


class Node : private Noncopyable
{
public:
	virtual double calc() const = 0;
	virtual ~Node() {}
};

class numberNode : public Node
{
public:
	numberNode(double number) : number_(number) {}
	double calc() const;
private:
	const double number_;
};

template <typename T>
class BinaryNode : public Node
{
public:
	BinaryNode(Node* left, Node* right)
		: left_(left), right_(right) {}
	~BinaryNode()
	{
		delete left_;
		delete right_;
	}
	double calc() const
	{
		T op;
		return op(left_->calc(), right_->calc());
	}
protected:
	Node* const left_;
	Node* const right_;
};

class UnaryNode : public Node
{
public:
	UnaryNode(Node* child)
		: child_(child) {}
	~UnaryNode();
protected:
	Node* const child_;
};

class UMinusNode : public UnaryNode
{
public:
	UMinusNode(Node* child)
		: UnaryNode(child) {}
	double calc() const;
};

#endif