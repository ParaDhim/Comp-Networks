#include "byte_stream.hh"

#include <algorithm>
#include <vector>
#include <string>

// You will need to add private members to the class declaration in `byte_stream.hh`

/* Replace all the dummy definitions inside the methods in this file. */


using namespace std;

ByteStream::ByteStream(const size_t capa){
  _capacity = capa;
  _bytes_read = 0;
  _bytes_write = 0;
  myDeque = {};
  _eof = false;
  _error = false;
}

size_t ByteStream::write(const string &data) {
  if(_eof || eof()){
    return 0;
  }
  size_t len = data.length();
  size_t remCap = remaining_capacity();
  size_t ret = 0;
  if(len > remCap){
    for(size_t i = 0; i < remCap; i++){
      myDeque.push_back(data[i]);
      _bytes_write++;
      ret++;
    }
  }
  else{
    for(size_t i = 0; i < len; i++){
      myDeque.push_back(data[i]);
      _bytes_write++;
      ret++;
    }

  }
  return ret;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
  string ret = "";
  if(len > myDeque.size()){
    for(size_t i = 0; i < myDeque.size(); i++){
      ret += myDeque[i];
    }
  }
  else{
    for(size_t i = 0; i < len; i++){
      ret += myDeque[i];
    }
  
  }
  return ret;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
  if(len > myDeque.size()){
    _error = true;
    return;
  }
  for(size_t i = 0; i < len; i++){
    myDeque.pop_front();
  }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
  if(len > myDeque.size()){
    _error = true;
    return "";
  }
  string ret = "";
  for(size_t i = 0; i < len; i++){
  ret += myDeque.front();
  myDeque.pop_front();
  _bytes_read++;
}

  return ret;
}

void ByteStream::end_input() { 
  _eof = true;
}

bool ByteStream::input_ended() const { return _eof;}

size_t ByteStream::buffer_size() const {return myDeque.size(); }

bool ByteStream::buffer_empty() const {
  if(myDeque.empty()){
    return true;
  }
  else
  {
    return false;
  }
  
 }

bool ByteStream::eof() const { 
  if(_eof == true && myDeque.empty() == true){
    return true;
  }
  else{
    return false;
  }
}

size_t ByteStream::bytes_written() const { return _bytes_write;}

size_t ByteStream::bytes_read() const { return _bytes_write - myDeque.size();  }

size_t ByteStream::remaining_capacity() const { return _capacity - myDeque.size(); }
