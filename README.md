# corewar
CoreWar is a C pet-project from 42 course written in order to know more about
assembler, memory rules and to reproduce old memory-based game named "Core War".

## Installation
```bash
make
```

## Usage
```bash
Usage: ./corewar [-dump N | -dump64 N] [-d | -dc | -dr | -df [-e N] | -v [s N]] [-a] <[-n N] champion.cor> <...>
********************* PROGRAMM FLAGS *********************************
| -a            : Prints output from 'aff' (default is to hide it)   |
| -n N <*.cor>  : Sets champion number (from 1) for <champion.cor>   |
********************* TEXT OUTPUT MODE *******************************
| -dump N       : Dumps memory by 32 octets after N cycles then exit |
| -dump64 N     : Dumps memory by 64 octets after N cycles then exit |
********************* DEBUG OUTPUT MODE ******************************
| -d            : Debug mode                                         |
| -dc           : Debug mode with cycles                             |
| -dr           : Debug mode with car death                          |
| -df           : Debug mode with dc and dr modifications            |
| -e N          : Sets end cycle for output                          |
********************* VISUAL OUTPUT MODE *****************************
| -v            : Visual (by Ncurses) output mode                    |
********************* OUTPUT FLAGS ***********************************
| -s N          : Sets start cycle for output                        |
**********************************************************************
```
