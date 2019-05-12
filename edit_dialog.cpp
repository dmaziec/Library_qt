#include "edit_dialog.h"
#include <iostream>

edit_dialog::edit_dialog(QObject *parent )
{
}

void edit_dialog ::accept()
{

    emit send_data(m_author->text(), m_title->text(), m_year->text());
    window->close();
};


void edit_dialog :: close_window()
{
    window->close();

}

void edit_dialog :: open_dialog(QString author, QString title, int year)
{
    author_edit=author;
    title_edit=title;
    year_edit=year;
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

    m_author->setText(author);
    m_author->cursorBackward(true, author.length());
    m_title->setText(title);
    m_title->cursorBackward(true, title.length());
    m_year->setValue(year);
    window->setLayout(fl);
    window->setWindowTitle("Edit");
   but=buttons->button( QDialogButtonBox::Save );
    but->setEnabled(false);
    connect( m_title, SIGNAL(textChanged(const QString &)),this,  SLOT(enableSlot(const QString &)));
    connect( m_author, SIGNAL(textChanged(const QString &)),this,  SLOT(enableSlot(const QString &)));
    connect( m_year, SIGNAL(valueChanged(const QString &)),this,  SLOT(enableSlot(const QString &)));
    window->exec();
}

void edit_dialog :: displaymessage()
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


    delete box; }

    else close_window();

}

void edit_dialog :: enableSlot(const QString &)
{

    if((m_author->text()==author_edit  && m_title->text()==title_edit && m_year->value()==year_edit) ||  m_author->text().isEmpty()==true || m_title->text().isEmpty()==true) but->setEnabled(false);
    else but->setEnabled(true);
}


