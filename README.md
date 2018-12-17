# P1: Pakkelevering
## Traveling salesman

P1: Pakkelevering is a program written in C that can find the shortest route inbetween a series of nodes (Up to 20 addresses depending on your RAM and limited to the city of Aalborg).
As this programs is trying to calculate a pn the ram usages from the combinatorial algorithm will grow exponentially, with 27 addresses taking around 15 gb of ram, no matter the pc, therefor, use at own risk.

## Installation

### Linux:

Navigate to build directory.

Run Cmake command:

```
Cmake build
```

**build** being the directory in which the Cmake files lies.

Run 

```
sudo make install p1_pakkelevering
```



### Windows:

????????????


## Usage
### Linux:

After this run the file with the wanted parameter, any file written after will be taken as the input file for the addresses you want to search for.

#### Example:

```
p1_pakkelevering <filename.txt>
```

This will make **p1_pakkelevering** calculate the plan from the addresses within **filename.txt**







## License

[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
