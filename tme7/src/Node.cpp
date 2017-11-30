// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/7>" -*-

#include <limits>
#include "XmlUtil.h"
#include "Node.h"
#include "Line.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

namespace Netlist {

    using namespace std;


    const size_t  Node::noid = numeric_limits<size_t>::max();


    Node::Node ( size_t id )
    : id_      (id)
    , position_()
    , lines_   ()
    { }


    Node::~Node ()
    {
        while ( not lines_.empty() ) {
            delete lines_[0];
        }
    }


    void  Node::attach ( Line* line )
    {
        for ( size_t i=0 ; i<lines_.size() ; ++i ) {
            if (lines_[i] == line) return;
        }
        lines_.push_back( line );
    }


    void  Node::detach ( Line* line )
    {
        vector<Line*>::iterator iline = lines_.begin();
        for ( ; iline != lines_.end() ; ++iline ) {
            if ((*iline) == line) {
                lines_.erase( iline );
                break;
            }
        }
    }


    NodePoint::NodePoint ( Net* net, size_t id, Point p )
    : Node(id), net_(net)
    {
        setPosition( p );
        net_->add( this );
    }


    NodePoint::~NodePoint ()
    { net_->remove( this ); }


    Net* NodePoint::getNet () const
    { return net_; }


    void  NodePoint::toXml ( ostream& stream ) const
    {
        stream << indent << "<node x=\""  << position_.getX()
        <<    "\" y=\""  << position_.getY()
        <<    "\" id=\"" << id_ << "\"/>\n";
    }


    NodeTerm::NodeTerm ( Term* term, size_t id )
    : Node(id), term_(term)
    { }


    NodeTerm::~NodeTerm ()
    { if (getNet()) getNet()->remove( this ); }


    Net* NodeTerm::getNet () const
    { return term_->getNet(); }


    void  NodeTerm::toXml ( ostream& stream ) const
    {
        if (term_->isInternal()) {
            stream << indent << "<node term=\"" << term_->getName()
            << "\" instance=\"" << term_->getInstance()->getName()
            << "\" id=\""       << id_;
        } else {
            stream << indent << "<node term=\"" << term_->getName()
            << "\" id=\""       << id_;
        }
        stream << "\" x=\"" << position_.getX() << "\" y=\"" << position_.getY() << "\"/>\n";
    }
    /*    void Node::toXml(std::ostream& s){
    if(term_->isInternal()){
    s<<indent<<"<node term=\""<<term_->getName();s<<"\" instance=\""<<term_->getInstance()->getName();s<<"\" id=\""<<id_;s<<"\"/>"<<std::endl;
}else {
s<<indent<<"<node term=\""<<term_->getName();s<<"\" id=\""<<id_;s<<"\"/>"<<std::endl;
}
}
*/

bool Node::fromXml(Net* net, xmlTextReaderPtr reader){
    const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"node" );
    const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );
    int nodeId = -1;

    //vérification du nom du node actuel par rapport au Tag demandé
    if(nodeTag == nodeName){

        //récupération des attributs
        std::string nodeTerm = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"term" ) );
        std::string nodeInstance = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"instance" ) );
        xmlGetIntAttribute( reader, "id", nodeId );

        //on vérifie que le term n'est pas vide et que l'id du node est positif
        if(nodeTerm.empty() or nodeId<0) return false;

        Term* term = NULL;

        //on test l'existence de l'attribut instance
        if(nodeInstance.empty()){
            //on récupère la cell et on fait la connection
            if( !(net->getCell()->connect(nodeTerm, net)) ) return false;
            term = net->getCell()->getTerm(nodeTerm);
            term->getNode()->setId(nodeId);
        }else {
            //on récuprère l'instance et on fait la connection
            Instance* instance = net->getCell()->getInstance(nodeInstance);
            if( !(instance->connect(nodeTerm, net)) ) return false;
            term = instance->getTerm(nodeTerm);
            term->getNode()->setId(nodeId);
        }
    }
    return true;
}
}  // Netlist namespace.
