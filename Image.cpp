#include "Image.h"


StatusType Image::setLabelScore(int pixel,int label,int score)
{
    int superPixel = pixels->find(pixel);
    LabelBylabel labelBylabel(label,score);
    LabelByScore labelByScore(label,score);
    if(labels[superPixel].labelsBylabel->contains(label)){
        labels[superPixel].labelsBylabel->Get(label).updateScore(score);
        labels[superPixel].labelsByScore->remove(labelByScore);
        labels[superPixel].labelsByScore->Insert(labelByScore, labelByScore);
        labels[superPixel].highestScoredLabel = labels[superPixel].labelsByScore->getMaxKey().getLabel();
        return SUCCESS;
    }
    labels[superPixel].labelsBylabel->Insert(labelBylabel,label);
    labels[superPixel].labelsByScore->Insert(labelByScore, labelByScore);
    labels[superPixel].highestScoredLabel = labels[superPixel].labelsByScore->getMaxKey().getLabel();
    return SUCCESS;
}

StatusType Image::resetLabelScore(int pixel,int label)
{   int superPixel =pixels->find(pixel);
    if(!(labels[superPixel].labelsBylabel->contains(label)))
        return FAILURE;
    LabelByScore labelByScore(label, 0);
    labels[superPixel].labelsBylabel->remove(label);
    labels[superPixel].labelsByScore->remove(labelByScore);
    labels[superPixel].highestScoredLabel = labels[superPixel].labelsByScore->getMaxKey().getLabel();
    return SUCCESS;
}
StatusType Image::highestScoredLabel(int pixel, int *label){
    int superPixel =pixels->find(pixel);
    if(!labels[superPixel].labelsByScore->GetSize())
        return FAILURE;
    *label = labels[superPixel].highestScoredLabel;
    return SUCCESS;
}
class LabelFunction{
public:
    int operator()(LabelBylabel& labelBylabel){
        return labelBylabel.getLabel();
    }
};
class ScoreFunction{
public:
    LabelByScore& operator()(LabelByScore& labelByScore){
        return labelByScore;
    }
};
StatusType Image::mergeSuperPixels(int pixel1, int pixel2){
        int superPixel1=pixels->find(pixel1);
        int superPixel2=pixels->find(pixel2);
        if(superPixel1==superPixel2) return FAILURE;
        pixels->merge(pixel1,pixel2);
        int newSuperPixel = pixels->find(pixel1);
        LabelFunction labelFunction;
        ScoreFunction scoreFunction;
        labels[newSuperPixel].labelsBylabel->
                uniteTrees(labels[superPixel1].labelsBylabel,
                           labels[superPixel2].labelsBylabel,labelFunction);
        labels[newSuperPixel].labelsByScore->
                uniteTrees(labels[superPixel1].labelsByScore,
                           labels[superPixel2].labelsByScore,scoreFunction);
        return  SUCCESS;
}
