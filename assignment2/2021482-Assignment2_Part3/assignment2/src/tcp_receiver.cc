#include "tcp_receiver.hh"


#include <algorithm>


using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader head = seg.header();
    auto data = seg.payload().copy();
    // ...

    // --- Hint ------
        // convert the seqno into absolute seqno
    
    // --- Hint ------  
    if (head.syn && _synReceived)
    {
        return;
    }
    bool eof = false;
    if(head.syn && !_synReceived){
        _synReceived = true;
        _isn = head.seqno;
        if (head.fin)
        {
            _finReceived = true;
            eof = true;
        }
        _reassembler.push_substring(data, 0, eof);
        return;
    }
    if (_synReceived && head.fin)
    {
        /* code */
        _finReceived = true;
        eof = true;
    }
    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t abs_seqno = unwrap(head.seqno, _isn, checkpoint);
    uint64_t stream_idx = abs_seqno - _synReceived;

    _reassembler.push_substring(data, stream_idx, eof);    
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    if(!_synReceived){
        return nullopt;
    }
    return wrap(_reassembler.ack_index() + 1 +(_reassembler.empty() && _finReceived), _isn);
}

size_t TCPReceiver::window_size() const { return stream_out().remaining_capacity();  }
