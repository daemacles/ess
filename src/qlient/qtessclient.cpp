#include "qtessclient.h"
#include "ui_qtessclient.h"

QtESSClient::QtESSClient(bool *_ctr,
                         RocketControl *rc,
                         QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtESSClient),
    clientThreadRunning(_ctr),
    rocketControl(rc)
{
    ui->setupUi(this);
}

QtESSClient::~QtESSClient()
{
    delete ui;
}

void QtESSClient::keyPressEvent (QKeyEvent *event) {
    rocketControl->name.main1 = 0;
    rocketControl->name.main2 = 0;
    rocketControl->name.main3 = 0;
    rocketControl->name.main4 = 0;
    rocketControl->name.rot1 = 0;
    rocketControl->name.rot2 = 0;
    rocketControl->name.rot3 = 0;
    rocketControl->name.rot4 = 0;
    char key = event->text().data()[0].toAscii();
    switch(key) {
    case 'w':
        rocketControl->name.main3 = 1;
        rocketControl->name.main4 = 1;
        break;
    case 'a':
        rocketControl->name.main3 = 0;
        rocketControl->name.main4 = 1;
        break;

    case 'd':
        rocketControl->name.main3 = 1;
        rocketControl->name.main4 = 0;
        break;

    default:
        rocketControl->name.main3 = 0;
        rocketControl->name.main4 = 0;
        break;
    }
}

void QtESSClient::keyReleaseEvent( QKeyEvent *event) {
    rocketControl->name.main1 = 0;
    rocketControl->name.main2 = 0;
    rocketControl->name.main3 = 0;
    rocketControl->name.main4 = 0;
    rocketControl->name.rot1 = 0;
    rocketControl->name.rot2 = 0;
    rocketControl->name.rot3 = 0;
    rocketControl->name.rot4 = 0;
}
