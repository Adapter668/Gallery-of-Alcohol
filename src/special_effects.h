#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include <time.h>
#include <functional>

#include "camera.h"
#include "sceneBuilder.h"

#define EFFECTS_AMOUNT      10;

class Special_effects {
private:
    Camera* camera_ptr;
    SceneBuilder* sceneBuilder;

    void swaying(short type);                                                 // 0
    void penetrability();                                                           // 1
    void changePerspective(float aspect = 5.0f);              //2
    void upsideDown();                                                              // 3
    void closePerspective(float angle = 15.0f);                 //4
    void colorChange();                                                             //5

public:
    Special_effects(Camera* camera_ptr, SceneBuilder* sceneBuilder);
    ~Special_effects() {} ;

    void bottleDetected(int bottle_number);
    void checkTime();

};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
