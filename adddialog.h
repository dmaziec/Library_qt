#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QObject>
#include "messagebox.h"
#include <QPushButton>

class adddialog : public QObject
{
    Q_OBJECT
public:
    adddialog(QObject *parent = 0);
    QDialogButtonBox *buttons; //= new QDialogButtonBox;

 /*   QString add_author();
    QString add_title();
    QString add_year(); */
    void open_dialog();
private:
    QLineEdit *m_title;//=new QLineEdit;
    QLineEdit *m_author;// = new QLineEdit;
    QSpinBox *m_year;//= new QSpinBox;
    QFormLayout *fl;//= new QFormLayout (this);
    QDialog *window;//=new QWidget;
    QPushButton *but;
public slots:
    void accept();
    void close_window();
    void displaymessage();
    void enableSlot(const QString &);

signals:
    void send_data(QString author, QString title, QString year);
};
#endif // ADDDIALOG_H
