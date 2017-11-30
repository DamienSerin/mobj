// -*- explicit-buffer-name: "Term.h<M1-MOBJ/4-5>" -*-

#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include <iostream>
#include <libxml/xmlreader.h>
#include <string>
#include "Indentation.h"
#include "Node.h"

namespace Netlist {

	class Net;
	class Cell;
	class Instance;

	class Term{

	public:
		enum Type 		{
			Internal=1,
			External=2,
		};
		enum Direction 	{
			In=1,
			Out=2,
			Inout=3,
			Tristate=4,
			Transcv=5,
			Unknown=6
		};

		Term(Cell*, const std:: string& name, Direction);
		Term(Instance*, const std:: string& name, Direction);
		~Term();

		static 	std::string 			toString    	(Type);
		static 	std::string  			toString    	(Direction);
		static 	Direction    			toDirection		(std::string);
		static 	Type					toType			(std::string);
		static 	Term* 					fromXml			(Cell*, xmlTextReaderPtr);

		inline	bool					isInternal		()	const;
		inline	bool					isExternal		()	const;

		inline	const std::string&		getName			() const;
		inline	Node* 					getNode 		();
		inline	Net* 					getNet 			() const;
				Cell* 					getCell			() const;
				Cell* 					getOwnerCell 	() const;
				Instance* 				getInstance 	() const;
		inline	Direction 				getDirection 	() const;
		inline	Point 					getPosition 	() const;
		inline	Type 					getType 		() const;

				void 					setNet 			(Net*);
				void 					setNet 			(const std::string&);
				void 					setDirection	(Direction);
				void 					setPosition		(const Point&);
				void 					setPosition		(int x, int y);

				void 					toXml			(std::ostream&);

	private:
		void* 			owner_;
		std::string 	name_;
		Direction 		direction_;
		Type 			type_;
		Net* 			net_;
		Node 			node_;

	};

	inline			bool 				Term::isInternal	() const	{return (type_==Internal)?true:false;}
	inline			bool 				Term::isExternal	() const	{return (type_==External)?true:false;}
	inline	const 	std::string& 		Term::getName		() const	{return name_;}
	inline			Net*				Term::getNet		() const	{return net_;}
	inline			Node* 				Term::getNode		()			{return &node_;}
	inline			Term::Direction 	Term::getDirection	() const	{return direction_;}
	inline			Point				Term::getPosition	() const	{return node_.getPosition();}
	inline			Term::Type 			Term::getType		() const	{return type_;}

	inline			void 				Term::setPosition	( const Point& p){node_.setPosition(p);}
	inline			void 				Term::setPosition	( int x, int y){node_.setPosition(x,y);}
	inline			void 				Term::setDirection	( Direction d){direction_ = d;}

} // Netlist namespace.

#endif  // NETLIST_TERM_H
