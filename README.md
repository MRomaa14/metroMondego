# Metro Mondego Management System 🚇

> A comprehensive C program for managing a metro transit system, featuring stops (paragens), lines (linhas), and intelligent route planning with automatic data persistence.

![C](https://img.shields.io/badge/C-99-blue?style=flat-square&logo=c)
![CMake](https://img.shields.io/badge/CMake-3.24+-green?style=flat-square&logo=cmake)
![Standard](https://img.shields.io/badge/Standard-C99-lightblue?style=flat-square)

## 🎯 Overview

**Metro Mondego Management System** is a C application developed as part of a programming course. It implements a complete metro transit management system featuring dynamic stop registration, line management, and intelligent route planning across a network of interconnected lines.

The system provides:
- **Dynamic stop management** with automatic code generation
- **Flexible line creation** through manual entry or file import
- **Intelligent route calculation** for single-line and transfer journeys
- **Persistent data storage** with automatic session recovery
- **User-friendly menu interface** for all operations

## Features

### 🛑 Stop Management (Paragens)
- **Register Stops**: Add new stops to the system with automatic alphanumeric code generation (4 characters)
- **Delete Stops**: Remove stops from the system (only if not assigned to any line)
- **View All Stops**: Display a complete list of all registered stops

### 🚊 Line Management (Linhas)
- **Add Lines**: Create new metro lines with associated stops
  - Input via manual entry or text file import
  - Validates that all stops are registered in the system
  - Prevents duplicate line names
- **Update Lines**: Modify stop sequences (add or remove stops)
- **View Lines**: 
  - Display all lines in the system
  - Filter lines by a specific stop

### 🗺️ Route Calculation (Percursos)
- **Single-Line Routes**: Find routes using only one metro line
- **Transfer Routes**: Find routes requiring a single line transfer
- Comprehensive path information displaying all intermediate stops

### 💾 Data Persistence
- Automatic saving of all stops and lines to binary files
- Data recovery on program startup
- Maintains system state between sessions

## 📦 Prerequisites

Before building the project, ensure you have:

- **C Compiler** supporting C99 standard (GCC, Clang, MSVC)
- **CMake** version 3.24 or higher
- **Make** (for Unix-like systems) or appropriate build tools for your OS

### Installation Instructions

#### Linux/macOS
```bash
# Install CMake
sudo apt-get install cmake  # Ubuntu/Debian
brew install cmake          # macOS

# Install build tools
sudo apt-get install build-essential  # Ubuntu/Debian
```

#### Windows
- Download and install [CMake](https://cmake.org/download/)
- Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) or MinGW
- Ensure both are added to your system PATH

## 🚀 Installation & Building

### Build Steps

#### Linux/macOS
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

#### Windows (with Visual Studio):
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Debug
```

#### Windows (with MinGW/GCC):
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. -G "Unix Makefiles"
make
```

### Running the Program

After building, execute the program:

**Linux/macOS:**
```bash
./TP_P
```

**Windows:**
```bash
TP_P.exe
```

## 🎮 Usage Guide

### Main Menu Navigation

The program presents an interactive menu system:

```
╔════════════════════════════════╗
║  Metro Mondego Management      ║
║  1. Routes (Percursos)         ║
║  2. Lines (Linhas)             ║
║  3. Stops (Paragens)           ║
║  4. Exit                       ║
╚════════════════════════════════╝
```

### Menu Operations

| Menu Item | Option | Description |
|-----------|--------|-------------|
| **Routes** | Single Line | Find routes on one line |
| | Transfer | Find routes with line changes |
| **Lines** | Add Line | Register new line |
| | Update Line | Modify line stops |
| | View All | Display all lines |
| | View by Stop | Show lines passing through a stop |
| **Stops** | Register | Add new stop |
| | Delete | Remove stop |
| | View All | Display all stops |

### Step-by-Step Examples

#### 📍 Adding a Stop

1. Select **Stops** from main menu
2. Choose **Register Stop**
3. Enter the stop name (e.g., "Parque da Cidade")
4. System auto-generates 4-character code

**Example:**
```
Enter stop name: Parque da Cidade
Stop registered successfully with code: P011
```

#### 🚇 Adding a Line (Manual Entry)

1. Select **Lines** → **Add Line** → **Manual Entry**
2. Enter line name (e.g., "Linha da Baixa")
3. For each stop, select from the registered stops list
4. Confirm to save

#### 📄 Importing a Line from File

1. Prepare a text file (see File Formats section)
2. Select **Lines** → **Add Line** → **Import from File**
3. Provide the file path
4. System validates all stops before importing

#### 🗺️ Finding Routes

**Single-Line Route:**
```
Menu: Routes → Single Line Route
Enter departure: Parque da Cidade
Enter arrival: Coimbra-B

Results:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Line: Linha da Baixa
Direction: Parque da Cidade → Coimbra-B
Path: Parque da Cidade → Portagem → Loja do Cidadão → Casa do Sal → Coimbra-B
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**Transfer Route:**
```
Menu: Routes → Route with Transfer
Enter departure: Stop A
Enter arrival: Stop D

Results:
First Line: Linha 1
Path: Stop A → Stop B → Stop C
Transfer at: Stop C
Second Line: Linha 2
Path: Stop C → Stop D
```

## 📋 File Formats

### Text File Format for Line Import

Lines can be imported from `.txt` files following this structure:

```
Linha da Baixa
Parque da Cidade # P011
Portagem # P123
Loja do Cidadao # Q998
Casa do Sal # F554
Coimbra-B # H123
```

**Format Specifications:**
- **Line 1**: Name of the metro line
- **Subsequent lines**: Stop name, separator `#`, and stop code
- **Separator**: The `#` character acts as delimiter (never appears in names/codes)
- **One stop per line**: Each stop must occupy exactly one line
- **Order matters**: Stops define the line direction

### Binary File Format

The program maintains state using binary files:

- **`paragem.bin`**: Serialized array of all registered stops
- **`linha.bin`**: Serialized linked list of all metro lines

Files are automatically created/updated on program exit and restored on startup.

## 🏗️ Architecture

### Key Components

The system is built around modular, single-responsibility components:

| Module | Purpose | Key Functions |
|--------|---------|----------------|
| **paragem.c** | Stop management | Register, delete, validate, search stops |
| **linha.c** | Line management | Add, update, traverse lines |
| **percurso.c** | Route algorithms | Find single/transfer routes |
| **menus.c** | User interface | Display menus, capture input |
| **ficheiros.c** | Persistence | Save/load binary files, parse text files |
| **utils.c** | Utilities | String handling, validation, helpers |

### Data Structures

**Stops (Dynamic Array)**
- Rationale: O(1) random access for quick stop lookup
- Efficient for relatively static data
- Easy sequential display
- Simpler code for adding/removing while maintaining order

**Lines (Linked List)**
- Rationale: O(1) insertion/deletion without shifting
- Efficient for frequent line additions/modifications
- Natural bidirectional traversal
- Clean pointer-based navigation

## ⚠️ Important Notes

- **Stop Codes**: Auto-generated (4-character alphanumeric) - users never specify them
- **Non-Circular Lines**: Each stop appears at most once per line
- **Unique Names**: System prevents duplicate stop/line names
- **Bidirectional Travel**: All lines can be traveled in both directions
- **Transfer Validation**: Only stops shared between lines enable transfers
- **Data Safety**: Binary files automatically created/updated on exit

## 🔧 Constraints & Limitations

- Single transfer routes only (multi-transfer not supported)
- Non-circular lines (each stop appears once per line)
- No time-based scheduling or frequency information
- No passenger capacity tracking
- No real-time updates

## 👥 Author

* **Miguel Roma** - [2025138654@my.ipleiria.pt](mailto:2025138654@my.ipleiria.pt)

---

## 📄 License

This project is licensed under the terms found in the `LICENSE` file.
