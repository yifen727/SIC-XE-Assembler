# Simple Assembler Project

This project implements a simple assembler in C++, designed to convert assembly language into object code. The assembler reads an input assembly code file, processes it line by line, and generates the corresponding object program.

## OS and Environment

- **Operating System:** Windows (PowerShell)
- **Language:** C++

## Features

- Processes assembly code line by line.
- Handles different assembly instructions and generates location counters.
- Produces object code using base relative and PC relative addressing.
- Generates the object program with Head, Text, Modification, and End records.
- Outputs detailed location, symbol, and object code for each statement.

## Project Structure

### 1. **Assembler Structure:**

- **NODE struct:** 
  Contains information about each line in the assembly code, including:
  - `location`
  - `symbol`
  - `instruction`
  - `reference`
  - `objectcode`
  
- **assem[500]:** 
  An array of `NODE` structs to store all parsed lines from the assembly file.

### 2. **Main Workflow:**

- **Step 1:** 
  Reads the input assembly code file and splits each line by spaces. Depending on the number of words per line, it assigns them to `symbol`, `instruction`, and `reference` fields.
  
- **Step 2:** 
  Calculates the `location` for each instruction based on its opcode and updates the location counter.

- **Step 3:** 
  Generates the object code for each instruction, considering the opcode, symbol, and addressing mode (base relative or PC relative).

- **Step 4:** 
  Produces the final object program, which consists of:
  - **Head Record**
  - **Text Records** for each statement
  - **Modification Record**
  - **End Record**

- **Step 5:** 
  Outputs:
  - **`output.txt`**: Contains the location, source statement, and generated object code.
  - **`object_program.txt`**: Contains the final object program.

## How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yifen727/SIC-XE-Assembler
