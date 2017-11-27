#include "Point.h"
#include "Instance.h"
#include "Cell.h"
#include "Term.h"
#include "XmlUtil.h"
#include <string>

namespace Netlist {
  Instance::Instance(Cell* owner, Cell* model, const std::string& name):owner_(owner),masterCell_(model),name_(name){
    owner->add(this);
    for(std::vector<Term*>::const_iterator x = model->getTerms().begin(); x != model->getTerms().end();x++){
      add(new Term(this,(*x)->getName(),(*x)->getDirection()));
    }
  }

  Instance::~Instance(){}

  const std::string& Instance::getName() const{
    return name_;
  }

  Cell* Instance::getMasterCell() const{
    return masterCell_;
  }

  Cell* Instance::getCell() const{
    return owner_;
  }

  const std::vector<Term*>& Instance::getTerms() const{
    return terms_;
  }

  Term* Instance::getTerm( const std::string& s) const{
    for(std::vector<Term*>::const_iterator x = terms_.begin() ; x != terms_.end();x++){
      if((*x)->getName() == s){return (*x);}
    }
    return NULL;
  }

  Point Instance::getPosition() const{
    return position_;
  }

  bool Instance::connect(const std::string& name, Net* n){
    Term* x;
    if((x = getTerm(name))==NULL){
      std::cerr<<" [ERROR]["<<name_;std::cerr<<"] Couldnt find "<<name;std::cerr<<std::endl;
      return false;
    }
    x->setNet(n);
    return true;

  }

  void Instance::add( Term* t){
    terms_.push_back(t);
  }

  void Instance::remove( Term* t){
    for(std::vector<Term*>::iterator x = terms_.begin();x != terms_.end();x++){
      if((*x) == t){terms_.erase(x);}
    }
    return;
  }

  void Instance::setPosition( const Point& p){
    position_ = p;
  }

  void Instance::setPosition( int x, int y){
    position_ = Point(x,y);
  }

  void Instance::toXml(std::ostream& s){
    s<<indent<<"<instance name=\""<<name_;s<<"\" mastercell=\""<<masterCell_->getName();s<<"\" x=\""<< position_.getX();s<<"\" y=\""<< position_.getY()<<"\" />"<< std::endl;
  }

  Instance* Instance::fromXml(Cell* c, xmlTextReaderPtr reader){
      const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"instance" );
      const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

      Cell* mastercell = NULL;
      Instance* instance = NULL;
      if(nodeTag == nodeName){

          std::string instanceName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
          std::string mastercellName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) );
          mastercell = mastercell->find(mastercellName);
          // Net::fromXml(Cell, reader);
          instance = new Instance(c, mastercell, instanceName);
          instance->toXml(std::cout);
          return instance;
      }
      return NULL;
  }

}
