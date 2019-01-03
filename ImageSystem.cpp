//
// Created by Tomer on 06/12/2018.
//
#include "List.h"
#include "memory.h"
#include "AVL.h"
#include "ImageSystem.h"
#include "dsexceptions.h"

using List::ListDict;
using AVL::AVLDict;
using std::shared_ptr;
Segment::Segment():label(-1),isEmpty(nullptr){}


Image::Image(int id,int numberOfSegments):id(id),
numberOfSegments(numberOfSegments),segments(new Segment[numberOfSegments]),
unTaggedSegments(ListDict<int,int>()){
    try {
        for (int i = 0; i < numberOfSegments; i++) {
            segments[i].isEmpty = unTaggedSegments.insert(i, i);
        }
    }
    catch(...) {
        // if failed rethrow an error
        delete [] segments;
        throw std::bad_alloc();
    }
}
void Image::tagSegment(int segmentID,int label){
    if(this->segments[segmentID].label!=-1){
        throw Failure();
    }
    this->segments[segmentID].label=label;
    this->unTaggedSegments.deleteByNode(this->segments[segmentID].isEmpty);
    this->segments[segmentID].isEmpty= nullptr;
}
int Image::getLabel(int segmentID){
    if(this->segments[segmentID].label==-1){
        throw Failure();
    }
    return this->segments[segmentID].label;
}
void Image::unTagSegment(int segmentID){
    if(this->segments[segmentID].label==-1){
        throw Failure();
    }
    this->segments[segmentID].label=-1;
    this->segments[segmentID].isEmpty= unTaggedSegments.insert(segmentID, segmentID);
}
void Image::getAllUnLabeledSegments(int** segments,int* numOfSegments){
    *numOfSegments = this->unTaggedSegments.getSize();
    if(*numOfSegments == 0){
        *segments= nullptr;
        throw Failure();
    }
    *segments = static_cast<int*>(malloc(*numOfSegments * sizeof(int)));
    if(*segments == nullptr){
        throw std::bad_alloc();
    }
    auto node = this->unTaggedSegments.getFirst();
    for(int i = 0; i < *numOfSegments;i++){
        (*segments)[i]=node->value;
        node=node->getNext();
    }
}

int Image::countLabel(int label){
    int counter = 0;
    for(int i=0;i<this->numberOfSegments;i++){
        if(this->segments[i].label ==label){
            counter++;
        }
    }
    return counter;
}
void Image::getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments){
    for(int i=0;i<this->numberOfSegments;i++){
        if(this->segments[i].label ==label){
            (*images)[*numOfSegments] = this->id;
            (*segments)[*numOfSegments] = i;
            (*numOfSegments)++;
        }
    }
}
Image::~Image(){
    delete [] segments;
}
ImageSystem::ImageSystem(int numOfSegments):images(),numOfSegments(numOfSegments){}

void ImageSystem::addImage(int imageID){
    if(imageID <=0){
        throw InvalidInput();
    }
    try{
        this->images[imageID];
    }
    catch (Failure& ex){
        // if the image is not in the system
        this->images.insert(imageID,shared_ptr<Image>(new Image(imageID,this->numOfSegments)));
        return;
    }
    // if the image is in the system
    throw Failure();

}
void ImageSystem::deleteImage(int imageID){
    if(imageID <=0){
        throw InvalidInput();
    }
    this->images.deleteByKey(imageID);
}
void ImageSystem::addLabel(int imageID,int segmentID,int label){
    if(segmentID <0 || segmentID >=this->numOfSegments || imageID <=0 || label<=0){
        throw InvalidInput();
    }
    this->images[imageID]->tagSegment(segmentID,label);
}
int ImageSystem::getLabel(int imageID,int segmentID){
    if(segmentID <0 || segmentID >=this->numOfSegments || imageID <=0){
        throw InvalidInput();
    }
    return this->images[imageID]->getLabel(segmentID);
}
void ImageSystem::deleteLabel(int imageID,int segmentID){
    if(segmentID <0 || segmentID >=this->numOfSegments || imageID <=0){
        throw InvalidInput();
    }
    this->images[imageID]->unTagSegment(segmentID);
}
void ImageSystem::getAllUnLabeledSegments(int imageID,int** segments,int* numOfSegments){
    if(imageID <=0 || segments == nullptr || numOfSegments == nullptr){
        throw InvalidInput();
    }
    this->images[imageID]->getAllUnLabeledSegments(segments,numOfSegments);
}
void ImageSystem::getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments){
    if(label<=0 || images== nullptr || segments == nullptr || numOfSegments == nullptr){
        throw InvalidInput();
    }
    auto node = this->images.getFirst();
    int size = 0;
    *numOfSegments =0;
    while (node){
        size+= node->value->countLabel(label);
        node=node->getNext();
    }
    if(size == 0){
        *segments = nullptr;
        *images = nullptr;
        return;
    }

    *images = static_cast<int*>(malloc(size * sizeof(int)));
    *segments = static_cast<int*>(malloc(size * sizeof(int)));

    // if the allocation fail clear memory and return error
    if(*images == nullptr || *segments == nullptr){
        free(*images);
        free(*segments);
        *images = nullptr;
        *segments = nullptr;
        throw std::bad_alloc();
    }
    node = this->images.getFirst();
    while (node){
        node->value->getAllSegmentsByLabel(label,images,segments,numOfSegments);
        node=node->getNext();
    }



}
