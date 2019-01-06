#include "Image.h"

Image::~Image(){
    delete[] labels;
}

StatusType Image::setLabelScore(int pixel,int label,int score)
{
    LabelBylabel labelBylabel(label,score);
    if(labels[pixels.find(pixel)].labelsBylabel.contains(label)){
        labels[pixels.find(pixel)].labelsBylabel.Get(label).updateScore(score);
        return SUCCESS;
    }
    LabelByScore labelByScore(label,score);
    int indexInHeap=-1;
    indexInHeap = labels[pixels.find(pixel)].labelsByScore.Insert(labelByScore);
    labelBylabel.updateIndexInHeap(indexInHeap);
    labels[pixels.find(pixel)].labelsBylabel.Insert(labelBylabel,label);
    return SUCCESS;
}

StatusType Image::resetLabelScore(int pixel,int label)
{
    int index = labels[pixels.find(pixel)].labelsBylabel.Get(label).getIndex();
    int maxScore = labels[pixels.find(pixel)].labelsByScore.FindMax().getScore();
    LabelByScore labelByScore(label,maxScore+1);
    labels[pixels.find(pixel)].labelsByScore.IncreaseKey(labelByScore,index);
    labels[pixels.find(pixel)].labelsByScore.DelMax();
    labels[pixels.find(pixel)].labelsBylabel.remove(label);
    return SUCCESS;
}