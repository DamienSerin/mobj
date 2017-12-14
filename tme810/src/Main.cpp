// -*- explicit-buffer-name: "Main.cpp<M1-MOBJ/4-5>" -*-

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

#include <QApplication>
#include <QtGui>
#include "CellViewer.h"

using namespace Netlist;



int main ( int argc , char * argv []) {

    cout << "Chargement des modeles..." << endl;
    Cell* vdd = Cell::load( "vdd" );
    //vdd->toXml(cout);
    Cell* gnd = Cell::load( "gnd" );
    //gnd->toXml(cout);

    Cell* TransistorN = Cell::load( "TransistorN" );
    //TransistorN->toXml(cout);
    Cell* TransistorP = Cell::load( "TransistorP" );
    //TransistorP->toXml(cout);

    Cell* and2 = Cell::load( "and2" );
    //and2->toXml(cout);
    Cell* or2 = Cell::load( "or2" );
    //or2->toXml(cout);

    Cell* xor2      = Cell::load( "xor2" );
    Cell* halfadder = Cell::load( "halfadder" );

    //cout << "\nContenu du <xor2>:" << endl;
    //xor2->toXml( cout );

    //cout << "\nContenu du <halfadder>:" << endl;
    //halfadder->toXml( cout );


    QApplication* qa = new QApplication( argc , argv );
    CellViewer* viewer = new CellViewer();

    viewer->setCell( halfadder );
    viewer->show();

    int rvalue = qa->exec ();

    delete qa;
    return rvalue;
}
