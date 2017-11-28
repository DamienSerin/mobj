#include "Point.h"
#include "Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"
#include "XmlUtil.h"
#include <string>

namespace Netlist {
    Term::Term( Cell* c, const std::string& name, Direction d):owner_(c),name_(name),direction_(d),node_(this,Node::noid){
        type_ = External;
        c->add(this);
    }
    Term::Term( Instance* i, const std::string& name, Direction d):owner_(i),name_(name),direction_(d),node_(this,Node::noid){
        type_ = Internal;
    }

    Term::~Term(){
        if(net_==NULL){return;}
        std::vector <Node*>::iterator it;
        std::vector <Node*> nodz = net_->getNodes();
        for (it = nodz.begin(); it != nodz.end(); ++it){
            nodz.erase(it);
            return;
        }
    }

    Cell* Term::getCell() const{
        return (type_==Internal)?NULL:static_cast<Cell*>(owner_);
    }

    Cell* Term::getOwnerCell() const{
        return (type_==Internal)?static_cast<Cell*>(owner_):(getInstance()->getMasterCell());
    }

    Instance* Term::getInstance() const{
        return (type_==Internal)?static_cast<Instance*>(owner_):NULL;
    }

    void Term::setNet( Net* n){
        net_ = n;
        n->add(&node_);
    }

    void Term::setNet( const std::string& s){
        net_ = getOwnerCell()->getNet(s);
    }

    std::string Term::toString( Term::Type t){
        switch(t){
            case 1: return "Internal";
            case 2: return "External";
            default: return "Unknown";
        }
    }

    std::string Term::toString( Term::Direction d){
        switch(d){
            case 1: return "In";
            case 2: return "Out";
            case 3: return "Inout";
            case 4: return "Tristate";
            case 5: return "Transcv";
            default: return "Unknown";
        }
    }

    Term::Direction Term::toDirection(std::string d){
        if(d == "In") return Term::In;
        if(d == "Out") return Term::Out;
        if(d == "Inout") return Term::Inout;
        if(d == "Tristate") return Term::Tristate;
        if(d == "Transcv") return Term::Transcv;
        return Term::Unknown;
    }

    Term::Type Term::toType(std::string t){
        if(t == "Internal") return Term::Internal;
        else return Term::External;
    }

    void Term::toXml(std::ostream& s){
        Point p = Term::getPosition();
        int x = p.getX();
        int y = p.getY();

        s<<indent<<"<term name=\""<< name_ ;s<< "\" direction=\"" << Term::toString(direction_) ; s<< "\" x=\"" << x ;s<< "\" y=\"" << y ;s<< "\"/>" << std::endl;
    }

    Term* Term::fromXml(Cell* c, xmlTextReaderPtr reader){
        const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );
        Term* term = NULL;

        if(nodeTag == nodeName){

            std::string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
            std::string termDirection = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" ) );
            Direction d = term->toDirection(termDirection);

            if(termName.empty()) return NULL;

            term = new Term(c, termName, d);

            int termX = 0;
            int termY = 0;
            xmlGetIntAttribute( reader, "x", termX );
            xmlGetIntAttribute( reader, "y", termY );
            term->setPosition(termX, termY);
        }
        return term;
    }
}
