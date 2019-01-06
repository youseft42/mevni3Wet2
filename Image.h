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
    AVL<LabelBylabel,LabelBylabel> labelsBylabel;
};
class Image{
    int imageId;
    UnionFind pixels;
    Labels* labels;
public:
    Image(int imageId,int pixels):imageId(imageId),pixels(pixels){
        labels = new Labels[pixels];
    };
    ~Image(){
        delete[] labels;
    }
    StatusTypeT setLabelScore(int pixel,int label,int score)
    {
        LabelBylabel labelBylabel(label,score);
        if(labels[pixels.find(pixel)].labelsBylabel.contains(labelBylabel)){
            labels[pixels.find(pixel)].labelsBylabel.Get(labelBylabel).updateScore(score);
            return SUCCESS;
        }
        LabelByScore labelByScore(label,score);
        int indexInHeap=-1;
        indexInHeap=labels[pixels.find(pixel)].labelsByScore.Insert(labelByScore);
        labelBylabel.updateIndexInHeap(indexInHeap);
        labels[pixels.find(pixel)].labelsBylabel.Insert(labelBylabel,labelBylabel);
        return SUCCESS;
    }
    StatusTypeT resetLabelScore(int pixel,int label)
    {
        LabelBylabel labelBylabel(label,0);
        int index = labels[pixels.find(pixel)].labelsBylabel.Get(labelBylabel).getIndex();
        int maxScore = labels[pixels.find(pixel)].labelsByScore.FindMax().getScore();
        LabelByScore labelByScore(label,maxScore+1);
        labels[pixels.find(pixel)].labelsByScore.IncreaseKey(labelByScore,index);
        labels[pixels.find(pixel)].labelsByScore.DelMax();
        labels[pixels.find(pixel)].labelsBylabel.remove(labelBylabel);
        return SUCCESS;
    }
};


#endif //MEVNI3WET2_IMAGE_H
