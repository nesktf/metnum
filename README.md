# metnum
Excercises with numerical methods in C++17 that I did for some college assignments

All methods were taken from the book "Métodos numéricos para ingenieros - Quinta Edición" by
Steven C. Chapra & Raymond P. Canale

The excercises where probably taken from there too, i didn't check lmao

## Building
Tested on Debian 12 Bookworm and Arch Linux. You will need the following dependencies:

```sh
$ sudo apt install libarmadillo-dev liblaplack-dev libopenblas-dev
```
You will also need gnuplot if you want to plot the ODEs (uncomment the PLOT_THINGS define)

Then build and execute the project by doing the following:

```sh
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ make -C build -j4
$ ./build/metnum
```

## Links
- [armadillo](https://arma.sourceforge.net/) 
- [gnuplot-cpp](https://github.com/martinruenz/gnuplot-cpp) 
