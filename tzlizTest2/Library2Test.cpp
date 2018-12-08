#include <cstdio>
#include <iostream>
#include "Library2Test.h"
#include "../library2.h"
#include "testUtils.h"

#define SEGMENTS (1000)

static void *DS = NULL;
static int label = -1;
static int numOfSegments = -1;
static int *segments = NULL;
static int *images = NULL;

static void reset();

static void deleteAll();

static void addImage_dsNull();

static void addImage_idZero();

static void addImage_idNegative();

static void addImage_idAlreadyExist();

static void addImage_success();

static void deleteImage_dsNull();

static void deleteImage_idZero();

static void deleteImage_idNegative();

static void deleteImage_idDoesNotExist();

static void deleteImage_success();

static void addLabel_dsNull();

static void addLabel_idZero();

static void addLabel_idNegative();

static void addLabel_segmentNegative();

static void addLabel_segmentIsMaxPlusOne();

static void addLabel_segmentIsAboveMax();

static void addLabel_labelZero();

static void addLabel_labelNegative();

static void addLabel_idDoesNotExist();

static void addLabel_segmentAlreadyLabeled();

static void addLabel_success();

static void getLabel_dsNull();

static void getLabel_labelNull();

static void getLabel_idZero();

static void getLabel_idNegative();

static void getLabel_segmentNegative();

static void getLabel_segmentIsMaxPlusOne();

static void getLabel_segmentIsAboveMax();

static void getLabel_idDoesNotExist();

static void getLabel_segmentIsNotLabeled();

static void getLabel_success();

static void deleteLabel_dsNull();

static void deleteLabel_idZero();

static void deleteLabel_idNegative();

static void deleteLabel_segmentNegative();

static void deleteLabel_segmentIsMaxPlusOne();

static void deleteLabel_segmentIsAboveMax();

static void deleteLabel_idDoesNotExist();

static void deleteLabel_segmentIsNotLabeled();

static void getAllUnLabeledSegments_dsNull();

static void getAllUnLabeledSegments_segmentsNull();

static void getAllUnLabeledSegments_numOfSegmentsNull();

static void getAllUnLabeledSegments_idZero();

static void getAllUnLabeledSegments_idNegative();

static void getAllUnLabeledSegments_idDoesNotExist();

static void getAllUnLabeledSegments_noUnlabeledSegments();

static void getAllUnLabeledSegments_success();

static void getAllSegmentsByLabel_dsNull();

static void getAllSegmentsByLabel_imagesNull();

static void getAllSegmentsByLabel_segmentsNull();

static void getAllSegmentsByLabel_numOfSegmentsNull();

static void getAllSegmentsByLabel_labelZero();

static void getAllSegmentsByLabel_labelNegative();

static void getAllSegmentsByLabel_noLabels();

static void getAllSegmentsByLabel_success();

static void quit_dsNull();

static void quit_nullAfter();

static void reset() {
    deleteAll();

    DS = Init(SEGMENTS);

    label = -1;
    numOfSegments = -1;
    segments = NULL;
    images = NULL;
}

static void deleteAll() {
    Quit(&DS);

    if (segments != NULL) {
        free(segments);
        segments = NULL;
    }
    if (images != NULL) {
        free(images);
        images = NULL;
    }
}

