#include "Image.h"


StatusType Image::setLabelScore(int pixel,int label,int score)
{
    int superPixel = pixels->find(pixel);
    LabelBylabel labelBylabel(label,score);
    if(labels[superPixel].labelsBylabel->contains(label)){
        labels[superPixel].labelsBylabel->remove(label);
        labels[superPixel].labelsBylabel->Insert(labelBylabel,label);
        return SUCCESS;
    }
    labels[superPixel].labelsBylabel->Insert(labelBylabel,label);
    return SUCCESS;
}

StatusType Image::resetLabelScore(int pixel,int label)
{
    int superPixel =pixels->find(pixel);
    if(!(labels[superPixel].labelsBylabel->contains(label)))
        return FAILURE;
    labels[superPixel].labelsBylabel->remove(label);
    return SUCCESS;
}
StatusType Image::highestScoredLabel(int pixel, int *label){
    int superPixel = pixels->find(pixel);
    if(labels[superPixel].labelsBylabel->GetSize() == 0)
        return FAILURE;
    *label = labels[superPixel].labelsBylabel->GetHeadMax().getLabel();
    return SUCCESS;
}
class LabelFunction{
public:
    int operator()(LabelBylabel& labelBylabel){
        return labelBylabel.getLabel();
    }
};
class Compare{
public:
    int operator()(LabelBylabel& labelBylabel1,LabelBylabel& labelBylabel2){
        if(labelBylabel1.getLabel() < labelBylabel2.getLabel()) return -1;
        if(labelBylabel1.getLabel() > labelBylabel2.getLabel()) return 1;
        return 0;
    }
};
StatusType Image::mergeSuperPixels(int pixel1, int pixel2){
        int superPixel1=pixels->find(pixel1);
        int superPixel2=pixels->find(pixel2);
        if(superPixel1==superPixel2) return FAILURE;
        pixels->merge(pixel1,pixel2);
        int newSuperPixel = pixels->find(pixel1);
        AVL<LabelBylabel,int>* tree1 = labels[superPixel1].labelsBylabel;
        AVL<LabelBylabel,int>* tree2 = labels[superPixel2].labelsBylabel;
        AVL<LabelBylabel,int>* unitedTree = new AVL<LabelBylabel,int>;
        LabelFunction labelFunction;
        Compare compare;
        unitedTree->uniteTrees(tree1, tree2, labelFunction,compare);
        delete labels[newSuperPixel].labelsBylabel;
        labels[newSuperPixel].labelsBylabel = unitedTree;
        labels[newSuperPixel].labelsBylabel->FixTreeMax();
        return  SUCCESS;
}
