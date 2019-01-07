#include "Image.h"


StatusType Image::setLabelScore(int pixel,int label,int score)
{
    LabelBylabel labelBylabel(label,score);
    if(labels[pixels->find(pixel)].labelsBylabel->contains(label)){
        labels[pixels->find(pixel)].labelsBylabel->Get(label).updateScore(score);
        return SUCCESS;
    }
    LabelByScore labelByScore(label,score);
    int indexInHeap=-1;
    indexInHeap = labels[pixels->find(pixel)].labelsByScore->Insert(labelByScore);
    labelBylabel.updateIndexInHeap(indexInHeap);
    labels[pixels->find(pixel)].labelsBylabel->Insert(labelBylabel,label);
    return SUCCESS;
}

StatusType Image::resetLabelScore(int pixel,int label)
{
    if(!labels[pixels->find(pixel)].labelsBylabel->contains(label))
        return FAILURE;
    int index = labels[pixels->find(pixel)].labelsBylabel->Get(label).getIndex();
    int maxScore = labels[pixels->find(pixel)].labelsByScore->FindMax().getScore();
    LabelByScore labelByScore(label,maxScore+1);
    labels[pixels->find(pixel)].labelsByScore->IncreaseKey(labelByScore,index);
    labels[pixels->find(pixel)].labelsByScore->DelMax();
    labels[pixels->find(pixel)].labelsBylabel->remove(label);
    return SUCCESS;
}
StatusType Image::highestScoredLabel(int pixel, int *label){
    if(!labels[pixels->find(pixel)].labelsByScore->GetSize())
        return FAILURE;
    *label = labels[pixels->find(pixel)].labelsByScore->FindMax().getLabel();
    return SUCCESS;
}
StatusType Image::mergeSuperPixels(int pixel1, int pixel2){
        int superPixel1=pixels->find(pixel1);
        int superPixel2=pixels->find(pixel2);
        if(superPixel1==superPixel2) return FAILURE;
        class CreateHeap{
        public:
            int index;
            LabelByScore* arr;
            CreateHeap(int size):index(0){
                arr = new LabelByScore[size];
            }
            ~CreateHeap(){
                delete[] arr;
            }
            void operator()(LabelBylabel& labelBylabel,int label){
                LabelByScore labelByScore(label,labelBylabel.getScore());
                labelBylabel.updateIndexInHeap(index);
                arr[index]=labelByScore;
                index++;
            }
        };
        class TrueClass{
        public:
            bool operator()(LabelBylabel& labelBylabel){
                return labelBylabel.getLabel();
            }
        };

        pixels->merge(pixel1,pixel2);
        TrueClass trueClass;
        labels[pixels->find(pixel1)].labelsBylabel->uniteTrees(labels[superPixel1].labelsBylabel,labels[superPixel2].labelsBylabel,trueClass);
        int size=labels[pixels->find(pixel1)].labelsBylabel->GetSize();
        CreateHeap createHeap(size);
        labels[pixels->find(pixel1)].labelsBylabel->InOrder(createHeap);
        MaxHeap<LabelByScore> maxHeap(size);
        delete labels[pixels->find(pixel1)].labelsByScore;
        labels[pixels->find(pixel1)].labelsByScore=new MaxHeap<LabelByScore>(2*size);
        labels[pixels->find(pixel1)].labelsByScore->MakeHeap(createHeap.arr,size);
        return  SUCCESS;
}
