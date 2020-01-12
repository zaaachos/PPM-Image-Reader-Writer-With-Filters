# _PPM_ IMAGE MANIPULATION

This is a C++ academic project that converts images from/to ppm format. Furthermore, applies multiple filters such as linear, gamma and blur.

First of all, it uses a static library named `ppm` , which you could find it above in the `ppm/src` folder.
This `ppm lib` can read/write ppm format images only, and get the R-G-B values.
>To read more info about PPM Image you can click here -> [PPM](http://paulbourke.net/dataformats/ppm/)

Next, the project can make Images with the rgb values it got from loading, and can access at its pixels. In other words it can apply some filters we want, such as Linear, Blur, Gamma.

I personally use `Visual Studio` for my project.
>You can get Visual Studio from here -> [Visual Studio](https://visualstudio.microsoft.com/)

## **_Run the program_**
1. Download all code, and the Example Images folder.
2. Make a new Solution Project in Visual Studio.
3. Make a project which is gonna be a static lib, in your solution project, and name it ppm, and add `ppm\src` code.
4. Link your static lib with the main project.
5. Add the `src` code in your main project.
6. Build Project in Debug/Release Configuration.
7. Open Solution Folder, and open Debug Folder.
8. Open a new CMD inside and run `filterd.exe filter -f [your filter] [filter parameters] ... -f [your filter (n)] [filter (n) parameters] [name of the image]`.


>You can read the comments of the code, to understand how the program works.
