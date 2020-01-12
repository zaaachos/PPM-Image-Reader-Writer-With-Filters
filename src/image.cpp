#include "../../ppm/src/ppm.h"
#include "vec3.h"
#include "imageio.h"
#include "array2d.h"
#include<iostream> 
#include<array>
#include<string>
#ifndef Color
#define Color math::Vec3<float>
#endif

using namespace std;



namespace image {



	class Image : public math::Array2D<Color>, public image::ImageIO {


		
	public:
		float* temp = nullptr;							//Data for class Image.
		int w = 0;
		int h = 0;
		unsigned int wid = 0;
		unsigned int hei = 0;
		math::Array2D<Color>* rgb = nullptr;
		Color* pixels = nullptr;
		int len = 0;




		//Default Image Constructor (empty image)
		Image() {
		}

		//Image Constructor
		Image(unsigned int width, unsigned int height)
			: temp(new float[width * height * 3]), wid(width), hei(height) {			
			setPixels();			//Set the pixels of the Image we create.
		}
	

		//Image Copy Constructor.
		Image(const Image& copy) {
			pixels = copy.pixels;
			w = copy.w;
			h = copy.h;
			temp = copy.temp;
			rgb = copy.rgb;
			len = copy.len;
		}
		

		//Setter For Image Width.
		void setWid(unsigned int num) {
			wid = num;
		}

		//Getter of Image Width.
		unsigned int getWid() {
			return wid;
		}

		//Setter For Image Height.
		void setHei(unsigned int num) {
			hei = num;
		}

		//Getter of Image Height.
		unsigned int getHei() {
			return hei;
		}

		//Store pixels we got from image loading, to the pixels array.
		void setPixels() {


			for (len; len < w * h * 3; len += 3) {
				Color pixel(temp[len], temp[len + 1], temp[len + 2]);				//Store R - G - B.
				pixels[len / 3] = pixel;


			}

			rgb = new math::Array2D<Color>(w, h, pixels);			//Set the rgb array with the values we got.
			
		}

		//Get Pixels we want.
		Color getPixel(unsigned int x, unsigned int y) {
			Color pixel;
			if (x >= 0 && x < getHei() && y >= 0 && y < getWid()) {			//Check for invalid data.
				pixel.r = x * getWid() + y;
				pixel.g = x * getWid() + y + 1;
				pixel.b = x * getWid() + y + 2;
				
				return pixel;

			}
				
			else {									//Else return zeros ( 0 ).
				
				pixel.r = 0.f;
				pixel.g = 0.f;
				pixel.b = 0.f;
				return pixel;
			}


		}


		virtual bool image::ImageIO::load(const std::string& filename, const std::string& format) {				//Method to load the image data from a file.
			bool loading = true;			//bool loading to use it if the loading completes.

			temp = image::ReadPPM(filename.c_str(), &w, &h);
			string ppm = filename.substr(filename.find_last_of('.') + 1);				//Save the format of the filename parameter.
			unsigned int sz = ppm.size();

			setWid(w);
			setHei(h);
			
			pixels = new Color[getWid() * getHei()*3];

			cout << "Loading the file: " + filename + "\nTest the format...\nFormat: " + ppm;

			if (format.size() != sz) {				//First of all, check if the size equals to the size of the format given as parameter.
				cout << " ( ERROR! Only '.ppm' format is valid.)" << endl;
				return false;
			}


			for (unsigned int i = 0; i < sz; i++) {									//Check if the filename format equals to the format 'ppm',with case-insensitive comparison.
				if (tolower(ppm[i]) != tolower(format[i])) {
					cout << " ( ERROR! Only '.ppm' format is valid.)" << endl;
					return false;
				}
			}
			cout << " (OK!)." << endl;
			return loading;			//If the loading completes, return true.

		}

		virtual bool image::ImageIO::save(const std::string& filename, const std::string& format) {				//Method to save the image data to a specified file.
			bool saving = false;			//bool saving to use it if we complete the saving.

			if (temp == nullptr) {												//Check if the array data we want to save is not empty.
				cout << "I have no array data to write to: " + filename << endl;
				return saving;
			}
			string ppm = filename.substr(filename.find_last_of('.') + 1);				//Save the format of the filename parameter.
			unsigned int sz = ppm.size();
			cout << "Saving the file...\nTest the format...\nFormat: " + ppm;

			if (format.size() != sz) {				//First of all, check if the size equals to the size of the format given as parameter.
				cout << " ( ERROR! Only '.ppm' format is valid.)" << endl;
				return false;
			}


			for (unsigned int i = 0; i < sz; i++) {									//Check if the filename format equals to the format 'ppm',with case-insensitive comparison.
				if (tolower(ppm[i]) != tolower(format[i])) {
					cout << " ( ERROR! Only '.ppm' format is valid.)" << endl;

					return false;
				}
			}
			cout << " (OK!)." << endl;

			saving = image::WritePPM(temp, w, h, filename.c_str());
		

			return saving;			//If we complete the saving, return true.

		}


	};



}
