# SimpleFileCommand

SimpleFileCommand is a command-line utility written in C++ that serves as a clone of the popular Midnight Commander file manager. It is designed to provide a text-based file management experience with a simple interface. The program uses the `ncurses` library to create an interactive terminal interface.

## Features

- Copy files: Press `5` to copy a selected file.
- Move files: Press `6` to move a selected file.
- Create a new directory: Press `7` to create a new directory.
- Create a new file: Press `8` to create a new file.
- Create a new symbolic link: Press `9` to create a new symbolic link.
- Delete files: Press `d` to delete selected files.
- Regular Expression support: Press `r` to enter a regular expression, and then choose whether to copy, delete, or move selected files based on the provided pattern.
- `q` to quit

## Getting Started

To build SimpleFileCommand, follow these steps:

1. Clone this repository to your local machine:

```bash
git clone https://github.com/yourusername/simplefilecommand.git
```

2. Navigate to the project directory:

```bash
cd simplefilecommand
```

3. Build the project using make:

```bash
make
```

4. Run SimpleFileCommand:

```bash
./simplefilecommand
```

### Acknowledgment

I do not take any responsibility for damage that can be done by using this software.
This application is capable of deleting files, links, directories(regardles of emptiness). 


### Usage

Using keys:
- 5 = copy active file to inactive directory;
- 6 = move active file to inactive directory;
- 7 = create directory in active directory, input is required afterwards(name);
- 8 = create regular file in active directory, input is required afterwards(name);
- 9 = create link in active directory, input is required afterwards(name, target);
- d = delete active file in active directory;
- r = regex, input is required afterwards(regular expression, action(copy, move, delete));
- q = exit;
