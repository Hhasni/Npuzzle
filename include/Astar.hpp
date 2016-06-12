#ifndef ASTAR_HPP
# define ASTAR_HPP

# include <iostream>
# include <list>
# include <queue>
# include <set>
# include <map>
# include <unordered_set>

# include "Node.hpp"
# include "PriorityQueue.hpp"
# include "myCompare.hpp"

class Astar
{
	public:
		Node *Goal;
		Astar();
		Astar(Node &, Node &, int , bool);
		virtual ~Astar();
		void 													Run();
		void 													ft_display(std::vector< std::vector<int> > , bool) const;
		std::list<Node> 										CreatSuccessor(Node *);
		Node													ft_new_state(Node *n, int x1, int y1, int x2, int y2);
		int 													ft_heuristic(Node n);

		std::pair <int,int>										LookAfter(std::vector<std::vector<int> > tab, int x);
		int														ManhattanDistance(Node);
		int														MisplacedTiles(Node);

		int 													linearConflict(Node n);

		bool													ft_search_in_goal(int tj, int tk, int l);
		
		int 													TOORAC(Node n);
		bool													TOORACsearchX(int val, int line);
		bool													TOORACsearchY(int val, int line);

		bool 													MaxSwapIsBlankInGoalPos(std::vector< std::vector<int> > nodeTab);
		void													MaxSwapGetFirstMismatch(std::vector< std::vector<int> > * nodeTab);
		void 													MaxSwapWithMatched(std::vector< std::vector<int> > * nodeTab);
		int 													MaxSwap(Node n);

		void 													final_rec_display(Node *p, int *i);


	private:
		bool													_isAstar;
		int														_h;
		PriorityQueue < Node, std::vector<Node>, myCompare >	Open;	
		std::multiset <Node>									Close;
		Node *Start;
};

#endif
