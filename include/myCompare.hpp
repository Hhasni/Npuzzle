
#ifndef MYCOMPARE_HPP
# define MYCOMPARE_HPP

class myCompare
{
	public:
		bool operator() (Node obj1, Node obj2)
		{
			if (obj1.getF() == obj2.getF())
				return(obj1.getG() < obj2.getG());
			return (obj1.getF() > obj2.getF());
		}
};

#endif
