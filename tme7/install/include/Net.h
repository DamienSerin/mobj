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

			inline 			Cell* 						getCell			() 			const;
			inline 	const 	std::string& 				getName			() 			const;
			inline 			unsigned int 				getId			() 			const;
			inline 			Term::Type 					getType			() 			const;
			inline 			Node* 						getNode			(size_t id) const;
			inline 	const 	std::vector<Node*>&			getNodes		() 			const;
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

	inline Cell* Net::getCell() const{return owner_;}
	inline const std::string& Net::getName() const{return name_;}
	inline unsigned int Net::getId() const{return id_;}
	inline Term::Type Net::getType() const{return type_;}
	inline Node* Net::getNode( size_t id) const{return nodes_[id];}
	inline const std::vector <Node*>& Net::getNodes() const{return nodes_;}
}

#endif
