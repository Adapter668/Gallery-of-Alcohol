#ifndef GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
#define GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H

#include "camera.h"

class Special_effects {
private:
    Camera* camera_ptr;

public:
    Special_effects() {} ;
    ~Special_effects() {} ;
    void* array_of_effects;

    void setCameraPointer(Camera* camera);
    void swaying();
};


#endif //GALLERY_OF_ALCOHOL_SPECIAL_EFFECTS_H
