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
            case Qt::Key_Up:
                {
                    Rocket* rocket = static_cast<Rocket*>(entityHandler->dynamicEnts["rocket"]);
                    RocketControl control = {0.205, 0.205, 0.205, 0.205, 0, 0, 0, 0};
                    rocket->applyControl(control);
                    return false;
                }
                    /*
                for(auto o : this->entityHandler->dynamicEnts) {

                    Entity* e = o.second;
                    Pose& p = e->getPose();

                    btVector3 vec = btVector3(
                            p.worldTransform.getOrigin().x() - 0.01,
                            p.worldTransform.getOrigin().y() - 0.01,
                            p.worldTransform.getOrigin().z());
                    p.worldTransform.setOrigin(vec);

                }
                    */
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}
