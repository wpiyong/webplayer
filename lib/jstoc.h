#ifdef __cplusplus
extern "C" {
#endif

int imgTotal = 0;
int imgTotalNew = 0;

char** imgUrls;
char** imgData;
int* imgSize;
int* list;
int listSize = 0;

char** imgUrlsNew;
char** imgDataNew;
int* imgSizeNew;
int* listNew;
int listSizeNew = 0;
int* imgUrlSizeNew;

int imgFinished = 0;
int downloadIndex = 0;
int newRevolutionSets = 0;

#ifdef __cplusplus
}
#endif
