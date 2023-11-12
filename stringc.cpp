#include <iostream>
#include <cstring>
#include <string>
#include <assert.h>
#include <format>

struct String {
private:
    // Variables
    char* m_array;
    size_t length;

    // Modifiers
    void m_to(size_t start, size_t end, int offset) {
        for(int i = 0; i < this->length; i++) {
            if(this->m_array[i] >= start && this->m_array[i] <= end) {
                this->m_array[i] = (char)(this->m_array[i] + offset);
            }
        }
    };

    template<typename T>
    T m_contains(const char* pattern) {
         int offset = strlen(pattern);
        for(size_t i = 0; i < this->length; i++) {
            String slice = this->slice(i, i + offset);
            if(strcmp(slice.stringc(), pattern) == 0) {
                return typeid(T) == typeid(int) ? i : true;
            }
        }

        return typeid(T) == typeid(int) ? -1 : false;
    }
public:
    String(): m_array(nullptr), length(0) {};
    String(const char* string) : length(strlen(string)) {
        this->m_array = new char[this->length + 1];
        strcpy(this->m_array, string);

        this->length = strlen(string);
    }
    String(const String& other) : length(other.length) {
        this->m_array = new char[this->length + 1];
        strcpy(this->m_array, other.m_array);

        this->length = other.length;
    }
    String(const std::string other) : length(other.length()) {
        this->m_array = new char[this->length + 1];
        strcpy(this->m_array, other.data());

        this->length = other.length();
    }

    ~String() {
        delete[] m_array;
    }

    // Getters
    const size_t size() const {
        return length;
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

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.m_array;
        return os;
    }
};


int main() {
    String x = "hello world zz {{}}";

    std::cout << x.index_of("zz")  << std::endl;

    return 0;
}