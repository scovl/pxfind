# pxfind

`pxfind` is a simple command-line utility written in C that searches for a specific pixel color within a defined screen area. 

## Features

- Searches for a specific color within a specified area of the screen.
- Allows for color variation in the search.
- Returns the coordinates of the found pixel.

## Requirements

- GCC (GNU Compiler Collection)
- Windows OS (for GDI functions)

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/scovl/pxfind.git
    cd pxfind
    ```

2. Compile the program using GNU Make:
    ```bash
    make
    ```

## Usage

Run the compiled executable:
```bash
./pxfind
```