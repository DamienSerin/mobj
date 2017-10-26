// -*- explicit-buffer-name: "Term.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include <iostream>
#include "Indentation.h"
#include "Node.h"

namespace Netlist {

	class Net;
	class Cell;
	class Instance;

	class Term{

		public:
			enum Type 		{Internal=1, External=2};
			enum Direction 	{In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6};

			Term(Cell*, const std:: string& name, Direction);
			Term(Instance*, const std:: string& name, Direction);
			~Term();

			static std::string 			toString    	(Type);
			static std::string  		toString    	(Direction);
			static Direction    		toDirection		(std::string);

			 	   bool					isInternal		()	const;
			 	   bool					isExternal		()	const;
			 	   const std::string&	getName			() const;
			 	   Node* 				getNode 		() const;
			 	   Net* 				getNet 			() const;
				   Cell* 				getCell			() const;
			       Cell* 				getOwnerCell 	() const;
			 	   Instance* 			getInstance 	() const;
			 	   Direction 			getDirection 	() const;
			 	   Point 				getPosition 	() const;
			 	   Type 				getType 		() const;

				   void 				setNet 			(Net*);
				   void 				setNet 			(const std::string&);
				   void 				setDirection	(Direction);
				   void 				setPosition		(const Point&);
				   void 				setPosition		(int x, int y);
				   void 				toXml			(std::ostream&);

		private:
			void* 			owner_;
			std::string 	name_;
			Direction 		direction_;
			Type 			type_;
			Net* 			net_;
			Node 			node_;

	};

} // Netlist namespace.

#endif  // NETLIST_TERM_H
