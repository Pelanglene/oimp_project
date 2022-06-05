#include "zip.h"

Zipped::Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) : beg_(a_begin, b_begin), end_(a_end, b_end) {}

Zipped::ZippedIterator::ZippedIterator(Iterator a, Iterator b) : cur_({a, b}){}

bool Zipped::ZippedIterator::operator!=(const ZippedIterator& other) const {
    return cur_.first != other.cur_.first && cur_.second != other.cur_.second;
}

ZippedPair Zipped::ZippedIterator::operator*() const {
    return {*cur_.first, *cur_.second};
}

Zipped::ZippedIterator& Zipped::ZippedIterator::operator++() {
    ++cur_.first;
    ++cur_.second;
    return *this;
}

Zipped::ZippedIterator Zipped::begin() {
    return beg_;
}

Zipped::ZippedIterator Zipped::end() {
    return end_;
}

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    Zipped res(a_begin, a_end, b_begin, b_end);
    return res;
}