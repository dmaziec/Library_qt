#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QAbstractTableModel>
#include <QString>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QChar>
#include <QObject>
#include <QDir>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>
#include "adddialog.h"
#include "edit_dialog.h"
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = nullptr);
~MainWindow();
void addElement(QString author, QString title, QString year);
//void openFile();

private slots:
    void on_AddnewButton_clicked();

    void receive_data(QString author, QString title, QString year);

    void receive_dataedit(QString author, QString title, QString year);

    void on_clearButton_clicked();

    void on_filterButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void set_filter(const QString z);

   // void set_clear();

  //  void on_tableView_clicked(const QModelIndex &index);

    //void on_tableView_activated(const QModelIndex &index);

private:

Ui::MainWindow *ui;
QStandardItemModel table;
QSortFilterProxyModel proxy_a;
QSortFilterProxyModel proxy_t;
QSortFilterProxyModel proxy_y;
adddialog *add_dialog;
edit_dialog *edititem;
void openFile();
void saveFile();
int row_edit;
QVariant headerData(int section, Qt::Orientation orientation, int role) const;
void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
