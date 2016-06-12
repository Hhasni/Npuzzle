#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <queue>

class Node
{
	public:
		Node();
		Node(int);
		virtual ~Node();
		void 								setTab(std::vector<std::vector<int> >);
		void 								setParent(Node &);
		void 								AddToTab(std::vector<int>);
		void 								incG();

		std::vector< std::vector<int> >		getTab() const;
		std::vector< std::vector<int> >*	getTabad();
		Node* 								getParent();
		int									getH() const;
		int									getG() const;
		int									getF() const;
		void 								setH(int);
		void 								setG(int);
		void 								setF(int);

		bool operator<(const Node& rhs) const ;

	private:
		std::vector<std::vector<int> >		vTab;
		int									g;
		int									h;
		int									f;
		Node* 								Parent;
};

#endif
