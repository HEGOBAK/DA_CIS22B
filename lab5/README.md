# Lab 5 Cargo Management System 🚀

## 📂 Project Structure

TO USE Makefile :
> ⚠️ **IMPORTANT:** Remember to **uncomment** the `main()` and `action()` functions at the **very bottom** of `jxchulab5.cpp`, and **comment out** the original `main()` and `action()` functions at the top to use the Makefile correctly.


🛠 Compilation & Execution
This project uses a Makefile to compile the C++ program and run test cases.

🔹 1. Compile the Program
To compile jxchulab5.cpp, run (on terminal in lab5/):

make

This generates an executable runTest

🔹 2. Run All Tests
To automatically run all test files inside testFile/, use (on terminal in lab5/):

make run-tests
This runs the program with each test file.
The output is saved in results.txt and displayed in the terminal.

🔹 3. Recompile Everything from Scratch
If you need a fresh compilation, use (on terminal in lab5/):

make re

This is equivalent to:

make clean
make

🔹 4. Clean Up Compiled Files
To delete the executable and test results, run (on terminal in lab5/):

make clean

📜 How to Run Manually
If you prefer to run the program manually for a specific test file, use:

./runTest testFile/valid_data.txt
Replace testFile/valid_data.txt with any other test file.

