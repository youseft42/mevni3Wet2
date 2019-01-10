#ifndef MEVNI3WET2_DS_H
#define MEVNI3WET2_DS_H

#include "Image.h"
#include "ChainHashing.h"
class Destroy{
public:
    void operator()(Image& image1){
        image1.destroyImage();
    }
};
class Ds{
    int pixels;
    ChainHashing<Image, int> allImages;
public:
    Ds(int pixels);
    ~Ds(){

        Destroy destroy;
        allImages.DoSomething(destroy);
    };
    StatusType AddImage(int imageID);
    StatusType DeleteImage(int imageID);
    StatusType SetLabelScore(int imageID, int pixel, int label, int score);
    StatusType ResetLabelScore(int imageID, int pixel, int label);
    StatusType GetHighestScoredLabel(int imageID, int pixel, int *label);
    StatusType MergeSuperPixels(int imageID, int pixel1, int pixel2);
};


#endif //MEVNI3WET2_DS_H
