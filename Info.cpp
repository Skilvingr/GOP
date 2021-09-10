#include "Info.h"

Log_Widget::Log_Widget(QWidget *parent) : QTextEdit(parent){

    this -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this -> setReadOnly(true);
}

void Log_Widget::mousePressEvent(QMouseEvent *event){
    scrolling = true;
    old_y = event->y();
}

void Log_Widget::mouseMoveEvent(QMouseEvent *event){
    delta_y = (event->y() - old_y) / 3;
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - delta_y);
}

void Log_Widget::mouseReleaseEvent(QMouseEvent *event){
    scrolling = false;
    old_y = event->y();
}


Info::Info(QWidget *parent, QTableWidget *List) : QWidget(parent)
{

    this -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this -> setStyleSheet("background: black"); //Setta lo sfondo con il colore nero

    if (PLATFORM != "Android"){
        List_Widget = List;

        List_Widget -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        List_Widget -> setColumnCount(2);

        List_Widget -> setHorizontalHeaderLabels(QStringList(QList <QString>({"Name", "Current Block"})));

        //Gestione Splitter

        InfoSplitter -> setOrientation(Qt::Vertical); //Orientamento di divisione del widget verticale

        InfoSplitter -> addWidget(List_Widget);

        InfoSplitter -> addWidget(Log_Wid);

        InfoSplitter -> setStretchFactor(0, 1);

        InfoSplitter -> setStretchFactor(1, 2);

        VLayout -> addWidget(InfoSplitter);
    }

    else{
        VLayout -> addWidget(Log_Wid);

        InfoSplitter->~QSplitter();
    }

}
