#ifndef QTESSCLIENT_H
#define QTESSCLIENT_H

#include <QWidget>

namespace Ui {
class QtESSClient;
}

class QtESSClient : public QWidget
{
    Q_OBJECT
    
public:
    explicit QtESSClient(bool *_ctr, QWidget *parent = 0);
    ~QtESSClient();
    
private:
    Ui::QtESSClient *ui;
    bool *clientThreadRunning;
};

#endif // QTESSCLIENT_H
