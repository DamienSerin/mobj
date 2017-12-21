#include<QAbstractTableModel>
#include<vector>
#include<QFont>
#include<QApplication>

#include"Cell.h"

namespace Netlist {


    //class Point;

    class CellsModel:public QAbstractTableModel {
        Q_OBJECT;
    public:
                    CellsModel( QObject * parent = NULL );
        virtual     ~CellsModel();

        void        setCell( Cell * );
        Cell*       getModel( int row );
        int         rowCount( const QModelIndex& parent = QModelIndex()) const ;
        int         columnCount( const QModelIndex& parent = QModelIndex()) const ;
        QVariant    data(const QModelIndex& index, int role = Qt::DisplayRole) const ;
        QVariant    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const ;

        public slots:
            void        updateDatas();
    private:
        Cell* cell_ ;
    };
};
