#include "Node.hpp"

Node::Node()
{
	f = 0;
	g = 0;
	Parent = NULL;
	std::vector<std::vector<int>> vTab(3, std::vector<int>(3));
}

Node::Node(int i)
{
	f = i;
	g = 0;
	Parent = NULL;
	std::vector<std::vector<int>> vTab(3, std::vector<int>(3));
}

void 								Node::setTab(std::vector<std::vector<int> > tab)
{
	vTab = tab;
}

void 								Node::setParent(Node & obj)
{
	Parent = &obj;
}

void 								Node::setH(int i)
{
	h = i;
}

void 								Node::setG(int i)
{
	g = i;
}

bool								Node::operator<(const Node& rhs) const 
{
   return vTab < rhs.getTab();
}

void 								Node::setF(int i)
{
	f = i;
}

std::vector< std::vector<int> >		Node::getTab() const
{
	return vTab;
}

std::vector< std::vector<int> >*	Node::getTabad()
{
	return &vTab;
}

void 								Node::incG()
{
	g++;
}

Node* 								Node::getParent()
{
	return Parent;
}


int 								Node::getG() const
{
	return g;
}

int 								Node::getH() const
{
	return h;
}

int 								Node::getF() const
{
	return f;
}

void 								Node::AddToTab(std::vector<int> v)
{
	vTab.push_back(v);
}

Node::~Node(){}