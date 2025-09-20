# Bumblestack VM

Bumblestack VM is a modular, C-based virtual machine and reasoning engine, designed for experimentation with symbolic AI, NARS (Non-Axiomatic Reasoning System), and related cognitive architectures. **This project is a fork of [ONA (OpenNARS for Applications)](https://github.com/opennars/ONA) and incorporates code and ideas from ONA 0.8.7, as well as other open-source projects.**

The project includes a core C implementation, a Python interface, and a collection of scripts and utilities for building, testing, and extending the system. See the Libs and Credits section for full attributions.


## Table of Contents

- [Project Structure](#project-structure)
- [Building and Running](#building-and-running)
- [Notable Features](#notable-features)
- [Branches and Experiments](#branches-and-experiments)
- [Libs and Credits](#libs-and-credits)


## Project Structure

- `src/c/` — Core C source code for the VM, NARS logic, and supporting libraries
- `src/python/` — Python interface and parser (Lark grammar, Python bindings)
- `src/bash/` — Shell scripts for build and library management
- `src/nal/` — Example NARSese input files
- `src/c/generate_ruletable/` — Tools for generating rule tables
- `src/c/test/` — Unit tests (using Unity framework)


## Building and Running

**Requirements:**
- C compiler (e.g., gcc or clang)
- CMake (if using CMakeLists.txt)
- Python 3.x (for Python interface)

**To build the C code:**
```sh
cd /Users/seamus/Repos/bumblestack_vm
mkdir build && cd build
cmake ..
make
```

**To run unit tests:**
```sh
cd src/c/test
gcc -I../ unity/unity.c unit_tests.c -o unit_tests
./unit_tests
```

**To use the Python interface:**
```sh
cd src/python
python3 -m parser.py <input_file>
```


## Notable Features

- Modular C codebase for symbolic reasoning
- NARS/NARSese support
- Python parser and interface
- Unit tests with Unity
- Example NARSese files for experimentation


## Branches and Experiments

Here is a list of branches in the `seamus-brady/bumblestack_vm` repository, along with summaries of what each branch was attempting to do:

- **add-cli-handlers**  
	*Work on JavaScript operations for CLI handlers.*  
	[Working js ops!!!](https://github.com/seamus-brady/bumblestack_vm/commit/2f956574b9015590cf8a54b5e6aba624beca49f2)

- **add-new-slog-types**  
	*Summary unavailable from commit messages.*

- **add-repl**  
	*Addition and development of a REPL (Read-Eval-Print Loop) feature.*  
	[Added repl](https://github.com/seamus-brady/bumblestack_vm/commit/01458ba6e484c9f7c4d201de1fb3694b8772da60)  
	[Almost working repl](https://github.com/seamus-brady/bumblestack_vm/commit/6e7786b313a5d7d01fae632daa504799b49c3a35)


- **improve-wasm-build**  
	*Work to improve the WebAssembly build and add diagnostics.*  
	[Added wasm build and diagnostics](https://github.com/seamus-brady/bumblestack_vm/commit/32496bb90e343966fa01a65be75b731a16c64491)  
	[Fixed wasm issues](https://github.com/seamus-brady/bumblestack_vm/commit/54b58d9db0dbb33cae6f99c34f0f9a6560293a1f)


- **json**  
	*Attempting to add or improve JSON output and parsing.*  
	[Added json output](https://github.com/seamus-brady/bumblestack_vm/commit/7d244e042bd73884d044a0b4b3d369d3cb9a58be)

- **luajit**  
	*LuaJIT related experimentation.*  
	[Removed luajit](https://github.com/seamus-brady/bumblestack_vm/commit/9ad7c7b5ea023a80fc9b3f61451ca928d5b5b984)


- **s7-test**  
	*Experiments or integration work related to the s7 Scheme interpreter.*

- **shared_lib**  
	*Summary unavailable from commit messages.*  
	[View commit history](https://github.com/seamus-brady/bumblestack_vm/commits?sha=shared_lib&sort=updated)

- **wasm-build**  
	*Efforts related to building with WebAssembly.*  
	[View commit history](https://github.com/seamus-brady/bumblestack_vm/commits?sha=wasm-build)

- **wren-embed**  
	*Embedding the Wren VM; adding Wren scripting support.*

- **wren-embed-2**  
	*Additional or alternative work embedding the Wren VM.*  
	[Added wren vm](https://github.com/seamus-brady/bumblestack_vm/commit/310e00bcb33f1358ab8618417225c4e2509501b7)


For a full commit history on any branch, visit the [repository branches page](https://github.com/seamus-brady/bumblestack_vm/branches).


## Libs and Credits

- **ONA 0.8.7** — [OpenNARS for Applications](https://github.com/opennars/ONA) (c) 2020 The OpenNARS authors
- **Wren** — Copyright (c) 2013-2021 Robert Nystrom and Wren Contributors
- **JSON-Wren** — Copyright (c) 2015 Matthew Brandly
- **SLog** — Copyleft (C) 2015-2020 Sun Dro

For more information, see the source code and comments throughout the project. Contributions and experiments are welcome!
