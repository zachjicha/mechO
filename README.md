# mechanical Orchestra

One of the successors to Stepper-Music. This version is made in C and is designed to run on Raspberry Pi Zero, but should work on any Pi. The other successor (coming soon) is preferred to this one, but requires arduino. This works with only pi, but can occasionaly stutter, possibly due to the OS running on the pi.

**Installation:**  
1. Make sure cmake and make are installed on your pi  
2. Install [wiringPi](http://wiringpi.com/download-and-install/) on your pi  
3. As per [this Stack Overflow thread](https://stackoverflow.com/questions/30424236/add-wiringpi-lib-to-cmake-on-raspberrypi), create a file FindWiringPi.cmake with the following text:  
```
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
```  
4. Move FindWiringPi.cmake to the directory /usr/share/cmake-y.x/Modules where y.x is your cmake version  
5. Download or clone mechO onto your pi  
6. CD into the mechO directory  
7. Change any pin configs you need to using the wiringpi pins on the diagram on [this page](http://wiringpi.com/pins/)  
8. Enter the follwoing commands:  
```
cmake .
make
```
mechO will now be compiled and ready for use!  

**Usage:**  
`./mechO <filename>.mid` will run \<filename\>.mid on the motors given you have the same amount of motors as tracks  
`./mechO <filename>.mid <time>` is the same as above, but will wait \<time\> milliseconds before running
