#include "adddialog.h"
using namespace std;
#include <iostream>


adddialog::adddialog(QObject *parent  )
{
}

void adddialog :: close_window()
{
    window->close();
}


void adddialog :: open_dialog()
{
    window= new QDialog;
    buttons = new QDialogButtonBox;
    m_title=new QLineEdit;
    m_author = new QLineEdit;
    m_year= new QSpinBox;
    fl= new QFormLayout ();
    window->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    buttons->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Save);

    connect(buttons, SIGNAL(rejected()), this, SLOT(displaymessage()));
    connect (buttons, SIGNAL(accepted()), this, SLOT(accept()));

    m_year->setMaximum(2019);
    m_year->setMinimum(1900);
    fl->addRow("Author: ", m_author);
    fl->addRow("Title: ", m_title);
    fl->addRow("Year: ", m_year);
    fl->addWidget(buttons);
    window->move(500,275);

    window->setLayout(fl);
    window->setWindowTitle("Add new");

    but=buttons->button( QDialogButtonBox::Save );
    but->setEnabled(false);

   connect( m_title, SIGNAL(textChanged(const QString &)),this,  SLOT(enableSlot(const QString &)));
   connect( m_author, SIGNAL(textChanged(const QString &)),this,  SLOT(enableSlot(const QString &)));

    window->exec();
}

void adddialog ::accept()
{
    emit send_data(m_author->text(), m_title->text(), m_year->text());
    window->close();
};

void adddialog :: displaymessage()
{
    if(but->isEnabled()==true){
    messagebox *box=new messagebox;
    QString text= "Do you want to save your changes?";
    int z= box->show(text);

   if(z==0)
   {
       accept();
   }

   if(z==1)
   {
       close_window();
   }
   delete box;
    }
    else close_window();
}

void adddialog :: enableSlot(const QString &)
{

    if(m_title->text().isEmpty()==true || m_author->text().isEmpty()==true ) but->setEnabled(false);
    else but->setEnabled(true);
}

