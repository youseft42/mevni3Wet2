#include "Ds.h"

Ds::Ds(int pixels) : pixels(pixels), allImages(10) {}

StatusType Ds::AddImage(int imageID) {
    if (allImages.contains(imageID)) return FAILURE;
    Image newImage(imageID, pixels);
    try {
        allImages.Insert(newImage, imageID);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Ds::DeleteImage(int imageID) {
    if (!(allImages.contains(imageID))) return FAILURE;
    try {
        allImages.GetData(imageID).destroyImage();
        allImages.Delete(imageID);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Ds::SetLabelScore(int imageID, int pixel, int label, int score) {
    if (imageID <= 0 || pixel >= pixels || pixel < 0 || label <= 0 || score <= 0)
        return INVALID_INPUT;
    if (!(allImages.contains(imageID))) return FAILURE;
    try {
        allImages.GetData(imageID).setLabelScore(pixel, label, score);
    }catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Ds::ResetLabelScore(int imageID, int pixel, int label) {
    if (imageID <= 0 || pixel >= pixels || pixel < 0 || label <= 0)
        return INVALID_INPUT;
    if (!(allImages.contains(imageID))) return FAILURE;
    return allImages.GetData(imageID).resetLabelScore(pixel, label);
}

StatusType Ds::GetHighestScoredLabel(int imageID, int pixel, int *label) {
    if (imageID <= 0 || pixel >= pixels || pixel < 0 || label <= 0)
        return INVALID_INPUT;
    if (!(allImages.contains(imageID))) return FAILURE;
    return allImages.GetData(imageID).highestScoredLabel(pixel, label);
}

StatusType Ds::MergeSuperPixels(int imageID, int pixel1, int pixel2) {
    if (imageID <= 0 || pixel1 >= pixels || pixel1 < 0 || pixel2 >= pixels || pixel2 < 0)
        return INVALID_INPUT;
    if (!(allImages.contains(imageID))) return FAILURE;
    return allImages.GetData(imageID).mergeSuperPixels(pixel1, pixel2);
}