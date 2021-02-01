#ifndef VRA_STORAGE_H
#define VRA_STORAGE_H

#include "FlashIAPBlockDevice.h"
#include "TDBStore.h"
#include "mbed.h"
#include <cstring>

class VRAStorage {
public:

  VRAStorage(EventQueue *p_eq);

  void init();

  int set(const char *key, const void *buf, size_t buf_size);
  int get(const char *key, void *buf, size_t buf_size);

  int remove(const char *key);

  void printStorageInfo(void);

private:
  FlashIAPBlockDevice *bd;
  TDBStore *tdbstore;
  EventQueue *eq;
};

#endif