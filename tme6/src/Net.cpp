#include "Node.h"
#include "Instance.h"
#include "Net.h"
#include "Cell.h"
#include "XmlUtil.h"

using namespace std;

namespace Netlist {
    Net::Net( Cell* s, const std::string& name,Term::Type dir):owner_(s),name_(name),type_(dir),id_(s->newNetId()){
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
        if(n->getId() && (n->getId() < nodes_.size()) && !nodes_[n->getId()] ){
            nodes_[n->getId()]=n;
        }
        else{
            int x = Net::getFreeNodeId();
            if(x == -1){
                // If no existing and free, create new
                int i = nodes_.size();
                nodes_.push_back(n);
                n->setId(i);
            }
            else{
                nodes_[x]=n;
                n->setId(x);
            }
        }
    }

    bool Net::remove( Node* n){
        if(nodes_[n->getId()]!=n){
            return false;
        }
        nodes_[n->getId()]=NULL;
        n->setId(0);
        n->getTerm()->setNet(NULL);
        return true;
    }

    void Net::toXml(std::ostream& s){
        s<<indent<<"<net name=\""<<name_;s<<"\" type=\""<<Term::toString(type_);s<<"\">"<<std::endl;
        indent++;
        for(int x=0;x<nodes_.size();x++){
            if(nodes_[x]){nodes_[x]->toXml(s);}
        }
        indent--;
        s<<indent<<"</net>"<<std::endl;
    }

    Net* Net::fromXml(Cell* c, xmlTextReaderPtr reader){
        Net* net = NULL;

        const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"net" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

        if((nodeTag == nodeName) and !(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))
        {
            std::string netName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
            std::string netType = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" ) );

            Term::Type t = Term::toType(netType);
            net = new Net(c, netName, t);

            while(!((nodeTag == nodeName) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))){
                xmlTextReaderRead(reader);
                if( !(Node::fromXml(net, reader)) ) return NULL;
            }
        }
        return net;
    }
}
