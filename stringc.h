#include <iostream>
#include <cstring>
#include <assert.h>
#include <format>

struct String {
private:
    // Variables
    char* m_array;
    size_t m_length;

    // Modifiers
    void m_to(size_t start, size_t end, int offset) {
        for(int i = 0; i < this->m_length; i++) {
            if(this->m_array[i] >= start && this->m_array[i] <= end) {
                this->m_array[i] = (char)(this->m_array[i] + offset);
            }
        }
    };

    template<typename T>
    T m_contains(const char* pattern) {
         int offset = strlen(pattern);
        for(size_t i = 0; i <= this->m_length; i++) {
            String slice = this->slice(i, i + offset);
            if(strcmp(slice.stringc(), pattern) == 0) {
                return typeid(T) == typeid(int) ? i : true;
            }
        }

        return typeid(T) == typeid(int) ? -1 : false;
    }
public:
    String(): m_array(nullptr), m_length(0) {};
    String(const char* string) : m_length(strlen(string)) {
        this->m_array = new char[this->m_length + 1];
        strcpy(this->m_array, string);

        this->m_length = strlen(string);
    }
    String(const String& other) : m_length(other.length()) {
        this->m_array = new char[this->m_length + 1];
        strcpy(this->m_array, other.m_array);

        this->m_length = other.length();
    }
    String(const std::string other) : m_length(other.length()) {
        this->m_array = new char[this->m_length + 1];
        strcpy(this->m_array, other.data());

        this->m_length = other.length();
    }

    ~String() {
        delete[] m_array;
    }

    // Getters
    const size_t length() const {
        return m_length;
    }
    const char* stringc() const {
        return m_array;
    }

    // Modifiers
    String slice(size_t start, size_t end) {
        assert(!(start > end));

        char* slice_buff = new char[end - start + 1];
        for(size_t i = 0; i + start <= end; i++) {
            slice_buff[i] = this->m_array[i + start];
        }

        slice_buff[end - start] = '\0';
        String new_string = slice_buff;

        delete[] slice_buff;
        return new_string;
    };

    void concat(const char* other) {
        size_t new_size = this->m_length + strlen(other) + 1;
        char* buff = new char[new_size];
        
        strcat(buff, this->m_array);
        strcat(buff, other);
        buff[new_size] = '\0';

        delete[] this->m_array;
        this->m_array = buff;
        this->m_length = new_size;
        delete[] buff;
    }
    
    void replace(const char* pattern, const char* to_replace) {
        size_t count = 0;

    };

    void to_lower() {
        m_to(65, 90, 32);
    };
    void to_upper() {
        m_to(97, 122, -32);
    };
    
    int index_of(const char* pattern) {
        return this->m_contains<int>(pattern);
    };

    bool contains(const char* pattern) {
        return this->m_contains<bool>(pattern);       
    };

    // Vec<char> chars() {
    //     Vec<char> char_vec;
    // }


    // Operators
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.m_array;
        return os;
    }
};