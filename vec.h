#include <functional>

template<typename T>
struct Vec {
private:
    T* m_vec = nullptr;
    size_t m_length = 0;
    size_t m_capacity = 1;

    void resize(size_t new_capacity) {
        T* new_vec = new T[new_capacity];
        std::copy(this->m_vec, this->m_vec + this->m_length, new_vec);
        
        delete[] this->m_vec;

        this->m_vec = new_vec;
        this->m_capacity = new_capacity;
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

        else if (capacity == 0) {
            throw std::runtime_error("New capacity cannot be 0.");
        }

        this->resize(capacity);
    }
    
    // Modifiers
    void push(T el) {
        if(this->m_length >= this->m_capacity) {
            this->resize(this->m_capacity * 2);
        }

        this->m_vec[this->m_length++] = el;
    }

    void extend(Vec<T> vec) {
        if(this->m_length + vec.length() >= this->m_capacity) {
            this->resize(this->m_length + vec.length() + vec.capacity() + 99);
        }

        std::copy(vec.m_vec, vec.m_vec + vec.length(), this->m_vec + this->m_length);
        this->m_length += vec.length();
    }

    void clear() {
        delete[] this->m_vec;
        this->m_capacity = 1;
        this->m_length = 0;
    }

    Vec<T>& map(std::function<T(T)> fn) {
        for(size_t i = 0; i < this->m_length; i++) {
            this->m_vec[i] = fn(this->m_vec[i]);
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