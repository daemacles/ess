#include "qtessclient.h"
#include "ui_qtessclient.h"

QtESSClient::QtESSClient(bool *_ctr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtESSClient),
    clientThreadRunning(_ctr)
{
    ui->setupUi(this);
}

QtESSClient::~QtESSClient()
{
    delete ui;
}
