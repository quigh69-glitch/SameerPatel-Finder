# Simple-Finder
File finder
# Simple Finder (SF)

High-speed file recovery and trace detection tool written in C++. 
Originally created to hunt down "Sameer Patel", but fully universal.

## Features
- **Blazing Fast:** Traverses C:\ in seconds.
- **Fuzzy Search:** Finds files even with typos (using Levenshtein distance).
- **Safe:** Gracefully skips system folders and permission errors.
- **Interactive:** Choose a file number to reveal it in Windows Explorer.

## How to use
1. Open `main.cpp`.
2. Edit `target` to search for your string.
3. Edit `root` to specify the drive or folder.
4. Compile in **Release x64** mode.
