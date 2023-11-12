#include <iostream>
#include <vector>

template<typename T>
struct Vec {
private:
    T* m_vec = nullptr;
    size_t m_length = 0;
    size_t m_capacity = 1;

    void resize(size_t new_capacity) {
        T* new_vec = new T[new_capacity];
        std::copy(this->m_vec, this->m_vec + this->m_length, new_vec);
        
        delete[] m_vec;

        this->m_vec = new_vec;
        this->m_capacity = new_capacity;

        delete[] new_vec;
    }

public:
    Vec():  m_vec(new T[1]), m_length(0), m_capacity(1) {};
    Vec(T el):  m_vec(new T[1]) { 
        this->push(el);
    }
    Vec(T el, T els...): m_vec(new T[1]) {
        this->push(el);
        this->push(els);
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

        this->resize(capacity);
    }
    
    // Modifiers
    void push(T el) {
        if(this->m_length == this->m_capacity) {
            this->resize(this->m_capacity * 2);
        }

        this->m_vec[this->m_length++] = el;
    }

    void clear() {
        delete[] this->m_vec;
        this->m_capacity = 1;
        this->m_length = 0;
    }

    // Operators
    T& operator[](size_t index) {
        if(index > this->m_capacity) {
            throw std::out_of_range("Index is out of bounds.");
        }

        return this->m_vec[index];
    }
};

struct Point {
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};
};

int main() {
    Point x = {122, 22};
    Point y = {69, 45};
    Vec<Point> vec = {x, y};

    std::cout << "SUI" << std::endl;
    std::cout << vec[1].x << std::endl;
    
    return 0;
}