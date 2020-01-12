#include <iostream>
#include "imageio.h"
#include "vec3.h"
#include "image.cpp"
#include <math.h>

using namespace std;
using namespace image;



namespace filter {


	class Filter {					//Abstract class Filter.
	private:
		Image* filtered = nullptr;							//Initiliazing a pointer that Points to the Image we want to apply our filters.
	public:
		virtual Image operator << (const Image& image) = 0;
		//Filter Default Constructor.
		Filter();

		//Filter Copy Constructor.
		Filter(const Filter& filter);

		//Filter Constructor.
		Filter(Image img);

		virtual ~Filter();
		
	};
	Filter::Filter(){}

	Filter::Filter(const Filter& filter) {
		this->filtered = filter.filtered;
	}

	Filter::Filter(Image img) {
		filtered = &img;
	}
	Filter::~Filter() {}

	class FilterLinear : public Filter {					//Class Filter Linear.

	public:
		Color a, c;

		//FilterLinear Default Constructor.
		FilterLinear() :Filter() {}

		//FilterLinear Constructor.
		FilterLinear(Image image) :Filter(image) {}

		//FilterLinear Copy Constructor.
		FilterLinear(const FilterLinear& fil) { 
			a = fil.a;
			c = fil.c;
		}
		virtual ~FilterLinear() {}

		//Operator << to apply the Filter Linear to the image.
		virtual Image operator << (const Image& image) {
			cout << "Applying Linear Filter: ";
			int k = 0;	
			int z = 0;
			
			//while not reach at the end of the image.
			while (z < image.len/3) {																
				image.pixels[z] = getParameterA() * image.pixels[z] + getParameterC();				//Apply the filter, by changing the rgb values.

				image.temp[k] = image.pixels[z].r > 1.0 ? 1.0: image.pixels[z].r < 0.0? 0.0: image.pixels[z].r;					//Apply the filter at array temp of the Image.

				image.temp[k + 1] = image.pixels[z].g > 1.0 ? 1.0 : image.pixels[z].g < 0.0 ? 0.0 : image.pixels[z].g;
				image.temp[k + 2] = image.pixels[z].b > 1.0 ? 1.0 : image.pixels[z].b < 0.0 ? 0.0 : image.pixels[z].b;
				k +=3;
				z++;
				
			}
			cout << "DONE."<<endl;
			return image;			//Return filtered image.


		}
		//Setter for paramater A.
		void setParameterA(float r, float g, float b) {
			a.r = r;
			a.g = g;
			a.b = b;
		}
		//Getter for paramater A.
		Color getParameterA() {
			return a;
		}
		//Setter for paramater C.
		void setParameterC(float r, float g, float b) {
			c.r = r;
			c.g = g;
			c.b = b;
		}
		//Getter for paramater C.
		Color getParameterC() {
			return c;
		}


	};//end of class FilterLinear

	class FilterGamma : public Filter {						//Class Filter Gamma.
	public:
		double y = 0.0;

		//FilterGamma Default Constructor.
		FilterGamma() :Filter() {}

		//FilterGamma Constructor.
		FilterGamma(Image image) :Filter(image) {}

		//FilterGamma Copy Constructor.
		FilterGamma(const FilterGamma& fil) {
			y = fil.y;
		}

		virtual ~FilterGamma() {}

		//Operator << to apply the Filter Gamma to the image.
		virtual Image operator << (const Image& image) {
			cout << "Applying Gamma Filter: ";
			int k = 0;
			int z = 0;
			
			//while not reach at the end of the image.
			while (z < image.len / 3) {	

				image.temp[k] = pow(image.pixels[z].r, getParameterY());									//Apply the filter, by changing the rgb values.
				image.temp[k + 1] =pow(image.pixels[z].g, getParameterY());
				image.temp[k + 2] = pow(image.pixels[z].b, getParameterY());
				k += 3;
				z++;

			}
			cout << "DONE." << endl;
			return image;				//Return filtered image.
		}

		//Setter for paramater y.
		void setParameterY(double num) {
			y = num < 0.5 ? 0.5 : num > 2.0 ? 2.0 : num;
		}

		//Getter for paramater y.
		double getParameterY() {
			return y;
		}

	};//end of class FilterGamma.

	class FilterBlur : public math::Array2D<float>, public Filter {
	public:
		
		int N = 0;

		//FilterBlur Default Constructor.
		FilterBlur() :Filter() {}

		//FilterBlur Constructor.
		FilterBlur(Image image) :Filter(image) {}

		//FilterGamma Copy Constructor.
		FilterBlur(const FilterBlur& fil) {
			N = fil.N;
		}
		virtual ~FilterBlur() {}

		void setN(unsigned int num) {
			N = num;
		}
		
		 int getN() {
			return N;
		}


		virtual Image operator << (const Image& image) {
			
			cout << "Applying Blur Filter: ";
			unsigned int height = image.hei;			//Get the height of the image.
			unsigned int width = image.wid;				//Get the width of the image.
			Color pixel;		//Get the pixel.
			unsigned int ind = 0;				//Index for array pixels.


			int sum = 0;		//Save the SUM.	
			float red = 0;
			float green = 0;
			float blue = 0;
			int k = 0;
		
			for (unsigned int j = 0; j < height; j++) {

				for (unsigned int i = 0; i < width; i++) {

					for (int m = -(getN() / 2); m < (getN() / 2); m++) {

						for (int n = -(getN() / 2); n < (getN() / 2); n++) {
							
							pixel = image.rgb->operator()(j + m, i + n);			//Get the pixel from the image.
				
							sum++;

							red += pixel.r;			//Change rgb values and increase the SUM.
							green += pixel.g;
							blue += pixel.b;
						}
					}
					
					image.pixels[ind].r = (red/sum);					//Store our new pixels.
					image.pixels[ind].g = (green/sum); 
					image.pixels[ind].b = (blue/sum);

					image.temp[k] = image.pixels[ind].r;									//Apply the filter, by changing the rgb values.
					image.temp[k + 1] = image.pixels[ind].g;
					image.temp[k + 2] = image.pixels[ind].b;

					ind++;			//increase index.

					sum = 0;
					red = 0;
					green = 0;
					blue = 0;
					k += 3;			//Go to next pixel.
				}
					
			}
			cout << "DONE" << endl;
			return image;				//Return filtered image.
		}


	};//end of class Filter Blur

}