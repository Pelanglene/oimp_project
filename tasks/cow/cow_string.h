#pragma once
#include <string_view>
#include <string>

class CowString {
public:
    class CharProxy {
    private:
        CowString* cow_string_;
        size_t pos_;
    public:

        CharProxy(CowString* cow_string, size_t pos);

        CharProxy& operator=(char c);

        operator char();
        operator char() const;
    };
    

    class Iterator {
    private:
        CowString* cow_string_;
        size_t pos_;
    public:    
        Iterator(CowString* cow_string, size_t pos);

        CharProxy operator*();

        Iterator& operator++();

        bool operator!=(const Iterator& other) const;
    };
    
    class InternalCowString {
    private:
        std::string str_;
        size_t ref_count_ = 0;
    public:
        InternalCowString(const std::string& ggstr_);
        size_t& GetRefCount();
        std::string& GetStrRef();
    };

    class ConstCharProxy {
    private:
        const CowString* cow_string_;
        size_t pos_;
    public:
        ConstCharProxy(const CowString* cow_string, size_t pos);
        operator char() const;
    };

    class ConstIterator {
    private:
        const CowString* cow_string_;
        size_t pos_;
    public:    
        ConstIterator(const CowString* cow_string, size_t pos);

        ConstCharProxy operator*() ;

        ConstIterator& operator++() ;

        bool operator!=(const ConstIterator& other) const;
    };

    CowString(std::string_view str_);

    CowString(const CowString& other);

    CowString& operator=(const CowString& other);

    CowString(CowString&& other);

    CowString& operator=(CowString&& other);

    ~CowString();

    char& operator[](size_t pos_);

    char& At(size_t pos_) const;


    char* GetData() const;

    Iterator begin();

    Iterator end();

    ConstIterator begin() const;

    ConstIterator end() const;

    CowString operator+(const CowString& other);

    CowString operator+(const std::string_view& other);

    friend std::string_view operator+(const std::string_view& strw, const CowString& cows);

    CowString& operator+=(const std::string_view& other);
    
    CowString& operator+=(const CowString& other);

    friend std::string_view operator+=(std::string_view& strw, const CowString& cows);

    bool operator==(const std::string_view& other);

    friend bool operator==(const std::string_view& other, const CowString& cows);

    bool operator!=(const std::string_view& other);

    friend bool operator!=(const std::string_view& other, const CowString& cows);

    operator std::string_view() {
        return internal_str_->GetStrRef();
    }

private:
    InternalCowString* internal_str_ = nullptr;
};