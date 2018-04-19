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
    for(int i = 0; i < imgs; i ++) {
        imgUrls[i] = '\0';
        imgData[i] = '\0';
        imgSize[i] = 0;
    }
}

EMSCRIPTEN_KEEPALIVE void setImgUrl(char* url, int index, int length) {
    if(imgUrls) {
        imgUrls[index] = malloc((length + 1) * sizeof(char));
        strcpy(imgUrls[index], url);
    }
}

EMSCRIPTEN_KEEPALIVE void setImgData(char* data, int index, int length) {
    if(imgData) {
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
