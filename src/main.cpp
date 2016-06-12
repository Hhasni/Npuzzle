#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <sstream>
#include "Node.hpp"
#include "Astar.hpp"

void											ft_display_tab(std::vector<std::vector<int> > Goal)
{
	for (std::vector<std::vector<int> >::iterator iti = Goal.begin(); iti < Goal.end(); ++iti)
	{
		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
			std::cout << *itj << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void											ft_gen_goal_state(std::list<int> lst1, int n, Node* NGoal)
{
	std::list<int>::iterator					it2;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	std::vector< std::vector<int> >				Goal(n, std::vector<int>(n));
	int											a = 0;

	if (*(it2 = std::min_element(lst1.begin(), lst1.end())) == 0)
		lst1.remove(*it2);
	while (!lst1.empty())
	{
		//RIGHT
		row = Goal.begin() + a;
		col = row->begin() + a;
		while (!lst1.empty() && col + a != row->end())
		{
			it2 = std::min_element(lst1.begin(), lst1.end());
			*col = *it2;
			lst1.remove(*it2);
			col++;
		}
		//DOWN
		row = Goal.begin() + 1 + a;
		while (!lst1.empty() && row + a != Goal.end())
		{		
			col = row->end() - (1 + a);
			it2 = std::min_element(lst1.begin(), lst1.end());
			*col = *it2;
			lst1.remove(*it2);
			row++;
		}
		// LEFT
		row = Goal.end() - (1 + a);
		col = row->end() - (1 + a);
		while (!lst1.empty() && col - a != row->begin())
		{
			col--;
			it2 = std::min_element(lst1.begin(), lst1.end());
			*col = *it2;
			lst1.remove(*it2);
		}
		// UP
		row = Goal.end() - (2 + a);
		while (!lst1.empty() && row - a != Goal.begin())
		{
			col = row->begin() + a;
			it2 = std::min_element(lst1.begin(), lst1.end());
			*col = *it2;
			lst1.remove(*it2);
			row--;
		}
		a++;
	}
	NGoal->setTab(Goal);
}

std::list<int>									ft_gen_snail(std::list<int> lst1, int n)
{
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	std::vector< std::vector<int> >				Vtmp(n, std::vector<int>(n));
	std::list<int>								bkp = lst1;
	int											a = 0;

	for (std::vector<std::vector<int> >::iterator iti = Vtmp.begin(); iti < Vtmp.end(); ++iti)
	{
		for (std::vector<int>::iterator itj = iti->begin(); itj < iti->end(); ++itj)
		{
			*itj = lst1.front();
			lst1.pop_front();
		}
	}
	while (!bkp.empty())
	{
		//RIGHT
		row = Vtmp.begin() + a;
		col = row->begin() + a;
		while (!bkp.empty() && col + a != row->end())
		{
			lst1.push_back(*col);
			col++;
			bkp.pop_front();
		}
		//DOWN
		row = Vtmp.begin() + 1 + a;
		while (!bkp.empty() && row + a != Vtmp.end())
		{
			col = row->end() - (1 + a);
			lst1.push_back(*col);
			row++;
			bkp.pop_front();
		}
		// LEFT
		row = Vtmp.end() - (1 + a);
		col = row->end() - (1 + a);
		while (!bkp.empty() && col - a != row->begin())
		{
			col--;
			lst1.push_back(*col);
			bkp.pop_front();
		}
		// UP
		row = Vtmp.end() - (2 + a);
		while (!bkp.empty() && row - a != Vtmp.begin())
		{
			col = row->begin() + a;
			lst1.push_back(*col);
			bkp.pop_front();
			row--;
		}
		a++;
	}
	return lst1;
}


bool											ft_check_unsolvable(std::vector<std::vector<int> > s, std::list<int> lst, int n)
{
	int											inversion = 0;
	int											l = n;
	int											blank = 0;

	for (std::vector<std::vector<int> >::iterator iti = s.begin(), end = s.end(); iti != end; ++iti)
	{
		for (std::vector<int>::iterator itj = iti->begin(); itj != iti->end(); ++itj)
		{
			if (*itj == 0)
				blank = l;
		}
		l--;
	}

	std::list<int>::iterator					myend = lst.end();

	myend--;
	for (std::list<int>::iterator iti = lst.begin() ;iti != myend; ++iti)
	{
		int										hyh = 0;
		std::list<int>::iterator				plop = iti;

		plop++;
		while (plop != lst.end())
		{
			if (*iti != 0 && *plop != 0 && *iti > *plop)
			{
				inversion++;
				hyh++;
			}
			plop++;
		}
	}
	if (inversion % 2 == 0)
		return (false);
	return (true);

}

int												ft_read_from_file(std::string filename, Node* Start, Node* Goal)
{
	std::ifstream								ifs (filename.c_str(), std::ifstream::in);
	std::string									line;
	std::string									buf;
	std::list<int>								lst1;
	int											n = 0;

	if (!ifs.is_open())
	{
		ifs.close();
		throw std::runtime_error("Usage Error : Unable to open " + filename);
	}
	while (getline(ifs, line))
	{
		size_t									str_end = line.find("#");

		if (str_end != std::string::npos)
			line = line.substr(0, str_end);
		if (!line.empty())
		{
			if (n == 0)
			{
				size_t							endpos = line.find_last_not_of(" \t");

				if (std::string::npos != endpos)
				  line = line.substr(0, endpos+1);

				size_t							nd = line.find(" ");

				if (nd != std::string::npos)
					return (0);
				n = stoi(line);
				if (n < 3)
					return (n);
				std::cout << "n = " << n << std::endl;
			}
			else
			{
				std::stringstream 				ss(line);
				std::vector<int>				v;
				while (ss >> buf)
				{
					v.push_back(stoi(buf));
					lst1.push_back(stoi(buf));
				}
				Start->AddToTab(v);
			}
		}
	}
	if (ft_check_unsolvable(Start->getTab(), ft_gen_snail(lst1, n), n))
		return (-1);
	ft_gen_goal_state(lst1, n, Goal);
	return (n);
}

int												ft_arg(std::vector<std::string> *Tstr, bool *b)
{
	if (Tstr->begin() == Tstr->end())
		Tstr->push_back("-h");
	while (Tstr->size() > 0)
	{
		std::vector<std::string>::iterator it = Tstr->begin();
		if (!it->compare("-help") || !it->compare("-h"))
		{
			std::cout << "usage: npuzzle [-h] [HEURISTIC/ALGO] map" << std::endl << std::endl;
			std::cout << "heuristic for A*:" << std::endl;
			std::cout << "-mt, -missplacedTitles\t\t\t Use the missplaced titles heuristic" << std::endl;
			std::cout << "-md, -manathanDistance\t\t\t Use the manathan distance heuristic" << std::endl;
			std::cout << "-lc, -linearConflict\t\t\t Use the linear conflict heuristic" << std::endl;
			std::cout << "-ms, -maxSwap\t\t\t\t Use the N max swap heuristic" << std::endl;
			std::cout << "-to, -toorac\t\t\t\t Use the title out of row and colomn heuristic" << std::endl << std::endl;
			std::cout << "Other Algorithme :" << std::endl;
			std::cout << "-BFS, -bfs\t\t\t\t Use the Best First Search Algorithme" << std::endl << std::endl;
			return(0);
		}
		else if (!it->compare("-missplacedTitles") || !it->compare("-mt"))
		{
			Tstr->erase(it);
			return(1);
		}
		else if (!it->compare("-manathanDistance") || !it->compare("-md"))
		{
			Tstr->erase(it);
			return(2);
		}
		else if (!it->compare("-linearConflict") || !it->compare("-lc"))
		{
			Tstr->erase(it);
			return(3);
		}
		else if (!it->compare("-maxSwap") || !it->compare("-ms"))
		{
			Tstr->erase(it);
			return(4);
		}
		else if (!it->compare("-toorac") || !it->compare("-to"))
		{
			Tstr->erase(it);
			return(5);
		}
		else if (!it->compare("-BFS") || !it->compare("-bfs"))
		{
			*b = false;
			Tstr->erase(it);
		}
		else
			return (1);
	}
	return (1);
}

int												main(int ac, char const *av[])
{
	try
	{
		int										h = 0;
		bool									b = true;
		std::vector<std::string>				param(av, av+ac);

		param.erase(param.begin());
		if (!(h = ft_arg(&param, &b)))
			return (-1);

		Node*									Start = new Node();
		Node*									Goal = new Node();
		int										n = 0;

		n = ft_read_from_file(*(param.begin()), Start, Goal);
		if (n < 0)
		{
			std::cout << "UNSOLVABLE " << std::endl;
			return (-1);
		}
		else if (n < 3)
		{
			std::cout << "ERROR MAP"  << std::endl;
			return (-1);
		}

		Astar*									my_astar = new Astar(*Start, *Goal, h, b);
		my_astar->Run();
	}
	catch (std::exception &e)
	{
		std::cout << " I have just catch : "  << e.what() << std::endl;
	}
}
