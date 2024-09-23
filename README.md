# UAC Bypass Tool

**A tool to bypass User Account Control (UAC) using registry manipulation and `fodhelper.exe`.**

This tool takes advantage of a known UAC bypass technique by modifying the Windows registry and then launching `fodhelper.exe` to execute commands or files with elevated privileges.

## Features:
- **Registry Manipulation**: The tool modifies the registry key `HKEY_CURRENT_USER\Software\Classes\ms-settings\Shell\Open\command` to set a custom command or executable.
- **Bypass UAC**: It sets the `DelegateExecute` value to an empty string, allowing the bypass of UAC prompts.
- **Elevated Execution**: After the registry changes, the tool starts `fodhelper.exe`, which triggers the execution of the provided command or executable with elevated privileges.
- **Error Handling**: Provides basic error handling for registry operations and process creation.

## Usage:
```bash
UacBypass.exe <file.exe or command>
