#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"CellWidget.h"

namespace Netlist {

    class OpenCellDialog:public QDialog {
        Q_OBJECT ;
    public:
                            OpenCellDialog  ( QWidget * parent = NULL );
        static  bool        run             (QWidget* parent, QString& name );
        const   QString     getCellName     () const ;
                void        setCellName     ( const QString & );
    protected:
        QLineEdit * lineEdit_ ;
    };
}
