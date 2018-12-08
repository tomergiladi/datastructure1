//
// Created by Tomer on 07/12/2018.
//
#include "library2.h"
#include "ImageSystem.h"
#include "dsexceptions.h"
void *Init(int segments){
    if(segments<=0){
        return nullptr;
    }
    return new ImageSystem(segments);
}
StatusType AddImage(void *DS, int imageID){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->addImage(imageID);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }
}
StatusType DeleteImage(void *DS, int imageID){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->deleteImage(imageID);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }
}
StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->addLabel(imageID,segmentID,label);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }
}
StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
    if(DS==nullptr || label== nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        *label=imageSystem->getLabel(imageID,segmentID);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }
}
StatusType DeleteLabel(void *DS, int imageID, int segmentID){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->deleteLabel(imageID,segmentID);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }
}
StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,
                                   int* numOfSegments){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->getAllUnLabeledSegments(imageID,segments,numOfSegments);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }

}
StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int
*numOfSegments){
    if(DS==nullptr){
        return INVALID_INPUT;
    }
    try {
        auto imageSystem = static_cast<ImageSystem*>(DS);
        imageSystem->getAllSegmentsByLabel(label,images,segments,numOfSegments);
        return SUCCESS;
    }
    catch (Failure&){
        return FAILURE;
    }
    catch (InvalidInput&){
        return INVALID_INPUT;
    }
    catch(std::bad_alloc& err){
        return ALLOCATION_ERROR;
    }

}
void Quit(void **DS){
    if(DS== nullptr){
        return;
    }
    auto imageSystem= static_cast<ImageSystem*>(*DS);

    delete imageSystem;
    *DS= nullptr;
}




