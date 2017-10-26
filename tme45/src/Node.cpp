// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();


  Node::Node ( Term* term, size_t id  )
    : id_      (id)
    , term_    (term)
    , position_()
  { }


  Node::~Node ()
  {
    if (getNet()) getNet()->remove( this );
  }


  inline Net* Node::getNet () const { return term_->getNet(); }


  void Node::toXml(std::ostream& s){
      std::string ins;
      s<<indent<<"<node term=\""<<term_->getName();s<<"\" id=\""<<id_;s<<"\" x=\""<<position_.getX();s<<"\" y=\""<<position_.getY();s<<"\" />"<<std::endl;
  }


}  // Netlist namespace.
