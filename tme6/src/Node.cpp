// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"
#include "XmlUtil.h"

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
        if(term_->isInternal()){
            s<<indent<<"<node term=\""<<term_->getName();s<<"\" instance=\""<<term_->getInstance()->getName();s<<"\" id=\""<<id_;s<<"\"/>"<<std::endl;
        }else {
            s<<indent<<"<node term=\""<<term_->getName();s<<"\" id=\""<<id_;s<<"\"/>"<<std::endl;
        }
    }

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
