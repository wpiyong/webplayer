#ifdef __cplusplus
extern "C" {
#endif

int imgTotal = 0;
int imgTotalNew = 0;

char** imgUrls;     // image url array, array size = total images
char** imgData;     // image data array, array size = total images
int* imgSize;       // image size array, array size = total images
int* list;          // revolution sets array, max array size 10
int listSize = 0;   // total revolutions usually 10, but can be less
int* imgUrlSize;

char** imgUrlsNew;
char** imgDataNew;
int* imgSizeNew;
int* listNew;
int listSizeNew = 0;
int* imgUrlSizeNew;

char** imgUrlsLeft;
int* imgSizeLeft;
int* listLeft;
int*imgUrlSizeLeft;

int imgFinished = 0;
int downloadIndex = -1;
int newRevolutionSets = 0;
int totalRevolutionSets;

#ifdef __cplusplus
}
#endif
