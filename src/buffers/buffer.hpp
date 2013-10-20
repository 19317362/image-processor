#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

#include <cstddef>

namespace processor {

// Used to convey the write position of a buffer.
struct write_marker {
public:
  uint8_t* write_pos;
  uint32_t remaining;

// Should be stack allocated.
private:
  void* operator new(size_t);          // standard new
  void* operator new(size_t, void*);   // placement new
  void* operator new[](size_t);        // array new
  void* operator new[](size_t, void*); // placement array new
};

class Buffer {
public:
  Buffer(uint32_t capacity);
  // Disable copy constructor.
  Buffer(const Buffer& that) = delete;
  // Called to resume writing to a buffer.
  write_marker getCurrentWritePosition();
  bool updateWritePosition(uint32_t num_bytes_written);
  uint8_t* getReadPosition();
  void reset();
  ~Buffer();

private:
  uint8_t* start_;
  uint32_t capacity_;
  uint32_t write_pos_;
};

}  // image-processor.

#endif