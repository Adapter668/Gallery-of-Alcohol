#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include "camera.h"
#include "SceneBuilder.h"

class Special_effects {
private:
    Camera* camera_ptr;
    SceneBuilder* sceneBuilder;

public:
    Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder);
    ~Special_effects() {} ;

    void swaying(short type);
    void penetrability();
    void changePerspective();
};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
