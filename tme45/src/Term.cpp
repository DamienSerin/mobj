#include "Point.h"
#include "Term.h"
#include "Cell.h"
#include "Instance.h"
#include "Net.h"

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

  bool Term::isInternal() const{
    return (type_==Internal)?true:false;
  }

  bool Term::isExternal() const{
    return (type_==External)?true:false;
  }

  const std::string& Term::getName() const{
    return name_;
  }

  Net* Term::getNet() const{
    return net_;
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

  Term::Direction Term::getDirection() const{
    return direction_;
  }

  Point Term::getPosition() const{
    return node_.getPosition();
  }

  Term::Type Term::getType() const{
    return type_;
  }

  void Term::setNet( Net* n){
    net_ = n;
    n->add(&node_);
  }

  void Term::setNet( const std::string& s){
    net_ = getOwnerCell()->getNet(s);
  }

  void Term::setPosition( const Point& p){
    node_.setPosition(p);
  }

  void Term::setPosition( int x, int y){
    node_.setPosition(x,y);
  }

  void Term::setDirection( Direction d){
    direction_ = d;
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

  /*static Term::Direction toDirection( std::string d){
    switch(d){
      case "In": return Term::Direction::In;
      case "Out": return Term::Direction::Out;
      case "Inout": return Direction::Inout;
      case "Tristate": return Direction::Tristate;
      case "Transcv": return Direction::Transcv;
      default: return Direction::Unknown;
    }
*/
    void Term::toXml(std::ostream& s){
      s<<indent<<"<term name=\""<< name_ ;s<< "\" direction=\"" << Term::toString(direction_) ; s<< "\" />" << std::endl;
    }
}
