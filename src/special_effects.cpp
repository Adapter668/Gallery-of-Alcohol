#include <thread>
#include "special_effects.h"

Special_effects::Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder) {
    this->sceneBuilder = sceneBuilder;
    this->camera_ptr = camera_ptr;
} ;

void wait(int seconds) {
    clock_t end_of_waiting = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < end_of_waiting) {}
}

void Special_effects::bottleDetected(int bottle_number) {
    // TODO chosen bottle disappears
    // TODO flash light effect
    bottle* chosen_bottle;
    chosen_bottle = &SceneBuilder::all_bottles_coordinates[bottle_number];
    switch (chosen_bottle->type) {
        case CURACAO_BOTTLE:
            colorChange();
            break;
        case  WHISKY_BOTTLE:
            changePerspective();
            break;
        case  WINE_BOTTLE2:
            upsideDown();
            break;
        case  WINE_BOTTLE3:
            closePerspective();
            break;
    }
}


void Special_effects::swaying(short type) {
    vector<float> outVert, outNorm, outUV;
    double my_time = 0;
    sceneBuilder->getObjectsOuts(type, outVert, outNorm, outUV);
    for (int i = 0; i < outVert.size() / 3; i++) {
        // CUBE MOVEMENT
        outVert[i * 3] += sin(my_time + outVert[i * 3 + 1]) / 50;
        my_time += 0.1;
        // TEXTURE MOVEMENT
        outUV[i * 2] += sin(my_time + outVert[i * 2 + 1]) / 100;
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