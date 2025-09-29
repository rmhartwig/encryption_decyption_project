# Copilot Instructions for This Codebase

## Project Overview
This is a simple C++ command-line application implementing a custom cipher for encrypting and decrypting messages. The main logic is in `main.cpp`.

## Architecture & Key Files
- `main.cpp`: Contains the entire application logic, including:
  - User interaction loop (menu for encrypt/decrypt/exit)
  - `encrypt` and `decrypt` functions using a custom polynomial-based transformation
- No additional source or header files; all logic is in a single file.

## Encryption/Decryption Details
- **Encryption**: Each character is transformed using `y = 46(x + key)^3 + 1`, where `x` is the character code and `key` is user-supplied.
- **Decryption**: Inverts the above transformation using cube root and key subtraction.
- All characters (not just letters) are encrypted.
- Encrypted output is shown as space-separated uppercase hexadecimal numbers.

## Developer Workflows
- **Build**: Use the VS Code build task: `C/C++: g++.exe build active file` (Ctrl+Shift+B by default)
- **Run**: Execute the resulting `main.exe` in the terminal.
- **Debug**: Use VS Code's C++ debugging tools (launch.json if present, or F5 for default config).
- **No tests**: There are no automated tests or test framework present.

## Project Conventions
- All code is in `main.cpp`.
- Uses standard C++ libraries only; no external dependencies.
- User input is handled via `cin`/`getline`.
- Hexadecimal output uses `std::hex` and `std::uppercase`.
- Key must be an integer in the range (0, 100,000).

## Example Usage
- To encrypt: Enter a message and a key when prompted; output will be hex values.
- To decrypt: Paste hex values and enter the key; output will be the original message.

## Extending the Project
- For new features, add functions to `main.cpp`.
- If splitting into multiple files, update build instructions accordingly.

---
For more details, see `main.cpp`.
