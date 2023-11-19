#pragma once

#include <iostream>
#include <cstring>
#include <assert.h>
#include <format>

#include "vec.h"

namespace stringc {
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
            this->m_array[this->m_length] = '\0';

            strcpy(this->m_array, string);
        }
        String(const String& other) : m_length(other.length()) {
            this->m_array = new char[this->m_length + 1];
            this->m_array[this->m_length] = '\0';

            strcpy(this->m_array, other.m_array);
        }
        String(const std::string other) : m_length(other.length()) {
            this->m_array = new char[this->m_length + 1];
            this->m_array[this->m_length] = '\0';
            
            strcpy(this->m_array, other.data());
        }

        ~String() {
            delete[] this->m_array;
        }

        // Getters
        const size_t length() const {
            return m_length;
        }
        const char* stringc() const {
            return m_array;
        }

        vec::Vec<char> chars() {
            vec::Vec<char> char_vec;
            for(size_t i = 0; i < this->m_length; i++) {
                char_vec.push(this->m_array[i]);
            }

            return char_vec;
        }

        // Modifiers
        String slice(size_t start, size_t end) {
            assert(!(start > end));

            char* slice_buff = new char[end - start + 1];
            slice_buff[end - start] = '\0';
            strncpy(slice_buff, this->m_array + start, end - start);

            String slice = slice_buff;
            delete[] slice_buff;

            return slice;
        };

        void concat(const char* other) {
            size_t new_size = this->m_length + strlen(other);
            char* buff = new char[new_size + 1];
            buff[0] = '\0';

            if(this->m_array != nullptr)
                strcat(buff, this->m_array);

            strcat(buff, other);
            buff[new_size] = '\0';

            delete[] this->m_array;
            this->m_array = buff;
            this->m_length = new_size;
        }
        
        void replace(const char* pattern, const char* to_replace) {
            size_t count = 0;

        };

        String repeat(size_t amount) {
            size_t new_length = this->m_length * amount;
            char* new_array = new char[new_length + 1];
            new_array[new_length] = '\0';

            strcpy(new_array, this->m_array);
            for(size_t i = 1; i < amount; i++) {
                // much faster than strcat(new_array, this->m_array)
                memcpy(new_array + (i * this->m_length), this->m_array, this->m_length);
            }

            String result = new_array;
            delete[] new_array;
            
            return result;
        }

        vec::Vec<String> split(const char* pattern) {
            vec::Vec<String> split_vec = {};
            const char* token = strtok(this->m_array, pattern);
            while(token != nullptr) {
                split_vec.push(String{token});
                token = strtok(nullptr, pattern);
            }

            return split_vec;
        }

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

        String& operator=(const String& other) {
            if(this != &other) {
                delete[] this->m_array;

                this->m_length = other.m_length;
                this->m_array = new char[this->m_length];
                
                strcpy(this->m_array, other.m_array);
            }

            return *this;
        }
    };
}