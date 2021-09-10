#include "Init_Form.h"
#include "Game_Engine.h"


Init_Form::Init_Form()
{
    Game_Window -> addWidget(Campo);

    Campo -> draw_blocks();

    Game_Window -> showMaximized();

    bool ok; //Indica se l'utente ha inserito il numero di giocatori

    this -> setMinimumSize(Screen -> size() / 2); //Imposta la dimensione della finestra a metà di quella dello schermo

    Gamers_Input -> setMinimumSize(Screen -> size() / 3);

    if(PLATFORM == "Android")
        gamers_counter = Gamers_Input -> getInt(this, tr("Gamers"), tr("How many gamers are you? (Max 4)"), 2, 2, 4, 1, &ok); //Fa spawnare una dialog per

    else
        gamers_counter = Gamers_Input -> getInt(this, tr("Gamers"), tr("How many gamers are you?"), 2, 2, 2147483647, 1, &ok); //Fa spawnare una dialog per

    Lists_Creator(); //Richiama il  creatore delle liste(Gestione e Visualizzazione)

    Gamers_Editor(); //Richiama l'editor per modificare le proprietà dei giocatori

    Game_Window -> setAttribute(Qt::WA_DeleteOnClose);
}


void Init_Form::Lists_Creator()
{

    List_Widget -> setRowCount(gamers_counter); //Imposta un numero di righe pari a quello dei giocatori

    List_Widget -> setColumnCount(1); //Imposta una colonna di default (nome ed avatar), l'altra verrà aggiunta successivamente

    List_Widget -> setShowGrid(false); //Imposta la griglia a 'non visibile'

    List_Widget -> setHorizontalHeaderLabels(QStringList(QList <QString> ({"Name"}))); //Imposta la stringa "Name" come header per la colonna

    List_Widget -> setSelectionBehavior(QAbstractItemView::SelectRows); //Restringe la selezione possibile alle sole righe

    List_Widget -> setSelectionMode(QAbstractItemView::SingleSelection); //Restringe la selezione possibile ad una sola riga per volta

    List_Widget -> setEditTriggers(QAbstractItemView::NoEditTriggers); //Rende non modificabili le proprietà dei giocatori

    List_Widget -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch); //Adatta la tabella alla dimensione del widget in cui è contenuta

    List_Widget -> horizontalHeader() -> setDefaultAlignment(Qt::AlignCenter); //Allinea l'eader delle colonne centralmente

    List_Widget -> verticalHeader() -> setDefaultSectionSize(50); //Setta la dimensione verticale di default delle celle a 50 px

    List_Widget -> setIconSize(QSize(50, 50)); //Setta la dimensione delle icone a 50 x 50

    if(PLATFORM != "Android"){
        for(int i = 1; i <= gamers_counter; i++)
        {
            Gamers_List.push_back(new Gamer);

            Gamers_List [i - 1] -> Avatar = QIcon(":/avatars/multimedia/avatars/Yellow_Duck.png");

            Gamers_List [i - 1] -> Name = QString("Player ") += QString::number(i);

            List_Widget -> setItem(i - 1, 0, new QTableWidgetItem(Gamers_List [i - 1] -> Avatar, Gamers_List [i - 1] -> Name)); //Aggiunge il nome del giocatore e l'avatar alla lista di visualizzazione
        }
    }

    else{
        for(int i = 1; i <= gamers_counter; i++)
        {
            Gamers_List.push_back(new Gamer);

            if (i == 1) {Gamers_List [0] -> Avatar = QIcon(":/avatars/multimedia/avatars/Yellow_Duck.png");}
            else if (i == 2) {Gamers_List [1] -> Avatar = QIcon(":/avatars/multimedia/avatars/Green_Duck.png");}
            else if (i == 3) {Gamers_List [2] -> Avatar = QIcon(":/avatars/multimedia/avatars/Blue_Duck.png");}
            else if (i == 4) {Gamers_List [3] -> Avatar = QIcon(":/avatars/multimedia/avatars/Red_Duck.png");}

            Gamers_List [i - 1] -> Name = QString("Giocatore ") += QString::number(i);

            List_Widget -> setItem(i - 1, 0, new QTableWidgetItem(Gamers_List [i - 1] -> Avatar, Gamers_List [i - 1] -> Name)); //Aggiunge il nome del giocatore e l'avatar alla lista di visualizzazione
        }
    }
}


