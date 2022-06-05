#include "cow_string.h"

CowString::CowString(std::string_view str_) {
    internal_str_ = new InternalCowString(static_cast <std::string> (str_));
}

CowString::CowString(const CowString& other) {
    internal_str_ = other.internal_str_;
    internal_str_->GetRefCount()++;
}

CowString& CowString::operator=(const CowString& other) {
    if (internal_str_ == other.internal_str_) {
        return *this;
    }
    internal_str_->GetRefCount()--;
    if (internal_str_->GetRefCount() == 0) {
        delete internal_str_;
    }

    internal_str_ = other.internal_str_;
    internal_str_->GetRefCount()++;
    return *this;
}

CowString::CowString(CowString&& other) {
    std::swap(this->internal_str_, other.internal_str_);
}

CowString& CowString::operator=(CowString&& other) {   /// SUS
    std::swap(this->internal_str_, other.internal_str_);
    return *this;
}

CowString::~CowString() {
    internal_str_->GetRefCount()--;
    if (internal_str_->GetRefCount() == 0) {
        delete internal_str_;
    }
}

char& CowString::operator[](size_t pos_) {
    return internal_str_->GetStrRef()[pos_];
}

char& CowString::At(size_t pos_) const {
    return internal_str_->GetStrRef()[pos_];
}

char* CowString::GetData() const {
    return internal_str_->GetStrRef().data();
}

CowString::Iterator CowString::begin() {
    return Iterator(this, 0);
}

CowString::Iterator CowString::end() {
    return Iterator(this, internal_str_->GetStrRef().size());
}

CowString::ConstIterator CowString::begin() const {
    return ConstIterator(this, 0);
}

CowString::ConstIterator CowString::end() const {
    return ConstIterator(this, internal_str_->GetStrRef().size());
}

CowString::InternalCowString::InternalCowString(const std::string& ggstr_) {
    ref_count_ = 1;
    str_ = ggstr_;
}

size_t& CowString::InternalCowString::GetRefCount() {
    return ref_count_;
}

std::string& CowString::InternalCowString::GetStrRef() {
    return str_;
}

CowString::CharProxy::CharProxy(CowString* cow_string, size_t pos) : cow_string_(cow_string), pos_(pos) {}

CowString::CharProxy& CowString::CharProxy::operator=(char c) {
    if (c == cow_string_->At(pos_)) {
        return *this;
    }
    std::string buffer = cow_string_->internal_str_->GetStrRef();
    cow_string_->internal_str_->GetRefCount()--;
    buffer[pos_] = c;
    if (cow_string_->internal_str_->GetRefCount() == 0) {
        delete cow_string_->internal_str_;
    }
    cow_string_->internal_str_ = new InternalCowString(buffer);
    return *this;
}

CowString::CharProxy::operator char() {
    return cow_string_->At(pos_);
};

CowString::CharProxy::operator char() const {
    return cow_string_->At(pos_);
};

CowString::ConstCharProxy::ConstCharProxy(const CowString* cow_string, size_t pos) : cow_string_(cow_string), pos_(pos) {
}

CowString::ConstCharProxy::operator char() const {
    return cow_string_->At(pos_);
};

CowString::Iterator::Iterator(CowString* cow_string, size_t pos) {
    pos_ = pos;
    cow_string_ = cow_string;
}

CowString::CharProxy CowString::Iterator::operator*() {
    return CharProxy(cow_string_, pos_);
}

CowString::Iterator& CowString::Iterator::operator++() {
    pos_++;
    return *this;
}

bool CowString::Iterator::operator!=(const Iterator& other) const {
    return pos_ != other.pos_; 
}

CowString::ConstIterator::ConstIterator(const CowString* cow_string, size_t pos) : cow_string_(cow_string), pos_(pos) {
}

CowString::ConstCharProxy CowString::ConstIterator::operator*() {
    return ConstCharProxy(cow_string_, pos_);
}

CowString::ConstIterator& CowString::ConstIterator::operator++() {
    pos_++;
    return *this;
}


bool CowString::ConstIterator::operator!=(const ConstIterator& other) const {
    return pos_ != other.pos_; 
}



CowString CowString::operator+(const CowString& other) {
    return CowString(internal_str_->GetStrRef() + other.internal_str_->GetStrRef());
}

CowString CowString::operator+(const std::string_view& other) {
    return CowString(internal_str_->GetStrRef() + static_cast<std::string>(other));
}

CowString& CowString::operator+=(const std::string_view& other) {
    *this = CowString(internal_str_->GetStrRef() + static_cast <std::string> (other));
    return *this;
}

CowString& CowString::operator+=(const CowString& other) {
    *this = CowString(internal_str_->GetStrRef() + other.internal_str_->GetStrRef());
    return *this;
}

bool CowString::operator==(const std::string_view& other) {
    return other == internal_str_->GetStrRef();
}

bool operator==(const std::string_view& other, const CowString& cows) {
    return other == cows.internal_str_->GetStrRef();
}

bool CowString::operator!=(const std::string_view& other) {
    return !(*this == other);
}

bool operator!=(const std::string_view& other, const CowString& cows) {
    return cows != other;
}

