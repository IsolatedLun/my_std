#pragma once

#include <functional>

#include "mathc.h"

namespace vec {
    template<typename T>
    struct Vec {
    private:
        T* m_vec = nullptr;
        size_t m_length = 0;
        size_t m_capacity = 0;

        void resize(size_t new_capacity) {
            T* new_vec = new T[new_capacity];
            std::copy(this->m_vec, this->m_vec + this->m_length, new_vec);
            
            delete[] this->m_vec;

            this->m_vec = new_vec;
            this->m_capacity = new_capacity;
        }

    public:
        Vec():  m_vec(nullptr), m_length(0), m_capacity(0) {};
        Vec(T el):  m_vec(nullptr) { 
            this->push(el);
        }

        template<typename... Args>
        Vec(Args... els): m_vec(nullptr) {
            (this->push(els), ...);
        }

        // Getters
        const size_t length() const {
            return this->m_length;
        }

        const size_t capacity() const {
            return this->m_capacity;
        }

        // Setters
        void set_capacity(size_t capacity) {
            if(capacity <= this->m_capacity) {
                throw std::runtime_error("New capacity is less than the current capacity.");
            }

            else if (capacity == 0) {
                throw std::runtime_error("New capacity cannot be 0.");
            }

            this->resize(capacity);
        }
        
        // Modifiers
        void push(T el) {
            if(this->m_length >= this->m_capacity) {
                this->resize(mathc::max<size_t>(1, this->m_capacity * 2));
            }

            this->m_vec[this->m_length++] = el;
        }

        void extend(Vec<T> vec) {
            if(this->m_length + vec.length() >= this->m_capacity) {
                this->resize(this->m_length + vec.length() + vec.capacity());
            }

            std::copy(vec.m_vec, vec.m_vec + vec.length(), this->m_vec + this->m_length);
            this->m_length += vec.length();
        }

        void clear() {
            delete[] this->m_vec;

            this->m_vec = nullptr;
            this->m_capacity = 0;
            this->m_length = 0;
        }

        Vec<T>& map(std::function<void(T&)> fn) {
            for(size_t i = 0; i < this->m_length; i++) {
                fn(this->m_vec[i]);
            }

            return *this;
        }

        Vec<T> filter(std::function<bool(T)> fn) {
            Vec<T> new_vec;
            for(size_t i = 0; i < this->m_length; i++) {
                bool result = fn(this->m_vec[i]);
                if(result) {
                    new_vec.push(this->m_vec[i]);
                }
            }

            return new_vec;
        }

        Vec<T>& foreach(std::function<void(T)> fn) {
            for(size_t i = 0; i < this->m_length; i++) {
                fn(this->m_vec[i]);
            }

            return *this;
        }

        template<typename U>
        Vec<U> transform(std::function<U(T)> fn) {
            Vec<U> new_vec;
            for(size_t i = 0; i < this->m_length; i++) {
                new_vec.push(fn(this->m_vec[i]));
            }

            return new_vec;
        }
        template<typename U>
        Vec<U> transform() {
            Vec<U> new_vec;
            for(size_t i = 0; i < this->m_length; i++) {
                new_vec.push((U)(this->m_vec[i]));
            }

            return new_vec;
        }

        // Operators
        T& operator[](size_t index) {
            if(index > this->m_capacity) {
                throw std::out_of_range("Index is out of bounds.");
            }

            return this->m_vec[index];
        }

        Vec<T>& operator=(const Vec<T>& other) {
            if(this != &other) {
                delete[] this->m_vec;

                this->m_length = other.m_length;
                this->m_capacity = other.m_capacity;
                this->m_vec = new T[this->m_capacity];

                std::copy(other.m_vec, other.m_vec + other.m_length, this->m_vec);
            }

            return *this;
        }
    };
}