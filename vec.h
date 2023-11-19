#pragma once

#include <functional>
#include <exception>
#include <iostream>

#include "mathc.h"

namespace vec {
    template<typename T>
    struct Vec {
    private:
        T* m_vec = nullptr;
        size_t m_length = 0;
        size_t m_capacity = 0;

    public:
        Vec():  m_vec(new T[1]), m_length(0), m_capacity(1) {};
        Vec(T el):  m_vec(new T[1]), m_capacity(1) { 
            this->push(el);
        }
        Vec(const Vec<T>& other) {
            delete[] this->m_vec;

            this->m_vec = other.m_vec;
            this->m_capacity = other.m_capacity;
            this->m_length = other.m_length; 
        }

        template<typename... Args>
        Vec(Args... els): m_vec(new T[1]), m_capacity(1) {
            (this->push(els), ...);
        }

        ~Vec() {
            delete[] this->m_vec;
        }

        // Getters
        const size_t length() const {
            return this->m_length;
        }

        const size_t capacity() const {
            return this->m_capacity;
        }

        // Setters
        
        // Modifiers
        void reserve(size_t new_size) {
            if(new_size > this->m_capacity) {
                T* reserved_vec = new T[new_size];

                for(size_t i = 0; i < this->m_length; i++) {
                    reserved_vec[i] = this->m_vec[i];
                }

                delete[] this->m_vec;
                this->m_vec = reserved_vec;
                this->m_capacity = new_size;
            }
        }
        
        void push(T el) {
            if(this->m_length == this->m_capacity) {
                this->reserve(
                    mathc::max<size_t>(1, mathc::ceil(this->m_capacity * mathc::HALF_PI))
                );
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