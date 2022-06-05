#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    class ZippedIterator {
    public:
        ZippedIterator(Iterator a, Iterator b);
        ZippedIterator& operator++();
        ZippedPair operator*() const;
        bool operator!=(const ZippedIterator& other) const;
    private:
        std::pair<Iterator, Iterator> cur_; 
    };
    Zipped(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
    ZippedIterator begin();
    ZippedIterator end();
private:
    ZippedIterator beg_, end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