void Init_Form::Gamers_Editor()
{

    HLayout -> addWidget(List_Widget, 1); //Aggiunge la lista dei giocatori sulla sinistra della finestra

    HLayout -> setSpacing(5); //Setta uno spazio non estendibile pari a 5 px

    HLayout -> addWidget(Gamer_Prop, 3); //Aggiunge il widget che fa da editor per i giocatori --________---__--__--___--__--__

    VLayout -> addLayout(HLayout); //Aggiunge il layout orizzontale a quello verticale

    VLayout -> addWidget(Finish, Qt::AlignRight); //Aggiunge il pulsante Finish nella parte bassa della finestra

    connect(Finish, &QPushButton::clicked, this, &Init_Form::Init_Call); //Connette il pulsante Finish con lo slot Init_Call. Serve a generare un nuovo campo

    connect(List_Widget, &QTableWidget::itemClicked, Gamer_Prop, [this] {Gamer_Prop -> Edit_Gamer(List_Widget, &Gamers_List);}); //Connette il segnale che avvisa
                                                                                            //che il riferimento ad un oggetto della lista è stato cambiato
    this -> show(); //Mostra la finestra

}


Init_Form::~Init_Form()
{
}


void Init_Form::Init_Call()
{

    Info *Info_Widget = new Info (Game_Window, List_Widget);

    Game_Window -> addWidget(Info_Widget);

    Game_Window -> setStretchFactor(0, 3);

    Game_Window -> setStretchFactor(1, 2);

    Game_Engine *Start = new Game_Engine (Game_Window, Campo, Gamers_List, Info_Widget, this);

}



//Inizio Gamer Properties--------------------------------------

Gamer_Properties::Gamer_Properties(QWidget *parent, Init_Form *Tmp_Form) : QWidget(parent)
{
    this -> setAttribute(Qt::WA_DeleteOnClose);

    Init = Tmp_Form;

    Form_Layout -> addRow("Name: ", Name_Editor); //Aggiunge l'editor del nome al layout

    Form_Layout -> setSpacing(150);

    if(PLATFORM != "Android")
        Form_Layout -> addRow("Avatar: ", Avatar_Chooser); //Aggiunge l'avater chooser al layout

    this -> setLayout(Form_Layout); //Setta il layout per l'oggetto corrente
}


void Gamer_Properties::Edit_Gamer(QTableWidget *List_Widget, QVector <Gamer*> *Gamers_List)
{

    Name_Editor -> setText(List_Widget -> currentItem() -> text()); //Setta il testo visibile del Name_Editor scrivendo la stringa
                                                             //contenuta nell'oggetto selezionato nella List_Widget

    connect(Name_Editor, &QLineEdit::textEdited, [this, List_Widget, Gamers_List] //Se il testo nel Name_Editor appare modificato scrive i cambiamenti nella
                                                               //List_Widget_Widget, anche all'esterno(cattura l'oggetto corrente e la List_Widget
    {
        List_Widget -> currentItem() -> setText(Name_Editor -> text()); //Setta il testo dell'oggetto corrente nella List_Widget scrivendo il testo in Name_Editor

        Gamers_List -> at(List_Widget -> currentRow()) -> Name = Name_Editor -> text();
    });

    if(PLATFORM != "Android"){
        File_Connection = connect(Avatar_Chooser, &QPushButton::clicked, [this, List_Widget, Gamers_List]
        {
            List_Widget -> currentItem() -> setIcon(QIcon(QFileDialog::getOpenFileName(this, "Pick Avatar", "../multimedia/avatars/", "Images (*.png *jpg)")));

            Gamers_List -> at(List_Widget -> currentRow()) -> Avatar = List_Widget -> currentItem() -> icon();

            disconnect(File_Connection);
        });
    }
}
