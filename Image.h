#ifndef MEVNI3WET2_IMAGE_H
#define MEVNI3WET2_IMAGE_H

#include "Union-Find.h"
#include "Labels.h"
#include "AVLtree.h"
#include "MaxHeap.h"
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusTypeT;

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
    StatusTypeT setLabelScore(int pixel,int label,int score);
    StatusTypeT resetLabelScore(int pixel,int label);
};


#endif //MEVNI3WET2_IMAGE_H
