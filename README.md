BBB-Shell

BBB-Shell is a cross-platform terminal emulator with a graphical interface built on Qt. The project aims to simplify command-line interaction by combining familiar shell commands with a convenient visual text editor.

---

Key Features

- Support for standard shell commands such as echo, cd, ls, mkdir, rm, cat, touch — for easy file navigation and management.
- moduser command — basic user management and settings.
- Utility commands: pwd to display the current directory, whoami for the current user name, clear to clear the screen, and exit to quit the application.
- Graphical text editor bbb-nano — integrated directly into the shell. Requires an absolute file path to launch.
- Help command help — shows a list of available commands with brief descriptions.
- Dark theme and modern UI — comfortable to use even in low-light environments.

---

Technical Details

- The project is written in C++ using the Qt framework, providing cross-platform compatibility and flexible UI design.
- It uses an object-oriented approach with clear separation between command logic and the user interface.
- The built-in editor is based on QTextEdit with extended features for convenient file editing and saving.
- Command processing is done via a simple string parser, allowing easy expansion with custom commands and features.
- Special focus on stability and usability — a minimal set of commands helps users get started quickly without overwhelming them.

---

Getting Started

1. Clone the repository:
   git clone https://github.com/DanilaEfimov/BBB-Shell.git

2. Open the project in Qt Creator (recommended Qt version 6.7.2 or higher).

3. Build and run the application.

---

Usage

- Type help to see the list of available commands and brief descriptions.
- Use nano /absolute/path/to/file to open the graphical text editor.
- Execute other standard commands just like in a classic command line.

---

Contribution & Support

The project is open to improvements and suggestions. Feel free to send pull requests or open issues.

---

Thank you for using BBB-Shell!
