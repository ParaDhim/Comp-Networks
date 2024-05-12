#include "stream_reassembler.hh"

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    :_output(capacity),_first_unassembled_index(0),_stored_not_reassembled(0),_eof(false) ,_buffer(capacity,'\0'),_buff_bitmap(capacity,false),_capacity(capacity) {}


//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.

void StreamReassembler::check_contiguous() {
    string chk = "";
    while (_buff_bitmap.front())
    {
        chk += _buffer.front();
        _buffer.pop_front();
        _buff_bitmap.pop_front();
        _buffer.push_back('\0');
        _buff_bitmap.push_back(false);
    }
    if(chk.length() > 0){
        _output.write(chk);
        _first_unassembled_index += chk.length();
        _stored_not_reassembled -= chk.length();
    }
}


void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    
    if (eof)
    {
        _eof = true;
    }
    size_t ln = data.length();
    if(ln == 0 && _eof && _stored_not_reassembled == 0){
        _output.end_input();
        return;
    }
    if(index >= _first_unassembled_index + _capacity)return;

    if(index >= _first_unassembled_index){
        int offSet = index - _first_unassembled_index;
        size_t rl_ln = min(ln,_capacity - _output.buffer_size() - offSet);
        if (rl_ln < ln){
            _eof = false;
        }
        for(size_t i = 0;i < rl_ln;i++){
            if(_buff_bitmap[i + offSet]){
                continue;
            }
            _buffer[i + offSet] = data[i];
            _buff_bitmap[i + offSet] = true;
            _stored_not_reassembled++;
        }
        
    }else if(index + ln > _first_unassembled_index){
        int offSet = _first_unassembled_index - index;
        size_t rl_ln = min(ln - offSet,_capacity - _output.buffer_size());
        if (rl_ln < ln - offSet)
        {
            _eof = false;
        }
        for(size_t i = 0;i < rl_ln;i++){
            if(_buff_bitmap[i]){continue;}
            _buffer[i] = data[i + offSet];
            _buff_bitmap[i] = true;
            _stored_not_reassembled++;
        }
        
    }
    check_contiguous();
    if (_eof && _stored_not_reassembled == 0){
        _output.end_input();
    }
    
    
}


size_t StreamReassembler::unassembled_bytes() const { return _stored_not_reassembled;  }

bool StreamReassembler::empty() const { return _stored_not_reassembled == 0;  }

size_t StreamReassembler::ack_index() const { return _first_unassembled_index; }