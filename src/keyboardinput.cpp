#include "keyboardinput.h"

#include "rocketcontrol.h"
#include "rocket.h"

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
#define FORCE 0.1
            case Qt::Key_Up:
                {
                    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
                    RocketControl control = {FORCE, FORCE, FORCE, FORCE, 0, 0, 0, 0};
                    rocket->applyControl(control);
                    return false;
                }
            case Qt::Key_Right:
                {
                    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
                    RocketControl control = {FORCE, 0, FORCE, 0, 0, 0, 0, 0};
                    rocket->applyControl(control);
                    return false;
                }
            case Qt::Key_Left:
                {
                    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
                    RocketControl control = {0, FORCE, 0, FORCE, 0, 0, 0, 0};
                    rocket->applyControl(control);
                    return false;
                }
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}
