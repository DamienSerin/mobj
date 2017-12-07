#include"Symbol.h"
#include"Shape.h"
#include "XmlUtil.h"
#include "Cell.h"

namespace Netlist{

    Symbol::Symbol(Cell* owner):owner_(owner),shapes_(){}
    Symbol::~Symbol(){}

    Box Symbol::getBoundingBox() const {
        Box bb;
        std::vector<Shape*>::const_iterator ishape=shapes_.begin();
        for( ;ishape!=shapes_.end(); ++ishape){
            bb.merge((*ishape)->getBoundingBox());
        }
        return bb;
    }

    Cell* Symbol::getCell() const {
        return owner_;
    }

    TermShape* Symbol::getTermShape(Term* term) const {
        for(size_t i = 0; i<shapes_.size(); ++i){
            TermShape* termShape = dynamic_cast<TermShape*>(shapes_[i]);
            if(termShape and (termShape->getTerm() == term))
            return termShape;
        }
    }

    Point Symbol::getTermPosition(Term* term) const {
        TermShape* termShape = Symbol::getTermShape(term);
        if(termShape)
        return Point(termShape->getX(), termShape->getY());
        return Point();
    }

    void Symbol::add(Shape* shape){
        if(shape)
        shapes_.push_back(shape);
    }

    void Symbol::remove(Shape* shape){
        if(shape){
            for(std::vector<Shape*>::iterator ishape = shapes_.begin(); ishape != shapes_.end(); ++ishape){
                if(*ishape == shape)
                shapes_.erase(ishape);
            }
        }
    }

    void Symbol::toXml(std::ostream& stream) const {
        stream<<indent<<"<symbol>"<<std::endl;
        indent++;
        for(int x=0;x<shapes_.size();x++){
            TermShape* termShape = dynamic_cast<TermShape*>(shapes_[x]);
            if(termShape) termShape->toXml(stream);

            BoxShape* boxShape = dynamic_cast<BoxShape*>(shapes_[x]);
            if(boxShape) boxShape->toXml(stream);

            LineShape* lineShape = dynamic_cast<LineShape*>(shapes_[x]);
            if(lineShape) lineShape->toXml(stream);

            ArcShape* arcShape = dynamic_cast<ArcShape*>(shapes_[x]);
            if(arcShape) arcShape->toXml(stream);

            EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>(shapes_[x]);
            if(ellipseShape) ellipseShape->toXml(stream);
        }
        indent--;
        stream<<indent<<"</symbol>"<<std::endl;
    }

    Symbol* Symbol::fromXml(Cell* c, xmlTextReaderPtr reader){
        const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"symbol" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

        Symbol* symbol = c->getSymbol();
        Shape* shape = NULL;


        while(true){
            //on fait avancer le pointeur


            xmlTextReaderRead(reader);
            nodeName = xmlTextReaderConstLocalName     ( reader );
            if(nodeTag == nodeName){break;}

            switch ( xmlTextReaderNodeType(reader) ) {
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            }

            shape->fromXml(symbol, reader);
            if(shape) symbol->add(shape);
            //std::cout << "-----" << std::endl;
            //symbol->toXml(std::cout);

        }
        return symbol;
    }

}
