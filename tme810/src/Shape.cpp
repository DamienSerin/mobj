#include"Symbol.h"
#include"Shape.h"
#include"Cell.h"
#include "XmlUtil.h"
#include"Term.h"

namespace Netlist{

    Shape::Shape(Symbol* owner):owner_(owner){
        owner->add(this);
    }

    Shape::~Shape(){
        owner_->remove(this);
    }

    Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader ){
        // Factory-like method.

        const xmlChar* boxTag
        = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
        const xmlChar* ellipseTag
        = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
        const xmlChar* arcTag
        = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
        const xmlChar* lineTag
        = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
        const xmlChar* termTag
        = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName
        = xmlTextReaderConstLocalName( reader );

        Shape* shape = NULL;
        if (boxTag == nodeName)
            shape = BoxShape::fromXml( owner, reader );
        if (ellipseTag == nodeName)
            shape = EllipseShape::fromXml( owner, reader );
        if (arcTag == nodeName)
            shape = ArcShape::fromXml( owner, reader );
        if (lineTag == nodeName)
            shape = LineShape::fromXml( owner, reader );
        if (termTag == nodeName)
            shape = TermShape::fromXml( owner, reader );

        if (shape == NULL)
            std::cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
            << xmlTextReaderGetParserLineNumber(reader) << ")." << std::endl;

        return shape;
    }

    BoxShape::BoxShape(Symbol* owner, const Box& box):Shape(owner), box_(box){}
    BoxShape::BoxShape(Symbol* owner, int x1 , int y1 , int x2 , int y2):Shape(owner){
        box_ = Box(x1,y1,x2,y2);
    }
    BoxShape::~BoxShape(){}

    Box BoxShape::getBoundingBox() const {
        return box_;
    }

    void BoxShape::toXml(std::ostream& stream){
        stream << indent << "<box x1=\"" << box_.getX1()
                         << "\" y1=\""   << box_.getY1()
                         << "\" x2=\""   << box_.getX2()
                         << "\" y2=\""   << box_.getY2() << "\"/>" << std::endl;
    }

    BoxShape* BoxShape::fromXml(Symbol* symbol, xmlTextReaderPtr reader){
        const xmlChar* boxTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"box" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName    ( reader );

        BoxShape* boxShape = NULL;

        if(boxTag == nodeName){
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            xmlGetIntAttribute(reader, "x1", x1);
            xmlGetIntAttribute(reader, "y1", y1);
            xmlGetIntAttribute(reader, "x2", x2);
            xmlGetIntAttribute(reader, "y2", y2);

            boxShape = new BoxShape(symbol, x1, y1, x2, y2);
        }
        return boxShape;
    }

    TermShape::TermShape(Symbol* owner, std::string name, int x1, int y1):Shape(owner), term_(NULL), x1_(x1), y1_(y1){
        Cell* cell = owner->getCell();
        term_ = cell->getTerm(name);
    }
    TermShape::~TermShape(){}

    Box TermShape::getBoundingBox() const {
        return Box(x1_, y1_, x1_, y1_);
    }

    std::string TermShape::toString(TermShape::NameAlign n){
        switch(n){
            case 1: return "top_left";
            case 2: return "top_right";
            case 3: return "bottom_left";
            case 4: return "bottom_right";
            default: return "Unknown";
        }
    }

    TermShape::NameAlign TermShape::toAlign(std::string s){
        if(s == "top_left") return TermShape::TopLeft;
        if(s == "top_right") return TermShape::TopRight;
        if(s == "bottom_left") return TermShape::BottomLeft;
        if(s == "bottom_right") return TermShape::BottomRight;
    }

    void TermShape::toXml(std::ostream& stream){
        stream << indent << "<term name=\"" << term_->getName()
                         << "\" x1=\""      << TermShape::getX()
                         << "\" y1=\""      << TermShape::getY()
                         << "\" align=\""   << TermShape::toString(align_) << "\"/>" << std::endl;
    }

    TermShape* TermShape::fromXml(Symbol* symbol, xmlTextReaderPtr reader){
        const xmlChar* termTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

        TermShape* termShape = NULL;

        if(nodeName == termTag){
            int x1 = 0;
            int y1 = 0;
            std::string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
            std::string termAlign = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) );
            NameAlign nameAlign = termShape->toAlign(termAlign);
            xmlGetIntAttribute( reader, "x1", x1 );
            xmlGetIntAttribute( reader, "y1", y1 );

            termShape = new TermShape(symbol, termName, x1, y1);
            termShape->setAlign(nameAlign);
        }
        return termShape;
    }

    LineShape::LineShape(Symbol* owner, int x1, int y1, int x2, int y2):Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2){}
    LineShape::~LineShape(){}

    Box LineShape::getBoundingBox() const {
        return Box(x1_, y1_, x2_, y2_);
    }

    void LineShape::toXml(std::ostream& stream){
        stream << indent << "<line x1=\"" << x1_
                         << "\" y1=\""    << y1_
                         << "\" x2=\""    << x2_
                         << "\" y2=\""    << y2_ << "\"/>" << std::endl;
    }

    LineShape* LineShape::fromXml(Symbol* symbol, xmlTextReaderPtr reader){
        const xmlChar* lineTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"line" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

        LineShape* lineShape = NULL;

        if(nodeName == lineTag){
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            xmlGetIntAttribute(reader, "x1", x1);
            xmlGetIntAttribute(reader, "y1", y1);
            xmlGetIntAttribute(reader, "x2", x2);
            xmlGetIntAttribute(reader, "y2", y2);

            lineShape = new LineShape(symbol, x1, y1, x2, y2);
        }
        return lineShape;
    }

    ArcShape::ArcShape(Symbol* owner, const Box& box, int startAngle, int spanAngle):Shape(owner), box_(box), startAngle_(startAngle), spanAngle_(spanAngle){}
    ArcShape::ArcShape(Symbol* owner, int x1, int y1, int x2, int y2, int startAngle, int spanAngle):Shape(owner), startAngle_(startAngle), spanAngle_(spanAngle){
        box_ = Box(x1,y1,x2,y2);
    }
    ArcShape::~ArcShape(){}
    Box ArcShape::getBoundingBox() const{
        return box_;
    }

    void ArcShape::toXml(std::ostream& stream){
        stream << indent << "<arc x1=\""  << box_.getX1()
                         << "\" y1=\""    << box_.getY1()
                         << "\" x2=\""    << box_.getX2()
                         << "\" y2=\""    << box_.getY2()
                         << "\" start=\"" << startAngle_
                         << "\" span=\""  << spanAngle_ << "\"/>" << std::endl;
    }

    ArcShape* ArcShape::fromXml(Symbol* symbol, xmlTextReaderPtr reader){
        const xmlChar* arcTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"arc" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName    ( reader );
        ArcShape* arcShape = NULL;

        if(nodeName == arcTag){
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;
            int start = 0;
            int span = 0;

            xmlGetIntAttribute(reader, "x1", x1);
            xmlGetIntAttribute(reader, "y1", y1);
            xmlGetIntAttribute(reader, "x2", x2);
            xmlGetIntAttribute(reader, "y2", y2);
            xmlGetIntAttribute(reader, "start", start);
            xmlGetIntAttribute(reader, "span", span);

            arcShape = new ArcShape(symbol, x1, y1, x2, y2, start, span);
        }
        return arcShape;
    }

    EllipseShape::EllipseShape(Symbol* owner, const Box& box):Shape(owner), box_(box){}
    EllipseShape::EllipseShape(Symbol* owner, int x1, int y1, int x2, int y2):Shape(owner){
        box_ = Box (x1,y1,x2,y2);
    }
    EllipseShape::~EllipseShape(){}

    Box EllipseShape::getBoundingBox() const {
        return box_;
    }

    void EllipseShape::toXml(std::ostream& stream){
        stream << indent << "<ellipse x1=\"" << box_.getX1()
                         << "\" y1=\""       << box_.getY1()
                         << "\" x2=\""       << box_.getX2()
                         << "\" y2=\""       << box_.getY2() << "\"/>" << std::endl;
    }

    EllipseShape* EllipseShape::fromXml(Symbol* symbol, xmlTextReaderPtr reader){
        const xmlChar* ellipseTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"ellipse" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName        ( reader );

        EllipseShape* ellipseShape = NULL;

        if(ellipseTag == nodeName){
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            xmlGetIntAttribute(reader, "x1", x1);
            xmlGetIntAttribute(reader, "y1", y1);
            xmlGetIntAttribute(reader, "x2", x2);
            xmlGetIntAttribute(reader, "y2", y2);

            ellipseShape = new EllipseShape(symbol, x1, y1, x2, y2);
        }
        return ellipseShape;
    }
}
