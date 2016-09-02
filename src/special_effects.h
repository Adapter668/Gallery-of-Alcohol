#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include "camera.h"
#include "sceneBuilder.h"

class Special_effects {
private:
    Camera* camera_ptr;
    sceneBuilder* sceneBuilder;

public:
    Special_effects(Camera* camera_ptr, sceneBuilder* sceneBuilder);
    ~Special_effects() {} ;

    void swaying(short type);
    void penetrability();
    void changePerspective(float aspect = 5.0f);
    void upsideDown();
    void closePerspective(float angle = 15.0f);
    void colorChange();
};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