void Library2Test::test() {
    reset();
    addImage_dsNull();
    reset();
    addImage_idZero();
    reset();
    addImage_idNegative();
    reset();
    addImage_idAlreadyExist();
    reset();
    addImage_success();
    reset();
    deleteImage_dsNull();
    reset();
    deleteImage_idZero();
    reset();
    deleteImage_idNegative();
    reset();
    deleteImage_idDoesNotExist();
    reset();
    deleteImage_success();
    reset();
    addLabel_dsNull();
    reset();
    addLabel_idZero();
    reset();
    addLabel_idNegative();
    reset();
    addLabel_segmentNegative();
    reset();
    addLabel_segmentIsMaxPlusOne();
    reset();
    addLabel_segmentIsAboveMax();
    reset();
    addLabel_labelZero();
    reset();
    addLabel_labelNegative();
    reset();
    addLabel_idDoesNotExist();
    reset();
    addLabel_segmentAlreadyLabeled();
    reset();
    addLabel_success();
    reset();
    getLabel_dsNull();
    reset();
    getLabel_labelNull();
    reset();
    getLabel_idZero();
    reset();
    getLabel_idNegative();
    reset();
    getLabel_segmentNegative();
    reset();
    getLabel_segmentIsMaxPlusOne();
    reset();
    getLabel_segmentIsAboveMax();
    reset();
    getLabel_idDoesNotExist();
    reset();
    getLabel_segmentIsNotLabeled();
    reset();
    getLabel_success();
    reset();
    deleteLabel_dsNull();
    reset();
    deleteLabel_idZero();
    reset();
    deleteLabel_idNegative();
    reset();
    deleteLabel_segmentNegative();
    reset();
    deleteLabel_segmentIsMaxPlusOne();
    reset();
    deleteLabel_segmentIsAboveMax();
    reset();
    deleteLabel_idDoesNotExist();
    reset();
    deleteLabel_segmentIsNotLabeled();
    reset();
    getAllUnLabeledSegments_dsNull();
    reset();
    getAllUnLabeledSegments_segmentsNull();
    reset();
    getAllUnLabeledSegments_numOfSegmentsNull();
    reset();
    getAllUnLabeledSegments_idZero();
    reset();
    getAllUnLabeledSegments_idNegative();
    reset();
    getAllUnLabeledSegments_idDoesNotExist();
    reset();
    getAllUnLabeledSegments_noUnlabeledSegments();
    reset();
    getAllUnLabeledSegments_success();
    reset();
    getAllSegmentsByLabel_dsNull();
    reset();
    getAllSegmentsByLabel_imagesNull();
    reset();
    getAllSegmentsByLabel_segmentsNull();
    reset();
    getAllSegmentsByLabel_numOfSegmentsNull();
    reset();
    getAllSegmentsByLabel_labelZero();
    reset();
    getAllSegmentsByLabel_labelNegative();
    reset();
    getAllSegmentsByLabel_noLabels();
    reset();
    getAllSegmentsByLabel_success();
    reset();
    quit_dsNull();
    reset();
    quit_nullAfter();
    reset();
    deleteAll();
    std::cout << "End Library2Test." << std::endl;
}

static void addImage_dsNull() {
    assertTest(AddImage(NULL, 1) == INVALID_INPUT);
}

static void addImage_idZero() {
    assertTest(AddImage(DS, 0) == INVALID_INPUT);
}

static void addImage_idNegative() {
    assertTest(AddImage(DS, -1) == INVALID_INPUT);
}

static void addImage_idAlreadyExist() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(AddImage(DS, 1) == FAILURE);
}

static void addImage_success() {
    for (int i = 1; i <= 1000; i++) {
        assertTest(AddImage(DS, i) == SUCCESS);
    }
}

static void deleteImage_dsNull() {
    assertTest(DeleteImage(NULL, 1) == INVALID_INPUT);
}

static void deleteImage_idZero() {
    assertTest(DeleteImage(DS, 0) == INVALID_INPUT);
}

static void deleteImage_idNegative() {
    assertTest(DeleteImage(DS, -1) == INVALID_INPUT);
}

static void deleteImage_idDoesNotExist() {
    assertTest(DeleteImage(DS, 1) == FAILURE);
}

static void deleteImage_success() {
    for (int i = 1; i <= 1000; i++) {
        assertTest(AddImage(DS, i) == SUCCESS);
    }
    for (int i = 1; i <= 1000; i++) {
        assertTest(DeleteImage(DS, i) == SUCCESS);
    }
}

static void addLabel_dsNull() {
    assertTest(AddLabel(NULL, 1, 1, 1) == INVALID_INPUT);
}

static void addLabel_idZero() {
    assertTest(AddLabel(DS, 0, 1, 1) == INVALID_INPUT);
}

static void addLabel_idNegative() {
    assertTest(AddLabel(DS, -1, 1, 1) == INVALID_INPUT);
}

static void addLabel_segmentNegative() {
    assertTest(AddLabel(DS, 1, -1, 1) == INVALID_INPUT);
}

static void addLabel_segmentIsMaxPlusOne() {
    assertTest(AddLabel(DS, 1, SEGMENTS, 1) == INVALID_INPUT);
}

static void addLabel_segmentIsAboveMax() {
    assertTest(AddLabel(DS, 1, SEGMENTS + 1000, 1) == INVALID_INPUT);
}

static void addLabel_labelZero() {
    assertTest(AddLabel(DS, 1, 1, 0) == INVALID_INPUT);
}

static void addLabel_labelNegative() {
    assertTest(AddLabel(DS, 1, 1, -1) == INVALID_INPUT);
}

static void addLabel_idDoesNotExist() {
    assertTest(AddLabel(DS, 1, 1, 1) == FAILURE);
}

static void addLabel_segmentAlreadyLabeled() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(AddLabel(DS, 1, 1, 1) == SUCCESS);
    assertTest(AddLabel(DS, 1, 1, 1) == FAILURE);
}

static void addLabel_success() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(AddImage(DS, 2) == SUCCESS);
    for (int i = 1; i < SEGMENTS; i++) {
        assertTest(AddLabel(DS, 1, i, i) == SUCCESS);
        assertTest(AddLabel(DS, 2, i, i) == SUCCESS);
    }
}

static void getLabel_dsNull() {
    assertTest(GetLabel(NULL, 1, 1, &label) == INVALID_INPUT);
}

