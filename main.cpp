#include <algorithm>

template <typename T>
class shared_ptr {
    T *m_ptr;
    size_t *count; //счетчик
public:
    shared_ptr() : m_ptr(nullptr), count(nullptr) {}
    shared_ptr(T *ptr) : m_ptr(ptr), count(new size_t(1)) {}
    ~shared_ptr()
    {
        if (count) {
            if (*count == 1) {
                delete count;
                delete m_ptr;
            }
            else (*count)--;
        }
    }
    void reset(T * ptr = nullptr) //переназначение указателя
    {
        shared_ptr(ptr).swap(*this);
    }
    T* operator->() const { //Возвращает сохраненный указатель
        return m_ptr;
    }
    T& operator* () const {  //Возвращает ссылку на объект, на который указывает сохраненный указатель
        return *m_ptr;
    }
    T * get() const { // геттер
        return m_ptr;
    }
    shared_ptr(shared_ptr<T> & other) : count(other.count), m_ptr(other.m_ptr) {
        if (m_ptr) (*count)++;
    } // конструктор копирования
    shared_ptr<T> operator=(shared_ptr<T> const & other) {
        if (this != &other) {
            if (count) {
                if (*count == 1) {
                    delete count;
                    delete m_ptr;
                }
                else (*count)--;
            }
            m_ptr = other.m_ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    } //оператор присваивания
    void swap(shared_ptr & b) { //Обменивает содержимое двух указателей
        std::swap(m_ptr, b.m_ptr);
        std::swap(count, b.count);
    }
    size_t use_count() const {
        if(count) {
            return *count;
        }
        else {
            return 0;
        }
    }
};
