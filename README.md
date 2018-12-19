# P1: Pakkelevering
## Traveling Salesman Problem
P1: Pakkelevering is a program written in C that can find the shortest route inbetween a series of addresses within the city of Aalborg.
As this program uses the Held-Karp algorithm, the ram usages will grow exponentially as more addresses are used, with 27 addresses taking around 15 GB of RAM, therefore, use at own risk. We recommend using at most 25 addresses on most computers.

## Prerequisites
### Windows
* [MinGW](http://www.mingw.org/) with CMake installed
* Git

### Linux
* CMake
* Git

## Installation
### Linux
Clone the repository:
```
git clone https://github.com/hooolius/p1_pakkelevering.git
```
Navigate to the build directory:

```
cd p1_pakkelevering/src/build
```
Generate makefiles:

```
cmake -G "Unix Makefiles" ..
```
Install to a location:
```
sudo make DESTDIR=/path/to/location install 
```
Or to your bin directory:
```
sudo make install
```

### Windows:
Clone the repository:
```
git clone https://github.com/hooolius/p1_pakkelevering.git
```
Navigate to the build directory:

```
cd p1_pakkelevering/src/build
```
Open MinGW as administrator in src/build

Generate makefiles:

```
cmake ..
```
Install to Program Files (x86):
```
make install 
```

## Usage
### Linux:
To use a specific input file:

```
p1_pakkelevering <input file>
```

Or simply

```
p1_pakkelevering
```
Then input addresses at the prompt.

#### Example:

```
p1_pakkelevering test_file.txt
```

This will make **p1_pakkelevering** calculate the optimal tour from the addresses within **test_file.txt**

## License

[MIT](https://choosealicense.com/licenses/mit/)
