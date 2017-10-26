#include "Node.h"
#include "Instance.h"
#include "Net.h"
#include "Cell.h"

using namespace std;

namespace Netlist {
  Net::Net( Cell* s, const std::string& name,Term::Type dir):owner_(s),name_(name),type_(dir),id_(s->newNetId()){
    //cerr << "net::net " << (void*)this << endl;
    s->add(this);
  }


  Net::~Net(){}

  Cell* Net::getCell() const{
    return owner_;
  }

  const std::string& Net::getName() const{
    return name_;
  }

  unsigned int Net::getId() const{
    return id_;
  }

  Term::Type Net::getType() const{
    return type_;
  }

  Node* Net::getNode( size_t id) const{
    return nodes_[id];
  }

  const std::vector <Node*>& Net::getNodes() const{
    return nodes_;
  }

  size_t Net::getFreeNodeId() const{
    for(int x=0;x<nodes_.size();x++){
      if(!nodes_[x]){return x;}
    }
    return -1;
  }

  void Net::add( Node* n){
    //std::cerr<<"["<<name_;std::cerr<<"] adding node (from term) "<<n->getTerm()->getName();std::cerr<<std::endl;
    if(n->getId() && (n->getId() < nodes_.size()) && !nodes_[n->getId()] ){
      //std::cerr<<" Using choosen free id "<<n->getId();std::cerr<<std::endl;
      nodes_[n->getId()]=n;
    }
    else{
      int x = Net::getFreeNodeId();
      if(x == -1){
        // If no existing and free, create new
        int i = nodes_.size();
        //std::cerr<<" Adding new space id "<<i;std::cerr<<std::endl;
        nodes_.push_back(n);
        n->setId(i);
      }
      else{
        //std::cerr<<" Using first free id "<<x;std::cerr<<std::endl;
        nodes_[x]=n;
        n->setId(x);
      }
    }
  }

  bool Net::remove( Node* n){
    if(nodes_[n->getId()]!=n){
      //std::cerr<<"Net::remove: Unknown node";
      return false;
    }
    nodes_[n->getId()]=NULL;
    n->setId(0);
    n->getTerm()->setNet(NULL);
    return true;
  }

  void Net::toXml(std::ostream& s){
    s<<indent<<"<net name=\""<<name_;s<<"\" type=\""<<Term::toString(type_);s<<"\" >"<<std::endl;
    indent++;
    //std::cerr<<"Nodes: "<<nodes_.size();std::cerr<<std::endl;
    for(int x=0;x<nodes_.size();x++){
      if(nodes_[x]){nodes_[x]->toXml(s);}
    }
    indent--;
    s<<indent<<"</net>"<<std::endl;
  }
}
