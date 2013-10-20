#include "buffer.hpp"

namespace processor {

Buffer::Buffer(uint32_t capacity) :
  capacity_(capacity),
  write_pos_(0),
  start_(new uint8_t[capacity]) {  // TODO: Shitty new, fix this.
  }

Buffer::~Buffer() {
  delete[] start_;
}

write_marker Buffer::getCurrentWritePosition() {
  return write_marker{start_+write_pos_, capacity_ - write_pos_ - 1};
}

uint8_t* Buffer::getReadPosition() {
  return start_;
}

bool Buffer::updateWritePosition(uint32_t num_bytes_written) {
  if ((num_bytes_written + write_pos_) <= capacity_ - 1) {
    write_pos_ += num_bytes_written;
    return true;
  }
  return false;
}

void Buffer::reset() {
  write_pos_ = 0;
}

}  // image-processor