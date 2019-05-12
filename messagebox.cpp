#include "messagebox.h"

messagebox::messagebox()
{

}

int messagebox :: show(QString question)
{
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBox.setText(question);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    int ret=msgBox.exec();

switch (ret)
    {
case QMessageBox::Save:
    msgBox.close();
    return 0;
    break;
case QMessageBox::Discard:
    msgBox.close();
    return 1;
    break;
case QMessageBox::Cancel:
    msgBox.close();
    return 2;
    break;
default:
    // should never be reached
    break;

    }
}

int messagebox :: show_delete( )
{

    QString question= "Do you want to delete selected item(s)?" ;
    QMessageBox msgBox;
    msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBox.setText(question);
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);

    int ret=msgBox.exec();

    switch (ret)
    {
    case QMessageBox::Yes:
        msgBox.close();
        return 0;
        break;

    case QMessageBox::Cancel:
        msgBox.close();
        return 1;
        break;
    default:
        // should never be reached
        break;

    }

}
