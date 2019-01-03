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
    // creates Image With numberOfSegments
    Image(int id,int numberOfSegments);

    // add label to segementID in the Image
    void tagSegment(int segmentID,int label);

    // return label at segmentdID in the Image
    int getLabel(int segmentID);

    // remove label at segmentID in the Image
    void unTagSegment(int segmentID);

    // returns all segments with no label in the Image
    void getAllUnLabeledSegments(int** segments,int* numOfSegments);

    // returns how many segemnts are labeled with label in the Image
    int countLabel(int label);
    void getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments);
    ~Image();


};
class ImageSystem{
    AVL::AVLDict<int,std::shared_ptr<Image>> images;
    const int numOfSegments;
public:

    // creates ImageSystem
    explicit ImageSystem(int numOfSegments);

    // adds a new a Image to the system
    void addImage(int imageID);

    // removes image with imageID from the system
    void deleteImage(int imageID);

    // add label to image with imageID at segementID
    void addLabel(int imageID,int segmentID,int label);

    // returns label from image with imageID at segementID
    int getLabel(int imageID,int segmentID);

    // removes label from image with imageID at segementID
    void deleteLabel(int imageID,int segmentID);

    // creates new Array at segments add all unlabeled segments of imageID to it
    // the array length is given at numOfSegments
    void getAllUnLabeledSegments(int imageID,int** segments,int* numOfSegments);

    // creates 2 new Arrays at images and segments add all (imagedID,segmentsID) that are labeled with label
    // the arrays length is given at numOfSegments
    void getAllSegmentsByLabel(int label,int **images,int** segments,int* numOfSegments);


};
#endif //DATASTRUCTURE1_IMAGESYSTEM_H
