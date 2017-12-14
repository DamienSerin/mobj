#include<QAbstractTableModel>
#include<vector>
#include<QFont>
#include<QApplication>

#include"Cell.h"
namespace Netlist {


    //class Point;

    class InstancesModel:public QAbstractTableModel {
        Q_OBJECT;
    public:
                    InstancesModel( QObject * parent = NULL );
        virtual     ~InstancesModel();

        void        setCell( Cell * );
        Cell*       getModel( int row );
        int         rowCount( const QModelIndex& parent = QModelIndex()) const ;
        int         columnCount( const QModelIndex& parent = QModelIndex()) const ;
        QVariant    data(const QModelIndex& index, int role = Qt::DisplayRole) const ;
        QVariant    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const ;
    private:
        Cell * cell_ ;
    };
};
