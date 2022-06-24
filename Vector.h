#pragma once

#include <iostream>

using Value = double;

class Vector
{
public:
    Vector() = default;
    Vector(const Value* rawArray, const size_t size, float coef = 2.0f);

    explicit Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    explicit Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    void pushBack(const Value& value);


    void pushFront(const Value& value);


    void insert(const Value& value, size_t pos);
    void insert(const Value* values, size_t size, size_t pos);
    void insert(const Vector& vector, size_t pos);

    void popBack();


    void popFront();


    void erase(size_t pos, size_t count = 1);


    void eraseBetween(size_t beginPos, size_t endPos);


    size_t size() const;


    size_t capacity() const;


    double loadFactor() const;


    Value& operator[](size_t idx);
    const Value& operator[](size_t idx) const;

    long long find(const Value& value) const;
   
    void reserve(size_t capacity);

    void shrinkToFit();
	
    class Iterator
    {
        Value* _ptr;
    public:
        explicit Iterator(Value *ptr): _ptr(ptr){ }
    
        Value& operator*(){
            return *this->_ptr;
        }
    
        const Value& operator*() const{
            return *this->_ptr;
        }
    
        Value* operator->(){
            return this->_ptr;
        }
    
        const Value* operator->() const{
            return this->_ptr;
        }
    
        Iterator operator++(){
            this->_ptr++;
            return *this;
        }
    
        Iterator operator++(int){
            Iterator tmp = *this;
            this->_ptr++;
            return tmp;
        }
    
        bool operator==(const Iterator& other) const{
            return other._ptr == this->_ptr;
        }
    
        bool operator!=(const Iterator& other) const{
            return other._ptr != this->_ptr;
        }
    };

    Iterator begin(){
        return Iterator(_data);
    }
    Iterator end(){
        return Iterator(_data + _size);
    }


private:
    Value* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;

};
