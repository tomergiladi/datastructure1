#include "vcatch.hpp"
#include "vMisc.hpp"
#include <iostream>

namespace Tests {
	using std::string;
	std::string StatusToString(StatusType st) {
		string a;
		switch (st) {
		case SUCCESS:
			a = "SUCCESS";
			break;
		case FAILURE:
			a = "FAILURE";
			break;
		case INVALID_INPUT:
			a = "INVALID_INPUT";
			break;
		case ALLOCATION_ERROR:
			a = "ALLOCATION_ERROR";
			break;
		}
		return a;
	}

	TEST_CASE("Testing Initialization of Datastructure") {
		SECTION("Checking whether 0 segments case was handled:") {
			REQUIRE(!Init(0));
		}
		SECTION("Checking whether negative segments case was handled:") {
			REQUIRE(!Init(-1));
		}
		SECTION("Checking creating of Data structure for segments > 1:") {
			auto ds = Init(1);
			REQUIRE(ds);
			Quit(&ds);
		}

	}
	TEST_CASE("Testing add image Function") {
		SECTION("Checking whether null DS ptr was handled:") {
			REQUIRE(StatusToString(AddImage(NULL, 5)) == StatusToString(INVALID_INPUT));
		}
		auto ds = Init(5);
		SECTION("Checking whether non-positive imageID was handled") {
			REQUIRE(StatusToString(AddImage(ds, 0)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative imageID was handled") {
			REQUIRE(StatusToString(AddImage(ds, -1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking successful addition of an image") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
		}
		SECTION("Checking Failure on addition of an image with existing id:") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(FAILURE));
		}
		Quit(&ds);
	}
	TEST_CASE("Testing Delete_image Function:") {
		SECTION("Checking whether null DS ptr was handled:") {
			REQUIRE(StatusToString(DeleteImage(NULL, 5)) == StatusToString(INVALID_INPUT));
		}
		auto ds = Init(5);
		SECTION("Checking whether non-positive imageID was handled") {
			REQUIRE(StatusToString(DeleteImage(ds, 0)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative imageID was handled") {
			REQUIRE(StatusToString(DeleteImage(ds, -1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking failure on removal of non existing image when there are no images at all") {
			REQUIRE(StatusToString(DeleteImage(ds, 1)) == StatusToString(FAILURE));
		}
		SECTION("Checking failure on removal of non existing image when there are images in the DS") {
			REQUIRE(StatusToString(AddImage(ds, 2)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(DeleteImage(ds, 1)) == StatusToString(FAILURE));
		}
		SECTION("Checking success on removal of an existing image:") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(DeleteImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS)); //should be able to add it again after removal
		}
		Quit(&ds);
	}
	TEST_CASE("Testing AddLabel function:") {
		SECTION("Checking whether null DS ptr was handled:") {
			REQUIRE(StatusToString(AddLabel(NULL, 5, 5, 4)) == StatusToString(INVALID_INPUT));
		}
		auto ds = Init(5);
		SECTION("Checking whether non-positive imageID was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 0, 5, 4)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative imageID was handled") {
			REQUIRE(StatusToString(AddLabel(ds, -1, 5, 4)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative segmentID was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 1, -1, 4)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether zero label ptr was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 1, 0)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative label ptr was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 1, -1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether segmentID==segments handled as error") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 5, 4)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether segmentID>segments handled as error") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 6, 4)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether zero label was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 4, 0)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether negative label was handled") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 4, -1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking failure on adding label to non-existing image") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 1, 1)) == StatusToString(FAILURE));
		}
		SECTION("Checking success on adding label to an existing image") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 1, 1, 1)) == StatusToString(SUCCESS));
		}
		SECTION("Checking failure on adding label to an segment that's already labeled") {
			REQUIRE(StatusToString(AddImage(ds, 2)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 2, 1, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 2, 1, 1)) == StatusToString(FAILURE));
		}
		Quit(&ds);;
	}
	TEST_CASE("Testing GetLabel function") {
		int label;
		SECTION("Checking whether null DS ptr was handled") {
			REQUIRE(StatusToString(GetLabel(NULL, 1, 1, &label)) == StatusToString(INVALID_INPUT));
		}
		auto ds = Init(5);
		AddImage(ds, 1);
		SECTION("Checking whether segmentID < 0 was handled") {
			REQUIRE(StatusToString(GetLabel(ds, 1, -1, &label)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID = 0 was handled") {
			REQUIRE(StatusToString(GetLabel(ds, 0, 1, &label)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID < 0 was handled") {
			REQUIRE(StatusToString(GetLabel(ds, -1, 1, &label)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether label null ptr was handled") {
			REQUIRE(StatusToString(GetLabel(ds, 1, 1, NULL)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking segmentID==segments was handled") {
			REQUIRE(StatusToString(GetLabel(ds, 1, 5, &label)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking segmentID>segments was handled") {
			REQUIRE(StatusToString(GetLabel(ds, 1, 6, &label)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking failure on getting label from non-existing image") {
			REQUIRE(StatusToString(GetLabel(ds, 2, 4, &label)) == StatusToString(FAILURE));
		}
		SECTION("Checking failure on getting label from image where the segment isn't labeled") {
			REQUIRE(StatusToString(GetLabel(ds, 1, 4, &label)) == StatusToString(FAILURE));
		}
		SECTION("Checking success on getting label") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 1, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetLabel(ds, 1, 1, &label)) == StatusToString(SUCCESS));
			REQUIRE(label == 1);
		}
		Quit(&ds);
	}
	TEST_CASE("Testing DeleteLabel function") {
		SECTION("Checking whether null DS ptr was handled") {
			REQUIRE(StatusToString(DeleteLabel(NULL, 1, 1)) == StatusToString(INVALID_INPUT));
		}
		auto ds = Init(5);
		AddImage(ds, 1);
		AddLabel(ds, 1, 1, 1);
		SECTION("Checking whether segmentID < 0 was handled") {
			REQUIRE(StatusToString(DeleteLabel(NULL, 1, 1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID = 0 was handled") {
			REQUIRE(StatusToString(DeleteLabel(ds, 0, 1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID < 0 was handled") {
			REQUIRE(StatusToString(DeleteLabel(ds, -1, 1)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking segmentID==segments was handled") {
			REQUIRE(StatusToString(DeleteLabel(ds, 1, 5)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking segmentID>segments was handled") {
			REQUIRE(StatusToString(DeleteLabel(ds, 1, 6)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking failure on getting label from non-existing image") {
			REQUIRE(StatusToString(DeleteLabel(ds, 2, 1)) == StatusToString(FAILURE));
		}
		SECTION("Checking failure on getting label from image where the segment isn't labeled") {
			REQUIRE(StatusToString(DeleteLabel(ds, 1, 2)) == StatusToString(FAILURE));
		}
		SECTION("Checking success on delete of label") {
			REQUIRE(StatusToString(AddLabel(ds, 1, 2, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(DeleteLabel(ds, 1, 2)) == StatusToString(SUCCESS));
		}
		Quit(&ds);
	}
	TEST_CASE("Testing GetAllUnLabeledSegments function:") {
		int dummy;
		int* segments = &dummy;
		int numOfSegments;
		auto ds = Init(1);
		SECTION("Checking whether null DS ptr was handled") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(NULL, 5, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether null segments ptr was handled") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(NULL, 5, NULL, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether null numOfsegments ptr was handled") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, 5, &segments, NULL)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID = 0 was handled") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, 0, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether imageID < 0 was handled") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, -1, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking failure on getting the unlabeled segments from non-existing image") {
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, 1, &segments, &numOfSegments)) == StatusToString(FAILURE));
		}
		SECTION("Checking failure on getting the unlabeled segments from an image without free segments") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 1, 0, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, 1, &segments, &numOfSegments)) == StatusToString(FAILURE));
		}
		SECTION("Checking succes on getting the unlabeled segments from an image") {
			REQUIRE(StatusToString(AddImage(ds, 2)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetAllUnLabeledSegments(ds, 2, &segments, &numOfSegments)) == StatusToString(SUCCESS));
			REQUIRE(numOfSegments == 1);
			REQUIRE(*segments == 0);
			free(segments);
		}
		Quit(&ds);
	}
	TEST_CASE("Testing GetAllSegmentsByLabel function:") {
		int dummy1;
		int dummy2;
		int* segments = &dummy1;
		int* images = &dummy2;
		int numOfSegments;
		auto ds = Init(3);
		SECTION("Checking whether null DS ptr was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(NULL, 5, &images, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether null images ptr was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, NULL, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether null segments ptr was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, &images, NULL, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether null numOfsegments ptr was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, &images, &segments, NULL)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether label = 0 was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 0, &images, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking whether label < 0 was handled") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, -1, &images, &segments, &numOfSegments)) == StatusToString(INVALID_INPUT));
		}
		SECTION("Checking NULL in images/segments and 0 in numOfSegments on getting non-existing label") {
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, &images, &segments, &numOfSegments)) == StatusToString(SUCCESS));
			REQUIRE_NOTHROW(!images);
			REQUIRE_NOTHROW(!segments);
			REQUIRE(numOfSegments == 0);
		}
		SECTION("Checking Success on 1 picture with 1 label") {
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 1, 2, 5)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, &images, &segments, &numOfSegments)) == StatusToString(SUCCESS));
			REQUIRE(images[0] == 1);
			REQUIRE(segments[0] == 2);
			REQUIRE(numOfSegments == 1);
			free(images);
			free(segments);
		}
		SECTION("Checking Success on 1 picture with 2 label") {
			REQUIRE(StatusToString(AddImage(ds, 2)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 2, 2, 4)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 2, 1, 4)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 4, &images, &segments, &numOfSegments)) == StatusToString(SUCCESS));
			REQUIRE(images[0] == 2);
			REQUIRE(images[1] == 2);
			REQUIRE(segments[0] == 1);
			REQUIRE(segments[1] == 2);
			REQUIRE(numOfSegments == 2);
			free(images);
			free(segments);
		}
		SECTION("Checking Success on 2 picture with 2 label") {
			REQUIRE(StatusToString(AddImage(ds, 3)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddImage(ds, 1)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 1, 2, 5)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 3, 2, 5)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(AddLabel(ds, 3, 1, 5)) == StatusToString(SUCCESS));
			REQUIRE(StatusToString(GetAllSegmentsByLabel(ds, 5, &images, &segments, &numOfSegments)) == StatusToString(SUCCESS));
			REQUIRE(images[0] == 1);
			REQUIRE(images[1] == 3);
			REQUIRE(images[2] == 3);
			REQUIRE(segments[0] == 2);
			REQUIRE(segments[1] == 1);
			REQUIRE(segments[2] == 2);
			REQUIRE(numOfSegments == 3);
			free(images);
			free(segments);
		}
		Quit(&ds);
	}
}