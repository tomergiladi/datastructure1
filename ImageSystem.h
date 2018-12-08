//
// Created by Tomer on 07/12/2018.
//

#ifndef DATASTRUCTURE1_IMAGESYSTEM_H
#define DATASTRUCTURE1_IMAGESYSTEM_H

#include "List.h"
#include "AVL.h"
#include "memory.h"
struct Segment{
    int label;
    std::shared_ptr<List::Node<int,int>> isEmpty;
    Segment();
};
class Image{
    const int id;
    const int numberOfSegments;
    Segment* segments;
    List::ListDict<int,int> unTaggedSegments;

public:
    Image(int id,int numberOfSegments);
    void tagSegment(int segmentID,int label);
    int getLabel(int segmentID);
    void unTagSegment(int segmentID);
    void getAllUnLabeledSegments(int** segments,int* numOfSegments);
    int countLabel(int label);
    void getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments);
    ~Image();


};
class ImageSystem{
    AVL::AVLDict<int,std::shared_ptr<Image>> images;
    const int numOfSegments;
public:
    explicit ImageSystem(int numOfSegments);

    void addImage(int imageID);
    void deleteImage(int imageID);
    void addLabel(int imageID,int segmentID,int label);
    int getLabel(int imageID,int segmentID);
    void deleteLabel(int imageID,int segmentID);
    void getAllUnLabeledSegments(int imageID,int** segments,int* numOfSegments);
    void getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments);


};
#endif //DATASTRUCTURE1_IMAGESYSTEM_H
