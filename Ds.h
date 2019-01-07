#ifndef MEVNI3WET2_DS_H
#define MEVNI3WET2_DS_H

#include "Image.h"
#include "ChainHashing.h"

class Ds{
    int pixels;
    ChainHashing allImages;
public:
    Ds(int pixels);
    ~Ds();
    StatusType AddImage(void *DS, int imageID);

};


#endif //MEVNI3WET2_DS_H
