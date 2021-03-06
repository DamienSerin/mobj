#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H

#include <iostream>
#include <vector>
#include <string>
#include <libxml/xmlreader.h>
#include "Indentation.h"

namespace Netlist {

	class Cell;
	class Term;
	class Net;
	class Point;

	class Instance {
		public:
			Instance(Cell* owner, Cell* model, const std::string&);
			~Instance();

			inline 	const std::string& 				getName			() 						const;
			inline 	Cell* 							getMasterCell	() 						const;
			inline 	Cell* 							getCell			() 						const;
			inline 	const std::vector<Term*>& 		getTerms		() 						const;
					Term* 							getTerm			(const std::string&) 	const;
			inline 	Point 							getPosition		() 						const;

			inline	void 							setPosition		(const Point&);
			inline	void 							setPosition		(int x, int y);

					bool 							connect			(const std::string& name, Net*);
					void 							add				(Term*);
					void 							remove			(Term*);

			static 	Instance* 						fromXml			(Cell*, xmlTextReaderPtr);
					void 							toXml			(std::ostream&);

		private:
			Cell* 					owner_;
			Cell* 					masterCell_;
			std::string 			name_;
			std::vector<Term*>		terms_;
			Point 					position_;
	};

	inline const 	std::string& 		Instance::getName		() const {return name_;}
	inline 			Cell* 				Instance::getMasterCell	() const {return masterCell_;}
	inline 			Cell* 				Instance::getCell		() const {return owner_;}
	inline const 	std::vector<Term*>& Instance::getTerms		() const {return terms_;}
	inline 			Point 				Instance::getPosition	() const {return position_;}

	inline			void 				Instance::setPosition	(const Point& p){position_ = p;}
	inline 			void 				Instance::setPosition	(int x, int y){position_ = Point(x,y);}
}

#endif
