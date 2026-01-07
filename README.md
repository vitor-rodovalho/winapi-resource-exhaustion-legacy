# WinAPI Resource Exhaustion (Legacy Project)

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Area](https://img.shields.io/badge/Area-Operating%20Systems-white.svg)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> **⚠️ WARNING: EDUCATIONAL & EXPERIMENTAL USE ONLY** > This program acts as a "stress test" or "prankware". It creates a fork-bomb-like effect by rapidly opening browser tabs and Windows Explorer instances until the system RAM is depleted, followed by a forced reboot.  
> **DO NOT RUN this on a machine with unsaved work.**



## 📜 About

This project was developed during my **first semester of Computer Science**. The goal was to explore the C language and the Windows API (`windows.h`) to interact with the operating system, manage processes, and monitor system resources.

It serves as a legacy artifact of my early learning process regarding:
- Native Windows API calls.
- Memory management concepts (monitoring available RAM).
- System calls and process spawning.



## ⚙️ How It Works

1. **User Identification:** Retrieves and displays the current Windows username.
2. **Disclaimer:** Forces the user to read a disclaimer (via Notepad) before proceeding.
3. **Resource Consumption:**
   - Monitors available RAM using `GlobalMemoryStatusEx`.
   - While free RAM is above the critical threshold (20MB), it loops through random actions:
     - Opens web browser tabs (including a classic "Rick Roll").
     - Opens system folders (Documents, Images, System32).
4. **Shutdown:** Once the memory threshold is reached, the system initiates a forced restart (`shutdown /r`).



## 🛠️ Technical Details

- **Language:** C
- **Platform:** Windows (Win32 API)
- **Key Libraries:** `<windows.h>`, `<shlobj.h>`
- **Logic:** The program uses a polling loop to check memory status and `ShellExecuteA` / `system()` commands to spawn processes.



## 🚀 How to Compile & Run

**Prerequisites:** MinGW or any C compiler for Windows.

1. Clone the repository:
    ```bash
    git clone https://github.com/vitor-rodovalho/winapi-resource-exhaustion-legacy.git
    ```

2. Compile the code:
    ```bash
    gcc system_exhaustion.c -o stress_test.exe
    ```

3. Run (at your own risk):
    ```bash
    ./stress_test.exe
    ```



## ⚖️ Disclaimer

This software is provided "as is", without warranty of any kind. The author is not responsible for any system instability, data loss, or hardware issues resulting from the execution of this code. This project is intended solely for the study of operating system behavior under stress.


---

## ⚠️ Language Note

Please note that the code comments are currently in **Portuguese**, as this project was originally developed for a university assignment.

## 📄 Author

Developed by **Vitor Hugo Rodovalho**.

---

**License**: MIT License
