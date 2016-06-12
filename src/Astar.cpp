# include "Astar.hpp"
# include <algorithm>    // std::find

Astar::Astar(){
}

Astar::Astar(Node & s, Node & g, int h, bool b)
{
	Goal = &g;
	Start = &s;
	_h = h;
	_isAstar = b;
	Start->setF(Start->getH() + Start->getG());
	Open.push(*Start);
	std::cout << "/=MAP=\\" << std::endl;
	ft_display(Start->getTab(), false);
	std::cout << "\\=====/" << std::endl << std::endl;
}

void 											Astar::ft_display(std::vector<std::vector<int> > n, bool f) const
{
	for (std::vector<std::vector<int> >::iterator iti = n.begin(); iti < n.end(); ++iti)
  	{
  		std::cout << " ";
  		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
  		{
  			if (*itj == 0)
  				std::cout << "\033[1;31m" << *itj << " \033[0m";
  			else
  				std::cout << "\033[1;34m" << *itj << " \033[0m";
  		}
  		std::cout << std::endl;
  	}
  	if (f)
 	 	std::cout << std::endl;
}

Node											Astar::ft_new_state(Node *n, int x1, int y1, int x2, int y2)
{
	int											tmp;
	Node										state = *n;
	std::vector< std::vector<int> >				tab = state.getTab();
	
	tmp = tab[y1][x1];
	tab[y1][x1] = tab[y2][x2];
	tab[y2][x2] = tmp;
	state.setTab(tab);
	return (state);
}


std::list<Node>									Astar::CreatSuccessor(Node *n)
{
	std::vector< std::vector<int> >				tmp = n->getTab();
  	std::list<Node>								lst;
	int											x = 0;
	int											y = 0;
	int											t = static_cast<int>(tmp.size());
	bool										end = false;
	std::vector< std::vector<int> >::iterator	iti = tmp.begin();

	while (iti < tmp.end() && !end)
	{
  		x = 0;
  		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
  		{
  			if (*itj == 0)
  			{
	  			end = true;
	  			break;
	  		}
  			x++;
  		}
  		if (end == true)
  			break;
  		y++;
  		iti++;
  	}
  	if (x > 0 && x <= t - 1)
  		lst.push_back(ft_new_state(n, x, y, x-1, y));
  	if (x >= 0 && x <  t - 1)
  		lst.push_back(ft_new_state(n, x, y, x+1, y));
  	if (y > 0 && y <=  t - 1)
  		lst.push_back(ft_new_state(n, x, y, x, y-1));
  	if (y >= 0 && y <  t - 1)
  		lst.push_back(ft_new_state(n, x, y, x, y+1));
  	return (lst);
}

std::pair <int,int>								Astar::LookAfter(std::vector< std::vector<int> > tab, int n)
{
	std::pair <int,int>							myPair = std::make_pair(0,0);	
	int											y = 0;

	for (std::vector<std::vector<int> >::iterator iti = tab.begin(); iti != tab.end(); ++iti)
	{
		int										x = 0;

		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
		{
			if (*itj == n)
			{
				myPair = std::make_pair(x, y);
				return (myPair);
			}
			x++;
		}
		y++;
	}
	return (myPair);
}

int												Astar::ManhattanDistance(Node n)
{
	int											sum = 0;
	std::vector<std::vector<int> >				finalTab = Goal->getTab();
	std::vector<std::vector<int> >				nodeTab = n.getTab();
	std::vector<std::vector<int> >::iterator	iti1 = nodeTab.begin();

	for (std::vector<std::vector<int> >::iterator iti = finalTab.begin(); iti < finalTab.end(); ++iti)
  	{
		std::vector<int>::iterator				itj1 = iti1->begin();

  		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
  		{
  			std::pair <int, int>				finalPair = LookAfter(finalTab, *itj);
  			std::pair <int, int>				nodePair = LookAfter(nodeTab, *itj);
			int									tmp1 = finalPair.first - nodePair.first;
			int									tmp2 = finalPair.second - nodePair.second;
			if (tmp1 < 0)
				tmp1 *= -1;
			if (tmp2 < 0)
				tmp2 *= -1;
			sum += tmp1 + tmp2;
			itj1++;
		}
		iti1++;
  	}
  	return sum;
}

int												Astar::linearConflict(Node n)
{
	int											sum = 0;
	int											l = 0;
	std::vector< std::vector<int> >				nodeTab = n.getTab();

	for (std::vector<std::vector<int> >::iterator iti = nodeTab.begin(); iti < nodeTab.end(); ++iti)
	{
  		for (std::vector<int>::iterator itja = iti->begin(), end = iti->end() - 1; itja != end; ++itja)
  		{
	  		std::vector<int>::iterator			itja2 = itja;
	  		itja2++;
	  		while (itja2 != iti->end())
	  		{
  				if (ft_search_in_goal(*itja2, *itja, l))
  					sum++;
  				itja2++;
  			}
  		}
		l++;
  	}
  	sum+= ManhattanDistance(n);
  	return sum;
}


