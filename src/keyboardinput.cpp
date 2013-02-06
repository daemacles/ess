#include "keyboardinput.h"

KeyboardInput::KeyboardInput(EntityHandler* entityHandler) {
    this->entityHandler = entityHandler;
}

bool KeyboardInput::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *KeyEvent = (QKeyEvent*)event;

        switch(KeyEvent->key())
        {
            case Qt::Key_Up:
                for(auto o : this->entityHandler->dynamicEnts) {
                    Entity* e = o.second;
                    Pose& p = e->getPose();
                    p.linForce = btVector3(
                            100, 100, 100);

                    /*
                    p.worldTransform.setOrigin(
                            vec
                            );
                            */
                    printf("AAAAAAA\n");
                }
                return false;
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}
