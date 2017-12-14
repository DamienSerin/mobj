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

    void  Net::add ( Line* line ){
        if (line)
        lines_.push_back( line );
    }

    Node* Net::getNode( size_t id) const{
        for(int x=0; x<nodes_.size(); x++){
            if(nodes_[x] and (nodes_[x]->getId() == id)){
                return nodes_[x];
            }
        }
        return NULL;
    }


    bool Net::remove(Node* node){
        if(node){
            size_t id = node->getId();
            if((id<nodes_.size()) and (nodes_[id] == node)){
                nodes_[id] = NULL;
                return true;
            }
        }
        return false;
    }

    bool  Net::remove ( Line* line ){
        if (line) {
            for ( vector<Line*>::iterator il = lines_.begin()
            ; il != lines_.end() ; ++il ) {
                if (*il == line) {
                    lines_.erase( il );
                    return true;
                }
            }
        }
        return false;
    }

    void Net::toXml(std::ostream& s){
        s<<indent<<"<net name=\""<<name_;s<<"\" type=\""<<Term::toString(type_);s<<"\">"<<std::endl;
        indent++;
        for(int x=0;x<nodes_.size();x++){
            if(nodes_[x]){nodes_[x]->toXml(s);}
        }
        for(int x=0;x<lines_.size();x++){
            if(lines_[x]){lines_[x]->toXml(s);}
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
            const xmlChar* nTag     = xmlTextReaderConstString        ( reader, (const xmlChar*)"node" );
            const xmlChar* lineTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"line" );


            while(!((nodeTag == nodeName) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))){

                xmlTextReaderRead(reader);

                switch ( xmlTextReaderNodeType(reader) ) {
                    case XML_READER_TYPE_COMMENT:
                    case XML_READER_TYPE_WHITESPACE:
                    case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                    continue;
                }

                const xmlChar* tmpNodeName = xmlTextReaderConstLocalName     ( reader );

                if(tmpNodeName == nTag){
                    if( !(Node::fromXml(net, reader)) ) return NULL;
                }
                if(tmpNodeName == lineTag){
                    if( !(Line::fromXml(net, reader)) ) return NULL;
                }
            }
        }
        return net;
    }
}
