#ifndef MEVNI3WET2_IMAGE_H
#define MEVNI3WET2_IMAGE_H

#include "Union-Find.h"
#include "Labels.h"
#include "AVLtree.h"
#include "MaxHeap.h"
#include "library.h"

struct Labels {
    MaxHeap<LabelByScore> labelsByScore;
    AVL<LabelBylabel,int> labelsBylabel;
};
class Image{
    int imageId;
    UnionFind pixels;
    Labels* labels;
public:
    Image(int imageId,int pixels):imageId(imageId),pixels(pixels){
        labels = new Labels[pixels];
    };
    ~Image();
    StatusType setLabelScore(int pixel,int label,int score);
    StatusType resetLabelScore(int pixel,int label);
    StatusType highestScoredLabel(int pixel, int *label);
    StatusType mergeSuperPixels(int pixel1, int pixel2);

};


#endif //MEVNI3WET2_IMAGE_H
