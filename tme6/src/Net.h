#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include <limits>
#include <iostream>
#include <vector>
#include "Term.h"
#include <libxml/xmlreader.h>

namespace Netlist {

	class Cell;
	class Node;

	class  Net {
		public:
			Net(Cell*, const std::string& name,Term::Type dir);
			Net(Instance*, const std::string& name,Term::Type dir);
			~Net();

			Cell* 						getCell			() 			const;
			const std::string& 			getName			() 			const;
			unsigned int 				getId			() 			const;
			Term::Type 					getType			() 			const;
			Node* 						getNode			(size_t id) const;
			const std::vector<Node*>&	getNodes		() 			const;
			size_t 						getFreeNodeId	() 			const;

			void 						add 			(Node*);
			bool 						remove			(Node*);

			void 						toXml			(std::ostream&);
	static  Net*						fromXml			(Cell*, xmlTextReaderPtr);
		private:
			Net (const Net&);
			Cell*					owner_;
			const std::string 		name_;
			Term::Type 				type_;
			unsigned int 			id_;
			std::vector<Node*> 		nodes_;
	};

}

#endif
