#include "VRAStorage.h"

VRAStorage::VRAStorage(EventQueue *p_eq) : eq(p_eq)
{
  this->bd = new FlashIAPBlockDevice(0x76000, 2 * 4096); //0x74000, 4 * 4096); // Bootloader start 0x78000
  this->tdbstore = new TDBStore(this->bd);
}

void VRAStorage::init()
{
  this->bd->init();
  this->tdbstore->init();
  //   this->printStorageInfo();
}

void VRAStorage::printStorageInfo(void)
{
  printf("Flash block device size: %llu\n",
         this->bd->size()); // Get the total size of the underlying device. in
                            // bytes (total size)
  printf("Flash block device read size: %llu\n",
         this->bd->get_read_size()); // Get the size of a readable block. in
                                     // bytes (min size)
  printf("Flash block device program size: %llu\n",
         this->bd->get_program_size()); // Get the size of a programable block.
                                        // in bytes (min size)
  printf("Flash block device erase size: %llu\n",
         this->bd->get_erase_size()); // Get the size of a eraseable block. in
                                      // bytes (one page)
}

int VRAStorage::set(const char *key, const void *buf, size_t buf_size)
{
  return this->tdbstore->set(key, buf, buf_size, 0);
} 

int VRAStorage::get(const char *key, void *buf, size_t buf_size)
{
  size_t actual_size;
  return this->tdbstore->get(key, buf, buf_size, &actual_size);
}

int VRAStorage::remove(const char *key) { return this->tdbstore->remove(key); }