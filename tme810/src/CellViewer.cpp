#include"Cell.h"
#include"CellViewer.h"
#include<QAction>
#include<QMenuBar>
#include<QMenu>
#include"Cell.h"
#include"InstancesWidget.h"

namespace Netlist {

    CellViewer::CellViewer(QWidget * parent):QMainWindow(parent), cellWidget_(NULL), instancesWidget_(NULL), saveCellDialog_(NULL){
        cellWidget_ = new CellWidget();
        saveCellDialog_ = new SaveCellDialog( this );

        instancesWidget_ = new InstancesWidget();

        instancesWidget_->setCellViewer(this);

        setCentralWidget ( cellWidget_ );

        QMenu* fileMenu = menuBar()->addMenu("&File");
        QAction* action = new QAction( "&Save As" , this );

        action->setStatusTip("Save to disk (rename) the Cell" );
        action->setShortcut( QKeySequence ("CTRL+S") );
        action->setVisible( true );

        fileMenu->addAction( action );
        connect( action , SIGNAL( triggered()) , this , SLOT( saveCell()) );

        action = new QAction( "&Open" , this );
        action->setStatusTip( "Open a cell" );
        action->setShortcut( QKeySequence ("CTRL+O") );
        action->setVisible( true );

        fileMenu->addAction( action );
        connect( action , SIGNAL( triggered()) , this , SLOT( openCell()));

        action = new QAction( "&InstancesWidget" , this );
        action->setStatusTip( "Open Instances Widget" );
        action->setShortcut( QKeySequence ("CTRL+I") );
        action->setVisible( true );

        fileMenu->addAction( action );
        connect( action , SIGNAL( triggered()) , this , SLOT( showInstancesWidget() ) );

        action = new QAction( "&Quit" , this );
        action->setStatusTip( "Exit the Netlist Viewer" );
        action->setShortcut( QKeySequence ("CTRL+Q") );
        action->setVisible( true );

        fileMenu->addAction( action );
        connect( action , SIGNAL( triggered()) , this , SLOT( close()) );

    }

    CellViewer::~CellViewer(){}

    void CellViewer::saveCell(){
        Cell* cell = getCell();
        if(cell == NULL) return ;
        QString cellName = cell->getName().c_str();
        if (saveCellDialog_->run(cellName)){
            cell->setName(cellName.toStdString());
            cell->save( cellName.toStdString() );
        }
    }

    void CellViewer::setCell(Cell* cell){
        cellWidget_->setCell(cell);
    }

    Cell* CellViewer::getCell() const {
        return cellWidget_->getCell();
    }

    void CellViewer::openCell(){
        std::cout << "ok" << std::endl;
        QString name;
        if(OpenCellDialog::run(this, name)){
            Cell* cell = Cell::find(name.toStdString());

            if(!cell){
                cell = Cell::load(name.toStdString());
            }
            if(cell){
                setCell(cell);
            }
        }
    }

    void CellViewer::showInstancesWidget(){
        std::cout << "instwidget" << std::endl;
        instancesWidget_->setCell(CellViewer::getCell());
        instancesWidget_->show();
    }
}
