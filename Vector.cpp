#include <iostream>
#include <exception>
#include <string>
#include "Vector.h"

Vector::Vector(const Value* rawArray, const size_t size, float coef){
	_data = new Value[static_cast<size_t>(size*coef)];
	_multiplicativeCoef = coef;
	_size = size;
	_capacity = static_cast<size_t>(size*coef);

	for(size_t i = 0; i < size; i++)
		_data[i] = rawArray[i];
}

size_t Vector::size() const{
	return _size;
}

size_t Vector::capacity() const{
	return _capacity;
}

double Vector::loadFactor() const{
	return static_cast<double>(_size/_capacity);
}

Vector::Vector(const Vector& other){
	if ((this != &other) && other._capacity <= static_cast<size_t>(other._size * _multiplicativeCoef)){ 
        delete[] _data;  
    	_data = new Value[other._capacity];
    	for (size_t i = 0; i < other._size; i++) 
        	_data[i] = other._data[i];
        
    	_size = other._size;        
    	_capacity = other._capacity;
    }
}


Vector::Vector(Vector&& other) noexcept{
    if ((this != &other) && other._capacity <= static_cast<size_t>(other._size * _multiplicativeCoef)){
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = other._capacity = 0;
    }
}


Vector& Vector::operator=(const Vector& other){
    if ((this != &other)) {
        delete[] _data;
      	_data = new Value[other._capacity];
      	for (size_t i = 0; i < other._size; i++) 
      		_data[i] = other._data[i];
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if ((this != &other)) {
        delete[] _data;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = nullptr;
        other._size = other._capacity = 0;
    }
    return *this;
}


void Vector::pushBack(const Value& value){
	if(_size == 0) reserve(_multiplicativeCoef);
	else if(_size >= _capacity) reserve(_size * _multiplicativeCoef);
	_data[_size++] = value;
}


void Vector::pushFront(const Value& value){
	if(_size == 0) reserve(_multiplicativeCoef);
	if(_size >= _capacity) return; //reserve(_size * _multiplicativeCoef);

	Value tmp = _data[0];
	_data[0] = value;

	for(size_t i = 1; i < _size; i++){
		Value tmp_ =_data[i];
		_data[i] = tmp;
		tmp = tmp_;
	}

	_data[_size] = tmp; _size++;
}

void Vector::popBack(){
	try{
		if(_size == 0) throw "empty vector";
		_size--;
	} catch(std::string str){
		std::cout << str << std::endl;
	}
}

void Vector::popFront(){
	try{
		if(_size == 0) throw "empty vector";
		for(size_t i = 0; i < _size-1; i++)
			_data[i] = _data[i+1];
		_size--;
	} catch(std::string str){
		std::cout << str << std::endl;
	}
}

Value& Vector::operator[](size_t idx){
	return _data[idx];
}

const Value& Vector::operator[](size_t idx) const{
	return _data[idx];
}

Vector::~Vector(){
	delete[] _data;
}


void Vector::insert(const Value& value, size_t pos){
	if(_size >= _capacity) return; //reserve(_capacity * _multiplicativeCoef);
	if(pos > _size || pos < 0) return;
	Value tmp = _data[pos];
	_data[pos] = value;
	for(size_t i = pos+1; i < _size; i++){
		Value _tmp = _data[i];
		_data[i] = tmp;
		tmp = _tmp;
	}
	_data[_size] = tmp;
	_size++;
}

void Vector::insert(const Value* values, size_t size, size_t pos){
	if(_size + size > _capacity || pos < 0) return;
	if(pos > _size) return;
	for(size_t i = 0; i < size; i++)
		this->insert(values[i], pos+i);
}

void Vector::insert(const Vector& vector, size_t pos){
	if(_size + vector.size() > _capacity || pos < 0) return;
	if(pos > _size) return;

	for(size_t i = 0; i < vector.size(); i++){
		this->insert(vector[i], pos + i);
	}
}

void Vector::erase(size_t pos, size_t count){
	try{
		if(_size == 0) throw "empty vector";
		if (pos < 0 || count <= 0) return;
		if(pos + count > _size){
			_size = pos;
		}
		else {
			for(size_t i = pos; i < _size - count; i++)
			_data[i] = _data[i + count];
			_size = _size - count;
		}
	}
	catch(std::string str){
		std::cout << str << std::endl;
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
	try{
		if(_size == 0) throw "empty vector";
		if(beginPos < 0 || beginPos > endPos) return;
		if(endPos > _size){
			_size = beginPos;
		}
		else{
			int k = endPos;
			for(size_t i = beginPos; i < _size - (endPos - beginPos); i++){
				_data[i] = _data[k]; k++;
			}
			_size = _size - (endPos - beginPos);
		}
	} catch(std::string str){
		std::cout << str << std::endl;
	}
}

long long Vector::find(const Value& value) const{
	for(size_t i = 0; i < _size; i++)
		if(value == _data[i]) return i;
	return -1;
}

void Vector::reserve(size_t capacity){
	if(capacity > _capacity){
		Value *tmp = new Value[capacity];
    	
		_capacity = capacity;
		for(size_t i = 0; i < _size; i++)
			tmp[i] = _data[i];

		delete [] _data;


    	_data = new Value[_capacity];
    	for(size_t i = 0; i < _size; i++)
       		_data[i] = tmp[i];

    	delete[] tmp;
	}
}

void Vector::shrinkToFit(){
	if(_capacity > _size){
		Value *tmp = new Value[_size];
		for(size_t i = 0; i < _size; i++)
			tmp[i] = _data[i];
		delete[] _data;

		_data = new Value[_size];
		for(size_t i = 0; i < _size; i++)
			_data[i] = tmp[i];
		_capacity = _size;

		delete [] tmp;
	}
}
