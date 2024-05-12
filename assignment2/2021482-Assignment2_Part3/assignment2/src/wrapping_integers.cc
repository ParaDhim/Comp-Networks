#include "wrapping_integers.hh"

#include <iostream>

using namespace std;
//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) { return isn + uint32_t(n); }

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    uint64_t plate = 0;
    uint64_t plate1 = 0;
    long long int my_var = 1ll;
    if (n - isn < 0) {
        plate = uint64_t(n - isn + (my_var << 32));
    } else {
        plate = uint64_t(n - isn);
    }
    if (plate >= checkpoint)
        return plate;
    plate |= ((checkpoint >> 32) << 32);
    while (plate <= checkpoint)
        plate += (my_var << 32);
    plate1 = plate - (my_var << 32);
    return (checkpoint - plate1 < plate - checkpoint) ? plate1 : plate;
}