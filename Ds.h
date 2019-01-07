#ifndef MEVNI3WET2_DS_H
#define MEVNI3WET2_DS_H

#include "Image.h"
#include "ChainHashing.h"

class Ds{
    int pixels;
    ChainHashing<Image, int> allImages;
public:
    Ds(int pixels);
    ~Ds(){
        class Distroy{
        public:
            void operator()(Image& image){
                image.destroyImage();
            }

        };
        Distroy distroy;
        allImages.DoSomething(distroy);
    };
    StatusType AddImage(int imageID);
    StatusType DeleteImage(int imageID);
    StatusType SetLabelScore(int imageID, int pixel, int label, int score);
    StatusType ResetLabelScore(int imageID, int pixel, int label);
    StatusType GetHighestScoredLabel(int imageID, int pixel, int *label);
    StatusType MergeSuperPixels(int imageID, int pixel1, int pixel2);
};


#endif //MEVNI3WET2_DS_H
