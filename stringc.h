#include <string>

struct String {
private:
    // Variables
    char* array;
    size_t length;

    void m_to(size_t start, size_t end, int offset);
    template<typename T> T m_contains(const char* pattern);
public:
    String slice(size_t start, size_t end);

    String();
    String(const char* string);
    String(const String& other);
    String(const std::string other);
    
    // Modifiers
    void replace(const char* pattern, const char* to_replace);
    void to_lower();
    void to_upper();
    
    int index_of(const char* pattern);
    bool contains(const char* pattern);
};