#include <Qt>

#include "entityhandler.h"

class KeyboardInput:public QObject {
    private:
        EntityHandler* entityHandler;

    public:
        KeyboardInput(EntityHandler* entityHandler);
        bool eventFilter(QObject *obj, QEvent *event);
};
