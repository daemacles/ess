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

                    btVector3 vec = btVector3(
                            p.worldTransform.getOrigin().x() - 0.01,
                            p.worldTransform.getOrigin().y() - 0.01,
                            p.worldTransform.getOrigin().z());
                    p.worldTransform.setOrigin(vec);

                }
                return false;
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}