static void getLabel_labelNull() {
    assertTest(GetLabel(DS, 1, 1, NULL) == INVALID_INPUT);
}

static void getLabel_idZero() {
    assertTest(GetLabel(DS, 0, 1, &label) == INVALID_INPUT);
}

static void getLabel_idNegative() {
    assertTest(GetLabel(DS, -1, 1, &label) == INVALID_INPUT);
}

static void getLabel_segmentNegative() {
    assertTest(GetLabel(DS, 1, -1, &label) == INVALID_INPUT);
}

static void getLabel_segmentIsMaxPlusOne() {
    assertTest(GetLabel(DS, 1, SEGMENTS, &label) == INVALID_INPUT);
}

static void getLabel_segmentIsAboveMax() {
    assertTest(GetLabel(DS, 1, SEGMENTS + 1000, &label) == INVALID_INPUT);
}

static void getLabel_idDoesNotExist() {
    assertTest(GetLabel(DS, 1, 1, &label) == FAILURE);
}

static void getLabel_segmentIsNotLabeled() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(GetLabel(DS, 1, 1, &label) == FAILURE);
}

static void getLabel_success() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(AddImage(DS, 2) == SUCCESS);
    for (int i = 1; i < SEGMENTS; i++) {
        assertTest(AddLabel(DS, 1, i, i) == SUCCESS);
        assertTest(AddLabel(DS, 2, i, i) == SUCCESS);
    }

    for (int i = 1; i < SEGMENTS; i++) {
        assertTest(GetLabel(DS, 1, i, &label) == SUCCESS);
        assertTest(label == i);
        assertTest(GetLabel(DS, 2, i, &label) == SUCCESS);
        assertTest(label == i);
    }
}

static void deleteLabel_dsNull() {
    assertTest(DeleteLabel(NULL, 1, 1) == INVALID_INPUT);
}

static void deleteLabel_idZero() {
    assertTest(DeleteLabel(DS, 0, 1) == INVALID_INPUT);
}

static void deleteLabel_idNegative() {
    assertTest(DeleteLabel(DS, -1, 1) == INVALID_INPUT);
}

static void deleteLabel_segmentNegative() {
    assertTest(DeleteLabel(DS, 1, -1) == INVALID_INPUT);
}

static void deleteLabel_segmentIsMaxPlusOne() {
    assertTest(DeleteLabel(DS, 1, SEGMENTS) == INVALID_INPUT);
}

static void deleteLabel_segmentIsAboveMax() {
    assertTest(DeleteLabel(DS, 1, SEGMENTS + 1000) == INVALID_INPUT);
}

static void deleteLabel_idDoesNotExist() {
    assertTest(DeleteLabel(DS, 1, 1) == FAILURE);
}

static void deleteLabel_segmentIsNotLabeled() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(DeleteLabel(DS, 1, 1) == FAILURE);
}

