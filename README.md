# Push Swap Visualizer

This project is a visualizer for the **"PUSH_SWAP"** 42 School Project.

**Push Swap** is a program that takes as argument a space separated list of numbers and outputs a list of commands that can be used to sort them.

You can read the subject [here](https://github.com/Binary-Hackers/42_Subjects/blob/master/00_Projects/02_Algorithmic/push_swap.pdf).

## Install

- Clone the `push_swap_visualizer` repository into the directory where your `push_swap` project is located:

```bash
git clone https://github.com/o-reo/push_swap_visualizer.git
```

This project uses C++17, cmake, SFML and ImGui.

---

## Debian-based package installation :
- Install required packages (if not already installed) using the following command :

```bash
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install g++
sudo apt-get install clang
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install libx11-dev libxrandr-dev
sudo apt-get install libudev-dev
sudo apt-get install libfreetype-dev
```

## macOS package installation (Intel-chip and Apple Silicon-chip) :
- Install HomeBrew Package Manager (if not already installed).
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
- Install required packages (if not already installed) using the following command :

```bash
brew update
brew install cmake
brew install gcc
brew install llvm
brew install mesa
brew install xquartz
brew install freetype
```
> [!IMPORTANT]
>  Please note that `libudev-dev` has no direct equivalent on macOS. Depending on your specific needs, you might be able to use other libraries or APIs available on macOS.
> 
> For example, `IOKit` is a macOS framework for handling hardware resources, which might be used as an alternative for some `libudev` functionalities.
> However, the usage and capabilities will not be the same, and you'll need to adjust your code accordingly.
>
> Also, `libx11-dev` and `libxrandr-dev` are replaced with `xquartz` on macOS, which provides the X11 server for macOS. But again, the functionality might not be exactly the same as on Linux.

---

- Navigate to the `push_swap_visualizer` directory, create `build` directory, and navigate into the build directory:

```bash
cd push_swap_visualizer
mkdir build
cd build
```

- Generate the build files using CMake and compile the visualizer:

```bash
cmake ..
make
```

- Run the visualizer:

```bash
./bin/visualizer
```

## Usage

- If you've relocated your push_swap program, simply update the visualizer's menu directory from "../../push_swap" to the new path of your push_swap program. For instance, "../../new_directory/push_swap".

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

![](https://i.imgur.com/zqcsZfY.png)
