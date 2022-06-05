#pragma once

#include <iterator>


template <typename Iterator1, typename Iterator2>
class Zipped {
private:
    class ZippedIterator {
    public:
        std::pair<Iterator1, Iterator2> cur_;
        using iterator1 = decltype(*cur_.first);
        using iterator2 = decltype(*cur_.second);

        ZippedIterator(Iterator1 a, Iterator2 b) {
            cur_ = {a, b};
        }

        std::pair<iterator1, iterator2> operator*() {
            return {*cur_.first, *cur_.second};
        }

        ZippedIterator& operator++() {
            ++cur_.first;
            ++cur_.second;
            return *this;
        }

        bool operator!=(const ZippedIterator& other) const {
            return cur_.first != other.cur_.first && cur_.second != other.cur_.second;
        }
    };

    ZippedIterator beg_, end_;

public:    
    Zipped(Iterator1 a_begin, Iterator1 a_end, Iterator2 b_begin, Iterator2 b_end) : beg_(a_begin, b_begin), end_(a_end, b_end) {}
    
    ZippedIterator begin() {
        return beg_;
    }

    ZippedIterator end() {
        return end_;
    }
};


template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
