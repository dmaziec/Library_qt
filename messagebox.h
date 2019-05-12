#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QObject>
#include <QMessageBox>
#include <QAbstractButton>

class messagebox : public QObject
{

    Q_OBJECT

public:
messagebox();
int show(QString question);
int show_delete();

};

#endif // MESSAGEBOX_H
