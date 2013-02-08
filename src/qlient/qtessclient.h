#ifndef QTESSCLIENT_H
#define QTESSCLIENT_H

#include <QWidget>
#include <QKeyEvent>

#include "essclient.h"

namespace Ui {
class QtESSClient;
}

class QtESSClient : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtESSClient(bool *_ctr,
                         RocketControl *rc,
                         QWidget *parent = 0);
    ~QtESSClient();

    void keyPressEvent (QKeyEvent *event);
    void keyReleaseEvent (QKeyEvent *event);

private:
    Ui::QtESSClient *ui;
    bool *clientThreadRunning;
    RocketControl *rocketControl;
};

#endif // QTESSCLIENT_H
