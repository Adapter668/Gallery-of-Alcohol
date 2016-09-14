#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include <time.h>
#include "camera.h"
#include "sceneBuilder.h"

using namespace std;

class Special_effects {
private:
    Camera* camera_ptr;
    SceneBuilder* sceneBuilder;
    int drunk_turning_counter = NO_BOTTLE_COLLISION;

    void swaying();
    void penetrability();
    void changePerspective(float aspect = 5.0f);
    void upsideDown();
    void closePerspective(float angle = 15.0f);
    void colorChange();



public:
    Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder);
    ~Special_effects() {} ;

    bool detection = false;
    vector<float> outVert[10];
    vector<float> outNorm[10];
    vector<float> outUV[10];
    bool proper_direction_to_go = true;

    void bottleDetected(int bottle_number);
    void stopEffects();
    void drunkTurning();
};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
