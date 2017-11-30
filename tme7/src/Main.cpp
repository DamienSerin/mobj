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
using namespace Netlist;


int main ( int argc, char* argv[] )
{
    cout << "Chargement des modeles..." << endl;
    Cell::load( "vdd" );
    Cell::load( "gnd" );
    Cell::load( "TransistorN" );
    Cell::load( "TransistorP" );
    Cell::load( "and2" );
    Cell::load( "or2" );
    Cell* xor2      = Cell::load( "xor2" );
    Cell* halfadder = Cell::load( "halfadder" );
    
    cout << "\nContenu du <xor2>:" << endl;
    xor2->toXml( cout );

    cout << "\nContenu du <halfadder>:" << endl;
    halfadder->toXml( cout );

    return 0;

    /*
    cout << "- <and2> ..." << endl;
    Cell::load( "and2" );

    cout << "- <or2> ..." << endl;
    Cell::load( "or2" );

    cout << "- <xor2> ..." << endl;
    Cell::load( "xor2" );

    cout << "- <halfadder> ..." << endl;
    Cell* halfadder = Cell::load( "halfadder" );

    cout << "\nContenu du <halfadder>:\n" << endl;
    halfadder->toXml( cout );

    return 0;
    */
}
