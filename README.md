```
 $$$$$$\                                $$\      $$\                     
$$  __$$\                               $$ | $\  $$ |                    
$$ /  \__| $$$$$$\   $$$$$$\   $$$$$$\  $$ |$$$\ $$ | $$$$$$\   $$$$$$\  
$$ |      $$  __$$\ $$  __$$\ $$  __$$\ $$ $$ $$\$$ | \____$$\ $$  __$$\ 
$$ |      $$ /  $$ |$$ |  \__|$$$$$$$$ |$$$$  _$$$$ | $$$$$$$ |$$ |  \__|
$$ |  $$\ $$ |  $$ |$$ |      $$   ____|$$$  / \$$$ |$$  __$$ |$$ |      
\$$$$$$  |\$$$$$$  |$$ |      \$$$$$$$\ $$  /   \$$ |\$$$$$$$ |$$ |      
 \______/  \______/ \__|       \_______|\__/     \__| \_______|\__|      
```
Grade : A🎖️ | Mark : 22/22 | Keynote : 4 444/4 444

* [Description](#description)
* [Prerequisites](#prerequisites)
* [Installation](#installation)


## Description

The Corewar project is a game in which several programs called "Champions" will fight to vecome the last one standing. Corewar is actually a computer simulation in which processors will share memory to run on. The project is based on a virtual machine in which the champions manipulate the machine's memory through several operations in order to win, the winner being the last champion able to signal that he is alive (i.e execute a "live" instruction").

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See [**program usage**](#program-usage) for notes on how to use the project after having it installed.

### Prerequisites

* `gcc`
* `make`
* `ncurses`

#### Fedora:
```
sudo dnf install make gcc ncurses-devel
```

#### Ubuntu / Debian:
```
sudo apt-get install gcc make libncurses5-dev libncursesw5-dev
```

#### Arch:
```
sudo pacman -S install gcc make libncurses5-dev libncursesw5-dev
```
#### MacOs:
```
brew install gcc make ncurses
```

### Installation

First, clone this repository and go into it :

```
git clone https://github.com/AdrienL06/corewar && cd corewar/
```

Compile the project: 

```
make
```

It will compile the three part of this project : our library containing some useful functions used throughout the project, the assembly part and the virtual machine part. If you want to use the visualiser, just run the `make` command in the `bonus` folder.

See the documentation :

```
make doxygen
```

## Program usage

Assembly part :
```
USAGE
    ./asm file_name[.s]
DESCRIPTION
    file_name file in assembly language to be converted into file_name.cor, an executable in the Virtual Machine.

For exemple :
    ./asm/asm champion1.s
```

Virtual machine part :
```
USAGE
    ./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...

DESCRIPTION
    -dump nbr_cycle dumps the memory after the nbr_cycle execution (if the round isn’t already over) with the following format: 32 bytes/line in hexadecimal (A0BCDEFE1DD3...)

    -n prog_number sets the next program’s number. By default, the first free number in the parameter order

    -a load_address sets the next program’s loading address. When no address is specified, optimize the addresses so that the processes are as far away from each other as possible. The addresses are MEM_SIZE modulo
```

So here's an exemple of the program or the visualizer without using any flag:
```sh
# First assembly part to obtain your .cor
❯ ./asm/asm champion1.s

# Then the corewar part to launch the virtual machine
❯ ./corewar/corewar champion1.cor champion2.cor champion3.cor champion4.cor

# To use the visualizer, just go into the bonus folder :
❯ ./visualizer champion1.cor champion2.cor champion3.cor champion4.cor
``` 

## Running the tests

We did some functionals tests (not unit-test as we didn't have enough time) using criterion :

```sh
# Run criterion through make :
❯ make tests_run

# Open a browser html page to look at the coverage of the tests with a graphique interface using gcovr :
❯ make gcovr

# And to reload the html page :
❯ gcovr-reload
```

## Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language)) - Main language used
* [Ncurses](https://en.wikipedia.org/wiki/Ncurses) - Library used to built bonus
* [Doxygen](https://www.doxygen.nl/) - Used to generate the documentation in a website form.

## Authors

* **Adrien Lachambre** - *assembler & documentation* - [AdrienL06](https://github.com/AdrienL06)
* **Enzo Maltese** - *virtual machine* - [EnzoMaltese](https://github.com/EnzoMaltese)
* **Micka Daoud** - *virtual machine* - [Micka-Daoud](https://github.com/Micka-DAOUD)
* **Virgile Legros** - *assembler & virtual machine* - [Virgile-Legros](https://github.com/Virgile-Legros)
