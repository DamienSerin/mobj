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

    Term* Instance::getTerm( const std::string& s) const{
        for(std::vector<Term*>::const_iterator x = terms_.begin() ; x != terms_.end();x++){
            if((*x)->getName() == s){return (*x);}
        }
        return NULL;
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

    void Instance::toXml(std::ostream& s){
        s<<indent<<"<instance name=\""<<name_;s<<"\" mastercell=\""<<masterCell_->getName();s<<"\" x=\""<< position_.getX();s<<"\" y=\""<< position_.getY()<<"\"/>"<< std::endl;
    }

    Instance* Instance::fromXml(Cell* c, xmlTextReaderPtr reader){
        const xmlChar* nodeTag  = xmlTextReaderConstString        ( reader, (const xmlChar*)"instance" );
        const xmlChar* nodeName = xmlTextReaderConstLocalName     ( reader );

        Instance* instance = NULL;

        //vérification du nom du node actuel par rapport au Tag demandé
        if(nodeTag == nodeName){

            //récupération des attributs
            std::string instanceName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
            std::string mastercellName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) );

            //test si nom de l'instance ou de la mastercell est vide
            if( instanceName.empty() or mastercellName.empty() ) return NULL;

            //création de l'instance
            Cell* mastercell = mastercell->find(mastercellName);
            instance = new Instance(c, mastercell, instanceName);

            //ajoute de la position
            int instanceX = 0;
            int instanceY = 0;
            xmlGetIntAttribute( reader, "x", instanceX );
            xmlGetIntAttribute( reader, "y", instanceY );
            instance->setPosition(instanceX, instanceY);
        }
        return instance;
    }
}