bool											Astar::TOORACsearchX(int val, int line)
{
	int											l = 0;
	std::vector< std::vector<int> >				Tab = Goal->getTab();

	for (std::vector< std::vector<int> >::iterator iti = Tab.begin(); iti < Tab.end(); ++iti)
	{
  		for (std::vector<int>::iterator itja = iti->begin(), end = iti->end(); itja != end; ++itja)
  		{
			if (line == l && val == *itja)
				return (false);
		}
		l++;
	}
	return (true);
}

bool											Astar::TOORACsearchY(int val, int line)
{
	int											a = 0;
	std::vector< std::vector<int> >				Tab = Goal->getTab();
  	std::vector< std::vector<int> >::iterator	iti = Tab.begin();
  	std::vector<int>::iterator					itja = iti->begin();

  	while (itja != iti->end())
  	{
		for (std::vector< std::vector<int> >::iterator it = Tab.begin(); it < Tab.end(); ++it)
		{
			std::vector<int>::iterator v = it->begin();
			if (a == line && *v == val)
				return (false);
		}
		itja++;
		a++;
  	}
  	return (true);
}

int												Astar::TOORAC(Node n)
{
	int											sum = 0;
	int											l = 0;
	std::vector< std::vector<int> >				nodeTab = n.getTab();

	for (std::vector< std::vector<int> >::iterator iti = nodeTab.begin(); iti < nodeTab.end(); ++iti)
	{
		for (std::vector<int>::iterator itja = iti->begin(), end = iti->end(); itja != end; ++itja)
		{
			if (TOORACsearchX(*itja, l))
				sum++;
		}
		l++;
	}

	int											a = 0;
	std::vector<std::vector<int> >::iterator	iti = nodeTab.begin();
	std::vector<int>::iterator					itja = iti->begin();

	while (itja != iti->end())
	{
		for (std::vector<std::vector<int> >::iterator it = nodeTab.begin(); it < nodeTab.end(); ++it)
		{
			std::vector<int>::iterator v = it->begin();
			if (TOORACsearchY(*v, a))
				sum++;
		}
		itja++;
		a++;
	}
	return sum;
}

bool											Astar::MaxSwapIsBlankInGoalPos(std::vector<std::vector<int> > nodeTab)
{
	std::vector<std::vector<int> >				finalTab = Goal->getTab();
	std::vector<std::vector<int> >::iterator	itn = nodeTab.begin();

	for (std::vector<std::vector<int> >::iterator itf = finalTab.begin(), end = finalTab.end(); itf != end; ++itf)
	{
		std::vector<int>::iterator				itn2 = itn->begin();

		for (std::vector<int>::iterator itf2 = itf->begin(); itf2 < itf->end(); ++itf2)
		{
			if (*itn2 == 0 && *itn2 == *itf2)
				return (true);
			itn2++;
		}
		itn++;
	}
	return false;
}

void											Astar::MaxSwapWithMatched(std::vector<std::vector<int> > * nodeTab)
{
	int 										x1 = -1;
	int 										x2 = -1;
	std::vector< std::vector<int> >				finalTab = Goal->getTab();
	std::vector< std::vector<int> >::iterator	itn = nodeTab->begin();

	for (std::vector<std::vector<int> >::iterator itf = finalTab.begin(), end = finalTab.end(); itf != end; ++itf)
	{
		std::vector<int>::iterator				itn2 = itn->begin();

		for (std::vector<int>::iterator itf2 = itf->begin(); itf2 < itf->end(); ++itf2)
		{
			if (*itn2 == 0 && *itn2 != *itf2)
			{
				x1 = *itn2;
				x2 = *itf2;
				break;
			}
			itn2++;
		}
		if (x1 != -1 && x2 != -1)
			break;
		itn++;
	}

	bool										b1 = false;
	bool										b2 = false;

	itn = nodeTab->begin();
	for (std::vector<std::vector<int> >::iterator itf = finalTab.begin(), end = finalTab.end(); itf != end; ++itf)
	{
		std::vector<int>::iterator				itn2 = itn->begin();

		for (std::vector<int>::iterator itf2 = itf->begin(); itf2 < itf->end(); ++itf2)
		{
			if (*itn2 == x1 && !b1)
			{
				*itn2 = x2;
				b1 = true;
			}
			else if (*itn2 == x2 && !b2)
			{
				*itn2 = x1;
				b2 = true;
			}
			itn2++;
		}
		itn++;
	}
}


