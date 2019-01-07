#include "library.h"
#include "Ds.h"

void * Init(int pixels){
    if (pixels <= 0) return NULL;
    return (void*) new Ds(pixels);
}

StatusType AddImage(void *DS, int imageID){
    if (DS == NULL || imageID <= 0) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->AddImage(imageID);
}

StatusType DeleteImage(void *DS, int imageID){
    if (DS == NULL || imageID <= 0) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->DeleteImage(imageID);
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){
    if (DS == NULL) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->SetLabelScore(imageID, pixel, label, score);
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){
    if (DS == NULL) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->ResetLabelScore(imageID, pixel, label);
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){
    if (DS == NULL) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->GetHighestScoredLabel(imageID, pixel, label);
}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){
    if (DS == NULL) return INVALID_INPUT;
    Ds* ds = (Ds*)DS;
    return ds->MergeSuperPixels(imageID, pixel1, pixel2);
}

void Quit(void** DS){
    if(DS) {
        Ds* tmp = (Ds*)(*DS);
        (*DS) = NULL;
        if (tmp)
            delete (tmp);
    }
}

