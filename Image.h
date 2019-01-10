#ifndef MEVNI3WET2_IMAGE_H
#define MEVNI3WET2_IMAGE_H

#include "Union-Find.h"
#include "Labels.h"
#include "AVLtree.h"
#include "library.h"

class Labels {
public:
    AVL<LabelBylabel,int>* labelsBylabel;
    Labels(){
        labelsBylabel = new AVL<LabelBylabel,int>;

    }
    ~Labels(){
        delete labelsBylabel;
    };
};
class Image{
    int imageId;
    UnionFind* pixels;
    Labels* labels;
public:
    Image() : imageId(0), pixels(0), labels(NULL){};
    Image(int imageId,int pixel) : imageId(imageId){
        pixels =new UnionFind(pixel);
        labels = new Labels[pixel];
    };
    ~Image()= default;
    void destroyImage(){
        delete pixels;
        delete[] labels;
    }
    StatusType setLabelScore(int pixel,int label,int score);
    StatusType resetLabelScore(int pixel,int label);
    StatusType highestScoredLabel(int pixel, int *label);
    StatusType mergeSuperPixels(int pixel1, int pixel2);

};


#endif //MEVNI3WET2_IMAGE_H
