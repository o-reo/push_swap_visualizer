# Push Swap Visualizer
This project is a visualizer for the **"PUSH_SWAP"** 42 School Project.

**Push Swap** is a program that takes as argument a space separated list of numbers and outputs a list of commands that can be used to sort them.

You can read the subject [here](https://github.com/Binary-Hackers/42_Subjects/blob/master/00_Projects/02_Algorithmic/push_swap.pdf).

## Usage
- In the **Values** window
    - Choose the size of the push swap input with the slider [Optional]
    - **Shuffle** the input [Optional]
    - The space separated values should be filled automatically, you can also put your own values
    - Set the Push Swap program path (Absolute or relative path).
    - **Compute** the sort commands, it will display OK when done.
- In the **Controls** window
    - **Load** the commands in the visualizer
    - **Start** the animation
    - Adjust the **Speed** as needed
    - **Pause** and go **Step** by step to see the details of your algorithm.
    - **Load** to restart the animation

## Install
This project uses C++17, cmake, SFML and ImGui.
- Install a C++ compiler (gcc, clang,...)
- Install cmake
- Move push_swap_visualizer inside push_swap
- Inside push_swap_visualizer, mkdir :
    - 'build'
- cd in the build folder and type :
    - 'cmake  ..'
    - 'make'
- run the visualizer with ./bin/visualizer

![](https://i.imgur.com/zqcsZfY.png)