static void getAllUnLabeledSegments_dsNull() {
    assertTest(GetAllUnLabeledSegments(NULL, 1, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllUnLabeledSegments_segmentsNull() {
    assertTest(GetAllUnLabeledSegments(DS, 1, NULL, &numOfSegments) == INVALID_INPUT);
}

static void getAllUnLabeledSegments_numOfSegmentsNull() {
    assertTest(GetAllUnLabeledSegments(DS, 1, &segments, NULL) == INVALID_INPUT);
}

static void getAllUnLabeledSegments_idZero() {
    assertTest(GetAllUnLabeledSegments(DS, 0, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllUnLabeledSegments_idNegative() {
    assertTest(GetAllUnLabeledSegments(DS, -1, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllUnLabeledSegments_idDoesNotExist() {
    assertTest(GetAllUnLabeledSegments(DS, 1, &segments, &numOfSegments) == FAILURE);
}

static void getAllUnLabeledSegments_noUnlabeledSegments() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    for (int i = 0; i < SEGMENTS; i++) {
        assertTest(AddLabel(DS, 1, i, i + 1) == SUCCESS);
    }

    assertTest(GetAllUnLabeledSegments(DS, 1, &segments, &numOfSegments) == FAILURE);
    assertTest(segments == NULL);
    assertTest(numOfSegments == 0);
}

static void getAllUnLabeledSegments_success() {
    assertTest(AddImage(DS, 1) == SUCCESS);

    for (int i = 200; i <= 800; i++) {
        assertTest(AddLabel(DS, 1, i, i + 1) == SUCCESS);
    }
    for (int i = 600; i <= 800; i++) {
        assertTest(DeleteLabel(DS, 1, i) == SUCCESS);
    }
    for (int i = 700; i < SEGMENTS; i++) {
        assertTest(AddLabel(DS, 1, i, i + 1) == SUCCESS);
    }

    // Labeled:   200-599, 700-SEGMENTS.
    // Unlabeled: 0-199  , 600-699.

    assertTest(GetAllUnLabeledSegments(DS, 1, &segments, &numOfSegments) == SUCCESS);

    assertTest(numOfSegments == 300);
    for (int i = 0; i < 200; i++) {
        assertNumberInArray(segments, numOfSegments, i);
    }
    for (int i = 600; i < 700; i++) {
        assertNumberInArray(segments, numOfSegments, i);
    }
}

static void getAllSegmentsByLabel_dsNull() {
    assertTest(GetAllSegmentsByLabel(NULL, 1, &images, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_imagesNull() {
    assertTest(GetAllSegmentsByLabel(DS, 1, NULL, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_segmentsNull() {
    assertTest(GetAllSegmentsByLabel(DS, 1, &images, NULL, &numOfSegments) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_numOfSegmentsNull() {
    assertTest(GetAllSegmentsByLabel(DS, 1, &images, &segments, NULL) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_labelZero() {
    assertTest(GetAllSegmentsByLabel(DS, 0, &images, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_labelNegative() {
    assertTest(GetAllSegmentsByLabel(DS, -1, &images, &segments, &numOfSegments) == INVALID_INPUT);
}

static void getAllSegmentsByLabel_noLabels() {
    assertTest(AddImage(DS, 1) == SUCCESS);
    assertTest(AddImage(DS, 2) == SUCCESS);

    assertTest(AddLabel(DS, 1, 1, 1) == SUCCESS);
    assertTest(AddLabel(DS, 2, 2, 2) == SUCCESS);

    assertTest(GetAllSegmentsByLabel(DS, 3, &images, &segments, &numOfSegments) == SUCCESS);
    assertTest(images == NULL);
    assertTest(segments == NULL);
    assertTest(numOfSegments == 0);
}

static void getAllSegmentsByLabel_success() {
    for (int i = 1; i <= 10; i++) {
        assertTest(AddImage(DS, i) == SUCCESS);
    }

    for (int i = 0; i < 200; i++) {
        for (int j = 1; j <= 10; j++) {
            assertTest(AddLabel(DS, j, i, 1) == SUCCESS);
        }
    }
    for (int i = 299; i >= 200; i--) {
        for (int j = 1; j <= 10; j++) {
            assertTest(AddLabel(DS, j, i, 3) == SUCCESS);
        }
    }
    for (int i = 300; i < 400; i++) {
        for (int j = 1; j <= 10; j++) {
            assertTest(AddLabel(DS, j, i, 2) == SUCCESS);
        }
    }
    for (int i = 400; i < 600; i++) {
        for (int j = 1; j <= 10; j++) {
            assertTest(AddLabel(DS, j, i, 3) == SUCCESS);
        }
    }
    for (int i = 400; i < 500; i++) {
        for (int j = 1; j <= 10; j++) {
            assertTest(DeleteLabel(DS, j, i) == SUCCESS);
        }
    }

    // Label 1: 0-199.
    // Label 2: 300-399.
    // Label 3: 200-299, 500-599.

    assertTest(GetAllSegmentsByLabel(DS, 1, &images, &segments, &numOfSegments) == SUCCESS);
    assertTest(numOfSegments == 2000);
    int segmentsCounter = 0;
    for (int i = 0; i < 2000; i++) {
        assertTest(images[i] == ((i / 200) + 1));
        assertTest(segments[i] == segmentsCounter);
        segmentsCounter++;
        if (segmentsCounter == 200) {
            segmentsCounter = 0;
        }
    }
    free(images);
    free(segments);

    assertTest(GetAllSegmentsByLabel(DS, 2, &images, &segments, &numOfSegments) == SUCCESS);
    assertTest(numOfSegments == 1000);
    segmentsCounter = 300;
    for (int i = 0; i < 1000; i++) {
        assertTest(images[i] == ((i / 100) + 1));
        assertTest(segments[i] == segmentsCounter);
        segmentsCounter++;
        if (segmentsCounter == 400) {
            segmentsCounter = 300;
        }
    }
    free(images);
    free(segments);

    assertTest(GetAllSegmentsByLabel(DS, 3, &images, &segments, &numOfSegments) == SUCCESS);
    assertTest(numOfSegments == 2000);
    segmentsCounter = 200;
    for (int i = 0; i < 2000; i++) {
        assertTest(images[i] == ((i / 200) + 1));
        assertTest(segments[i] == segmentsCounter);
        segmentsCounter++;
        if (segmentsCounter == 600) {
            segmentsCounter = 200;
        } else if (segmentsCounter == 300) {
            segmentsCounter = 500;
        }
    }
}

static void quit_dsNull() {
    Quit(NULL);
}

static void quit_nullAfter() {
    Quit(&DS);
    assertTest(DS == NULL);
}
int main(){
    Library2Test::test();
}