void											Astar::MaxSwapGetFirstMismatch(std::vector<std::vector<int> > * nodeTab)
{
	int											x1 = -1;
	int											x2 = -1;
	std::vector< std::vector<int> >				finalTab = Goal->getTab();
	std::vector< std::vector<int> >::iterator	itn = nodeTab->begin();

	for (std::vector<std::vector<int> >::iterator itf = finalTab.begin(), end = finalTab.end(); itf != end; ++itf)
	{
		std::vector<int>::iterator				itn2 = itn->begin();

		for (std::vector<int>::iterator itf2 = itf->begin(); itf2 < itf->end(); ++itf2)
		{
			if (*itn2 == 0 && x1 == -1)
				x1 = *itn2;
			else if (*itn2 != *itf2 && x2 == -1)
				x2 = *itn2;
			itn2++;
		}
		itn++;
	}
	bool										b1 = false;
	bool										b2 = false;

	itn = nodeTab->begin();
	for (std::vector<std::vector<int> >::iterator itf = finalTab.begin(), end = finalTab.end(); itf != end; ++itf)
	{
		std::vector<int>::iterator itn2 = itn->begin();
		for (std::vector<int>::iterator itf2 = itf->begin(); itf2 < itf->end(); ++itf2)
		{
			if (*itn2 == x1 && !b1)
			{
				*itn2 = x2;
				b1 = true;
			}
			else if (*itn2 == x2 && !b2)
			{
				*itn2 = x1;
				b2 = true;
			}
			itn2++;
		}
		itn++;
	}
}

int												Astar::MaxSwap(Node n)
{
	int											sum = 0;
	std::vector< std::vector<int> >				nodeTab = n.getTab();
	std::vector< std::vector<int> >				finalTab = Goal->getTab();

	while (nodeTab != finalTab)
	{
		if (MaxSwapIsBlankInGoalPos(nodeTab))
			MaxSwapGetFirstMismatch(& nodeTab);
		else
			MaxSwapWithMatched(& nodeTab);
		sum++;
	}
	return sum;
}

bool											Astar::ft_search_in_goal(int tj, int tk, int l)
{
	int											newl = 0;
	std::vector< std::vector<int> >				Goalplop = Goal->getTab();

	for (std::vector< std::vector<int> >::iterator iti = Goalplop.begin(); iti < Goalplop.end(); ++iti)
	{
  		for (std::vector<int>::iterator itja = iti->begin(), end = iti->end() - 1; itja != end; ++itja)
  		{
			std::vector<int>::iterator			itja2 = itja;

	  		itja2++;
	  		while (itja2 != iti->end())
	  		{
	  			if (*itja == tj && *itja2 == tk && newl == l)
	  				return true;
  				itja2++;
	  		}
		}
  		newl++;
	}
	return false;
}

int												Astar::MisplacedTiles(Node n)
{
	int											i = 0;
	std::vector<std::vector<int> >				finalTab = Goal->getTab();
	std::vector<std::vector<int> >				nodeTab = n.getTab();
	std::vector<std::vector<int> >::iterator	iti1 = nodeTab.begin();

	for (std::vector<std::vector<int> >::iterator iti = finalTab.begin(), end = finalTab.end(); iti != end; ++iti)
	{
		std::vector<int>::iterator				itj1 = iti1->begin();

		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
		{
			if (*itj != *itj1)
				i++;
			itj1++;
		}
		iti1++;
	}
	return i;
}

int												Astar::ft_heuristic(Node n)
{
	if (_h == 1)
		return (MisplacedTiles(n));
	if (_h == 2)
		return (ManhattanDistance(n));
	if (_h == 3)
		return (linearConflict(n));
	if (_h == 4)
		return (MaxSwap(n));
	if (_h == 5)
		return (TOORAC(n));
	return (1);
}

void											Astar::final_rec_display(Node *p, int *i)
{
	if (p->getParent())
	{
		final_rec_display(p->getParent(), i);
		ft_display(p->getTab(), true);
		*i = *i + 1;
	}
}

void											Astar::Run()
{
	int											cit = 0;
	int											cio = 0;
	std::list<Node>								lst;

	Start->setH(ft_heuristic(*Start));
	Start->setF(Start->getH() + Start->getG());
	while (!Open.empty())
	{
		Node									current = Open.top();
		Close.insert(current);
		Open.pop();
		Node *n = const_cast<Node *>(&(*(Close.find(current))));
		if (n->getTab() == Goal->getTab())
		{
			int								i = 0;
			Node							*p = n;
			final_rec_display(p, &i);
			std::cout << "MOVES = " << i << std::endl;
			std::cout << "COMPLEXITY IN TIME = " << cit + i << std::endl;
			std::cout << "COMPLEXITY IN size = " << (Close.size() + Open.size()) << std::endl;
			return ;
		}
		lst = CreatSuccessor(n);
		for (std::list<Node>::iterator it = lst.begin(), end = lst.end(); it != end; ++it)
		{
			if (_isAstar)
				it->setG(n->getG() + 1);
			it->setH(ft_heuristic(*it));
			it->setF(it->getG() + it->getH());
			it->setParent(*n);
			if (Close.find(*it) == Close.end())
			{
				cit++;
				Open.push(*it);
			}
			cio++;
		}
	}
	std::cout << "ERROR" << std::endl;
}

Astar::~Astar(){
}