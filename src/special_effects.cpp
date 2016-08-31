#include "special_effects.h"

Special_effects::Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder) {
    this->sceneBuilder = sceneBuilder;
    this->camera_ptr = camera_ptr;
} ;

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

void Special_effects::changePerspective() {
    if (camera_ptr->common_perspective) {
        camera_ptr->common_perspective = false;
        cout << "Different perspective\n";
    }
    else {
        camera_ptr->common_perspective = true;
        cout << "Normal perspective\n";
    }
}
