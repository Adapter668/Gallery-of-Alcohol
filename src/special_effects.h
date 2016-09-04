#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include <time.h>
#include <functional>
#include "camera.h"
#include "sceneBuilder.h"

class Special_effects {
private:
    Camera* camera_ptr;
    SceneBuilder* sceneBuilder;


    void swaying(short type);
    void penetrability();
    void changePerspective(float aspect = 5.0f);
    void upsideDown();
    void closePerspective(float angle = 15.0f);
    void colorChange();

public:
    Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder);
    ~Special_effects() {} ;

    void bottleDetected(int bottle_number);

};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
