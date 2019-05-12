#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagebox.h"

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

add_dialog=new adddialog;
connect (add_dialog, SIGNAL( send_data(QString,QString,QString)), this, SLOT(receive_data(QString, QString , QString )) );

edititem = new edit_dialog;
connect (edititem, SIGNAL( send_data(QString,QString,QString)), this, SLOT(receive_dataedit(QString, QString , QString )) );

ui->editButton->setEnabled(false);
ui->filterButton->setEnabled(false);
ui->clearButton->setEnabled(false);

table.setColumnCount(3);
table.setHeaderData(0,Qt::Horizontal, ("Author"),Qt::DisplayRole);
table.setHeaderData(1,Qt::Horizontal, ("Title"),Qt::DisplayRole);
table.setHeaderData(2,Qt::Horizontal, ("Year"),Qt::DisplayRole);

proxy_a.setSourceModel(&table);
proxy_a.setFilterCaseSensitivity(Qt::CaseInsensitive);
proxy_a.setFilterKeyColumn(0);

proxy_t.setSourceModel(&proxy_a);
proxy_t.setFilterCaseSensitivity(Qt::CaseInsensitive);
proxy_t.setFilterKeyColumn(1);

proxy_y.setSourceModel(&proxy_t);
proxy_y.setFilterCaseSensitivity(Qt::CaseInsensitive);
proxy_y.setFilterKeyColumn(2);

ui->yearCombo->addItem("");
for (int i = 2019; i >=1900; i--) ui->yearCombo->insertItem(1900,QString::number(i));

ui->tableView->setModel(&proxy_y);

connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
    ui->editButton->setEnabled(ui->tableView->selectionModel()->selectedRows().size() == 1);
});


ui->deleteButton->setEnabled(false);
connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
ui->deleteButton->setEnabled(ui->tableView->selectionModel()->selectedRows().size() >=1);
});

ui->yearCombo->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
ui->yearCombo->setMinimumHeight(50);
openFile();

connect(ui->editTitle, SIGNAL(textChanged(const QString)),this, SLOT(set_filter(const QString)) ) ;
connect(ui->editAuthor, SIGNAL(textChanged(const QString)),this, SLOT(set_filter(const QString)) ) ;
connect(ui->yearCombo, SIGNAL(currentIndexChanged(const QString)),this, SLOT(set_filter(const QString)) ) ;}

MainWindow::~MainWindow()
{
delete ui;
delete add_dialog;
delete edititem;
}

void MainWindow :: openFile()
{
    QFile file("Workbook11.csv");
    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "error opening file: " << QDir::current();
        return;
    }

    QTextStream instream(&file);

    QStringList elems;
    while(instream.atEnd()!=true)
    {
        QString line= instream.readLine();
        elems=line.split(";");
       addElement(elems.at(0), elems.at(1), elems.at(2));
    }

    file.close();
}

void MainWindow :: addElement(QString author, QString title, QString year)
{

   int row=table.rowCount(QModelIndex());
   table.insertRow(row,QModelIndex());
    QModelIndex index=table.index(row,0);
    table.setData(index,author);
    index=table.index(row,1);
    table.setData(index,title);
    index=table.index(row,2);
    table.setData(index,year);

}


void MainWindow::on_AddnewButton_clicked()
{

    add_dialog->open_dialog();

}

void MainWindow :: receive_data(QString author, QString title, QString year)
{

    addElement(author, title, year);
    saveFile();

}

void MainWindow :: saveFile()
{

    int nb= table.rowCount(QModelIndex());

    QDir().mkdir("MyFolder.csv");
    QFile file("Workbook11.csv");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "error opening file: " << QDir::current();
        return ;
    }
    QTextStream outstream(&file);
    int i=0;
    QModelIndex index0;
    QModelIndex index1;
    QModelIndex index2;
    while(i!=nb )
        {

            index0=table.index(i,0);
            index1=table.index(i,1);
            index2=table.index(i,2);

            outstream<<table.data(index0).toString()+";"+table.data(index1).toString()+";"+table.data(index2).toString()+"\n";
            i++;
        }

        file.flush();
        file.close();

}

void MainWindow::on_clearButton_clicked()
{

    ui->clearButton->setEnabled(false);
     proxy_y.setFilterFixedString({});
     proxy_a.setFilterFixedString({});
     proxy_t.setFilterFixedString({});

     ui->editAuthor->setText({});
     ui->editTitle->setText({});
     ui->yearCombo->setCurrentText("");

}

void MainWindow::on_filterButton_clicked()
{

     ui->clearButton->setEnabled(true);
     ui->filterButton->setEnabled(false);
    QString author=ui->editAuthor->text();
    QString title=ui->editTitle->text();
    QString year=ui->yearCombo->currentText();

    qDebug()<<year;

    if(!author.isEmpty())
    {
        proxy_a.setFilterRegExp(QRegExp(author));}

    if(!title.isEmpty())
    {
        proxy_t.setFilterRegExp(QRegExp(title)); }


    if( !year.isEmpty())
    {    proxy_y.setFilterRegExp(QRegExp(year)); }



}

void MainWindow::on_deleteButton_clicked()
{

    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    messagebox box;

    int z= box.show_delete();

    if(z==0){
    while(!selectedIndexes.empty())
    {
        ui->tableView->model()->removeRow(selectedIndexes.at(0).row());
        selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    }
    }
}

void MainWindow::on_editButton_clicked()

{

    QModelIndexList rows = ui->tableView->selectionModel()->selectedIndexes();

    QModelIndex row=rows.at(0);

    QModelIndex row_t=proxy_y.mapToSource(row);
    QModelIndex row_a=proxy_t.mapToSource(row_t);
    QModelIndex row_table= proxy_a.mapToSource(row_a);

    int nb_row= row_table.row();
    row_edit=nb_row;


    QModelIndex index0=table.index(nb_row,0);
    QString author= table.data(index0).toString();

    QModelIndex index1=table.index(nb_row,1);
    QString title= table.data(index1).toString();

    QModelIndex  index2=table.index(nb_row,2);
    QString year1= table.data(index2).toString();

   int year= year1.toInt();


    edititem ->open_dialog(author,title,year);

}

void MainWindow :: receive_dataedit(QString author, QString title, QString year)
{
     QModelIndex index0=table.index(row_edit,0);
     table.setData(index0,author);

    QModelIndex index1=table.index(row_edit,1);
    table.setData(index1,title);

    QModelIndex  index2=table.index(row_edit,2);
    table.setData(index2,year);

    saveFile();
}


void MainWindow:: closeEvent(QCloseEvent *event)
{
    proxy_y.setFilterFixedString({});
    proxy_a.setFilterFixedString({});
    proxy_t.setFilterFixedString({});

    saveFile();

    ui->editAuthor->setText({});
    ui->editTitle->setText({});
    ui->yearCombo->setCurrentText("");
    saveFile();
}

void MainWindow ::set_filter(const QString z)
{
    if(ui->editAuthor->text().isEmpty()!=true || ui->editTitle->text().isEmpty()!=true || ui->yearCombo->currentText().isEmpty()!=true ) ui->filterButton->setEnabled(true);
    else ui->filterButton->setEnabled(false);
}

