#include <thread>
#include "special_effects.h"

Special_effects::Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder) {
    this->sceneBuilder = sceneBuilder;
    this->camera_ptr = camera_ptr;
} ;

void wait(int seconds) {
    clock_t end_of_waiting = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < end_of_waiting) {}
    //terminate();
}

void Special_effects::bottleDetected(int bottle_number) {
    // TODO chosen bottle disappears
    // TODO flash light effect
    bottle* chosen_bottle;
    chosen_bottle = &SceneBuilder::all_bottles_coordinates[bottle_number];
    switch (chosen_bottle->type) {
        case CURACAO_BOTTLE:
            if(bottle_number < 10) {
                colorChange();
            }
            else{
                penetrability();
            }
            break;
        case  WHISKY_BOTTLE:
            changePerspective();
            break;
        case  WINE_BOTTLE2:
            if(bottle_number < 95){
                upsideDown();
            }
            else{
                changePerspective();
            }
            break;
        case  WINE_BOTTLE3:
            if(bottle_number < 150) {
                closePerspective();
            }
            else{
                swaying();
            }
            break;
    }
}

void Special_effects::swaying() {
    sceneBuilder->swaying = !sceneBuilder->swaying;
    if(sceneBuilder->swaying){
        cout << "Swaying on\n";
    }
    else{
        cout << "Swaying off\n";
    }
}

void Special_effects::penetrability() {
    if (camera_ptr->collision_on) {
        camera_ptr->collision_on = false;
        cout << "Penetrability on\n";
    }
    else {
        camera_ptr->collision_on = true;
        cout << "Penetrability off\n";
    }
}

void Special_effects::changePerspective(float aspect) {
    camera_ptr->different_perspective(aspect);
}

void Special_effects::upsideDown() {
    camera_ptr->upsideDown();
}

void Special_effects::closePerspective(float angle) {
    camera_ptr->closePerspective(angle);
}

void Special_effects::colorChange() {
    if (glIsEnabled(GL_LIGHT1)) {
        glDisable(GL_LIGHT1);
        cout << "Color change off\n";
    }
    else {
        glEnable(GL_LIGHT1);
        cout << "Color change on\n";
    }

}

void Special_effects::stopEffects() {
    if(sceneBuilder->swaying){
        sceneBuilder->swaying = false;
    }
    if(!camera_ptr->collision_on){
        camera_ptr->collision_on = true;
    }
    if (glIsEnabled(GL_LIGHT1)) {
        glDisable(GL_LIGHT1);
    }
    if(!camera_ptr->common_perspective){
        camera_ptr->different_perspective(5.0f);
    }
    if(camera_ptr->upside_down){
        camera_ptr->upsideDown();
    }
    if(camera_ptr->close){
        camera_ptr->closePerspective(15.0f);
    }

}