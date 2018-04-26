#include "../../../WebAssembly/emsdk/emscripten/1.37.36/system/include/emscripten.h"
#include "../../../WebAssembly/emsdk/emscripten/1.37.36/system/include/libc/stdlib.h"
#include "../../../WebAssembly/emsdk/emscripten/1.37.36/system/include/libc/string.h"
#include "../../../WebAssembly/emsdk/emscripten/1.37.36/system/include/emscripten/fetch.h"

#include "emprintf.h"
#include "jstoc.h"


#ifdef __cplusplus
extern "C" {
#endif

int SIZE = 10;
static int data[10];

EMSCRIPTEN_KEEPALIVE void add(int value) {
  for (int i=0; i<SIZE; i++) {
    data[i] = data[i] + value;
  }
}

EMSCRIPTEN_KEEPALIVE int getData(int index) {
  return data[index];
}

EMSCRIPTEN_KEEPALIVE void setData( int value, int index) {
    if(index < SIZE){
        data[index] = value;
    }
}

EMSCRIPTEN_KEEPALIVE void createList(int revolutions) {
    list = (int*)malloc(sizeof(int)*revolutions);
    listSize = revolutions;
}

EMSCRIPTEN_KEEPALIVE void setListData(int value, int index) {
    list[index] = value;
}

EMSCRIPTEN_KEEPALIVE void createImgUrlArray(int imgs) {
    imgUrls = malloc(imgs * sizeof(char*));
    imgData = malloc(imgs * sizeof(char*));
    imgSize = malloc(imgs * sizeof(int));
    imgUrlSize = malloc(imgs * sizeof(int));
    for(int i = 0; i < imgs; i ++) {
        imgUrls[i] = '\0';
        imgData[i] = '\0';
        imgSize[i] = 0;
        imgUrlSize[i] = 0;
    }
}

EMSCRIPTEN_KEEPALIVE void setImgUrl(char* url, int index, int length) {
    if(imgUrls) {
        imgUrls[index] = malloc((length + 1) * sizeof(char));
        //strcpy(imgUrls[index], url);
        memcpy(imgUrls[index], url, length);
        imgUrls[index][length] = '\0';
        imgUrlSize[index] = length;
    }
}

EMSCRIPTEN_KEEPALIVE void setImgData(char* data, int index, int length) {
    if(imgData) {
        if(imgData[index]){
            free(imgData[index]);
        }
        imgData[index] = malloc((length + 1) * sizeof(char));
        memcpy(imgData[index], data, length);
        imgData[index][length] = '\0';
    }
    if(imgSize) {
        imgSize[index] = length;
    }
}

EMSCRIPTEN_KEEPALIVE void setImgTotal(int count) {
    imgTotal = count;
}

// get new revolutions 6 functions

EMSCRIPTEN_KEEPALIVE void createListNew(int revolutions) {
    listNew = (int*)malloc(sizeof(int)*revolutions);
    listSizeNew = revolutions;
}

EMSCRIPTEN_KEEPALIVE void setListDataNew(int value, int index) {
    listNew[index] = value;
}

EMSCRIPTEN_KEEPALIVE void createImgUrlArrayNew(int imgs) {
    imgUrlsNew      = malloc(imgs * sizeof(char*));
    imgDataNew      = malloc(imgs * sizeof(char*));
    imgSizeNew      = malloc(imgs * sizeof(int));
    imgUrlSizeNew   = malloc(imgs * sizeof(int));

    for(int i = 0; i < imgs; i ++) {
        imgUrlsNew[i]       = '\0';
        imgDataNew[i]       = '\0';
        imgSizeNew[i]       = 0;
        imgUrlSizeNew[i]    = 0;
    }
}

EMSCRIPTEN_KEEPALIVE void setImgUrlNew(char* url, int index, int length) {
    if(imgUrlsNew) {
        imgUrlsNew[index] = malloc((length + 1) * sizeof(char));
        //strcpy(imgUrlsNew[index], url);
        memcpy(imgUrlsNew[index], url, length);
        imgUrlsNew[index][length] = '\0';
        imgUrlSizeNew[index] = length;
    }
}

// this function is replace by emscripten fetch function
EMSCRIPTEN_KEEPALIVE void setImgDataNew(char* data, int index, int length) {
    if(imgDataNew) {
        if(imgDataNew[index]){
            free(imgDataNew[index]);
        }
        imgDataNew[index] = malloc((length + 1) * sizeof(char));
        memcpy(imgDataNew[index], data, length);
        imgDataNew[index][length] = '\0';
    }
    if(imgSizeNew) {
        imgSizeNew[index] = length;
    }
}

EMSCRIPTEN_KEEPALIVE void resetNewRevolutionSets(){
    if(listNew)
        free(listNew);
    if(imgSizeNew)
        free(imgSizeNew);
    if(imgUrlSizeNew)
        free(imgUrlSizeNew);

    int i = 0;
    if(imgUrlsNew) {
        for(i = 0; i < imgTotalNew; i++) {
            if(imgUrlsNew[i])
                free(imgUrlsNew[i]);
        }
        free(imgUrlsNew);
    }
    imgTotalNew = 0;
    listSizeNew = 0;
}

EMSCRIPTEN_KEEPALIVE void prepareNewRevolutionSets(){
    // clear the flag
    newRevolutionSets = 0;

    // free old
    if(list)
        free(list);
    if(imgSize)
        free(imgSize);
    int i = 0;
    if(imgUrls) {
        for(i = 0; i < imgTotal; i++) {
            if(imgUrls[i])
                free(imgUrls[i]);
        }
        free(imgUrls);
    }
    if(imgData) {
        for(i = 0; i < imgTotal; i++) {
            if(imgData[i])
                free(imgData[i]);
        }
        free(imgData);
    }
    imgTotal = imgTotalNew;
    listSize = listSizeNew;

    // create new
    emprintf("prepareNewRevolutionSets listSize: %d.", listSizeNew);
    createList(listSize);
    for(i = 0; i < listSize; i++) {
        emprintf("prepareNewRevolutionSets setListData: %d, %d.", listNew[i], i);
        setListData(listNew[i], i);
    }

    emprintf("prepareNewRevolutionSets createImgUrlArray: %d.", imgTotal);
    createImgUrlArray(imgTotal);
    for(i = 0; i < imgTotal; i++) {
        emprintf("prepareNewRevolutionSets setImgUrl: %d, %s.", i, imgUrlsNew[i]);
        setImgUrl(imgUrlsNew[i], i, imgUrlSizeNew[i]);
    }
}

EMSCRIPTEN_KEEPALIVE void setImgTotalNew(int count) {
    imgTotalNew = count;
    newRevolutionSets = count;
}

EMSCRIPTEN_KEEPALIVE void setTotalRevolutionSets(int count) {
    totalRevolutionSets = count;
}

void downloadSucceeded(emscripten_fetch_t *fetch) {
  emprintf("Finished downloading %llu bytes from URL %s.", fetch->numBytes, fetch->url);
  // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  setImgData(fetch->data, downloadIndex, fetch->numBytes);
  emscripten_fetch_close(fetch); // Free data associated with the fetch.
  imgFinished = 1;
}

void downloadFailed(emscripten_fetch_t *fetch) {
  emprintf("Downloading %s failed, HTTP failure status code: %d.", fetch->url, fetch->status);
  emscripten_fetch_close(fetch); // Also free data on failure.
  imgFinished = 1;
}

EMSCRIPTEN_KEEPALIVE void fetch(char* url, int index) {
    imgFinished = 0;
    emprintf("downloading from URL %s.", url);
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = downloadSucceeded;
    attr.onerror = downloadFailed;
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, url); // Blocks here until the operation is complete.
//    if (fetch->status == 200) {
//        emprintf("Finished downloading %llu bytes from URL %s.", fetch->numBytes, fetch->url);
//        // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
//        setImgData(fetch->data, index, fetch->numBytes);
//    } else {
//        emprintf("Downloading %s failed, HTTP failure status code: %d.", fetch->url, fetch->status);
//    }
//    emscripten_fetch_close(fetch);
}

#ifdef __cplusplus
}
#endif
