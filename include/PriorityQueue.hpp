#ifndef PRIORITYQUEUE_HPP
# define PRIORITYQUEUE_HPP

# include <queue>
# include "Node.hpp"
# include "myCompare.hpp"


template <
	class T,
	class Container = std::vector<Node>,
	class Compare = myCompare
	> class PriorityQueue : public std::priority_queue<T, Container, Compare>
	{
	public:
		typedef typename
			std::priority_queue<
			T,
			Container,
			Compare
			>::container_type::iterator						iterator;

	iterator												thefind(Node val)
	{
		auto												first = this->c.begin();
		auto												last = this->c.end();
		while (first!=last)
		{
			if (first->getTab() == val.getTab())
				return first;
			++first;
		}
		return last;
	}

	iterator												getEnd()
	{
		return (this->c.end());
	}

	void													myerase(Node val)
	{
		PriorityQueue <Node, std::vector<Node>, Compare>	tmp;

		while (this->c.size() > 0)
		{
			auto											first = this->c.begin();
			if (first->getTab() == val.getTab())
			{
				this->pop();
				break;
			}
			tmp.push(*first);
			this->pop();
		}
		while (tmp.size() > 0)
		{
			this->push(tmp.top());
			tmp.pop();
		}
	}

};
#endif