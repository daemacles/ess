#include "entity.h"

void Entity::update (void) {
    if (physObject) {
        printf("I got updated!");
    }
}
