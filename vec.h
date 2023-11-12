template<typename T> struct Vec {
private:
    // Variables
    T* array = nullptr;
    size_t length;

    // Modifiers
    void resize(size_t capacity);
    
public:
    Vec();
    Vec(T el);
    Vec(T el, T els...);

    // Getters
    const size_t length() const;
    const size_t capacity() const;

    // Setters
    void set_capacity(size_t new_capacity);

    // Modifiers
    void push(T el);
    void clear();

    // Operators
    T& operator[](size_t index);
};
