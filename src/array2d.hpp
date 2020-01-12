#include "array2d.h"
#include <iostream>
using namespace std;


template<typename T>
const unsigned int math::Array2D<T>::getWidth() const {

	return this->width;

}

template<typename T>
const unsigned int math::Array2D<T>::getHeight() const {

	return this->height;

}

template<typename T>
T* math::Array2D<T>::getRawDataPtr() {

	return &buffer[0];
}

template <typename T>
void math::Array2D<T>::setData(const T* const& data_ptr) {


	int size = getWidth() * getHeight() * 3;
	if (buffer.empty()) {						//If buffer is empty, just push back all the values of the data_ptr.
		for (int k = 0;k < size;k++)
			buffer.push_back(*(data_ptr + k));

		return;
		
	}


	if (getHeight() == 0 || getWidth() == 0 ) {						//Check if width or height = 0.
		cout << "ERROR." << endl;
		cout << "The height or the width is not valid." << endl;
		return;
	}
	try {												//Check if the size of the array cannot be resized.
		for (int k = 0;k < size;k++) {
			buffer.at(k) = *(data_ptr + k);
		}
		
	}
	catch (...) {								//catch the exception.
		cout << "ERROR." << endl;
		cout << "The buffer can not be resized." << endl;
		return;
	}

}

template<typename T>
T& math::Array2D<T>::operator () (unsigned int x, unsigned int y) {
	T ZERO = NULL;
	if (x >= 0 && x < getHeight() && y >= 0 && y < getWidth()) {			//Check if data is valid.
		
		return buffer[x * getWidth() + y];					
	}
	
	return ZERO;
}


template<typename T>
math::Array2D<T>::Array2D(unsigned int w, unsigned int h, const T* data) :width(w), height(h) {
	
	int size = w * h;
	
	if (data == NULL && w > 0 && h > 0) {
		for (int i = 0; i < size; i++) {
			buffer.push_back(0);
		}
	}
	
	setData(data);					//Set the buffer.

}

template<typename T>
math::Array2D<T>::Array2D(const Array2D& src): width(src.width), height(src.height) {

	buffer = src.buffer;

}

template<typename T>
math::Array2D<T>::~Array2D() {


}
template<typename T>
math::Array2D<T>& math::Array2D<T>::operator=(const Array2D& right) {
	this->width = right.getWidth();
	this->height = right.getHeight();
	this->buffer = right.buffer;

	return *this;

}






