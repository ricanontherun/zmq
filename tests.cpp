#include "zmq_functions.h"
#include "zmq.hpp"
#include <assert.h>

void test_extract_to_void_buffer()
{
  // Build the zmq message.
  std::string data = "Christian Roman";
  zmq::message_t message((void *) data.c_str(), data.length());

  // Extract it into a voi *
  void * extracted_data = NULL;
  std::size_t extracted_length = 0;
  ZMQFunctions::extract(message, &extracted_data, extracted_length);

  assert(extracted_data);
  assert(extracted_length);

  // Create a string and compare against the original data.
  std::string extracted_string((char *) extracted_data);

  assert(extracted_string == data);

  if ( extracted_data ) free(extracted_data);
}

void test_extract_to_string()
{
  // Build the zmq message.
  std::string data = "Christian Roman";
  zmq::message_t message((void *) data.c_str(), data.length());

  std::string extracted_string;
  ZMQFunctions::extract(message, extracted_string);

  assert(extracted_string == data);
}

void test_pack_success()
{
  std::string data = "Christian Roman";
  zmq::message_t message;

  ZMQFunctions::pack(message, (void *) data.c_str(), data.length());

  assert(message.size() == data.size());

  // Extract it
  void * extracted_data = malloc(message.size());

  memcpy(extracted_data, message.data(), message.size());

  assert(extracted_data);

  std::string extracted_string((char *) extracted_data);

  assert(extracted_string.length() == data.length());

  if ( extracted_data ) free(extracted_data);
}

int main() {
  test_extract_to_void_buffer();

  test_extract_to_string();

  test_pack_success();

}
