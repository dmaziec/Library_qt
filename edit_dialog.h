#ifndef EDIT_DIALOG_H
#define EDIT_DIALOG_H
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QObject>
#include "messagebox.h"
#include <QPushButton>
using namespace std;
class edit_dialog :public QObject
{
    Q_OBJECT
public:
    edit_dialog(QObject *parent = 0);
    void open_dialog(QString author="", QString title="", int year= 1900);

QDialogButtonBox *buttons; //= new QDialogButtonBox;

private:
    QLineEdit *m_title;//=new QLineEdit;
    QLineEdit *m_author;// = new QLineEdit;
    QSpinBox *m_year;//= new QSpinBox;
    QFormLayout *fl;//= new QFormLayout (this);
    QDialog *window;//=new QWidget;
    QString author_edit;
    QString title_edit;
    int year_edit;
    QPushButton *but;
public slots:
    void accept();
    void close_window();
     void displaymessage();
     void enableSlot(const QString &);
signals:
    void send_data(QString author, QString title, QString year); };
#endif // EDIT_DIALOG_H
