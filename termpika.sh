#!/bin/bash

# Function to check if ZSH is installed
is_zsh_installed() {
    command -v zsh >/dev/null 2>&1
}

# Function to install ZSH (if not installed)
install_zsh() {
    if ! is_zsh_installed; then
        sudo apt install zsh -y  # Adjust package manager and command for your system
    fi
}

# Function to switch to ZSH (if not the default shell)
switch_to_zsh() {
    if [[ "$SHELL" != "/bin/zsh" ]]; then
        chsh -s /bin/zsh "$USER"
    fi
}

# Function to clone the GitHub repository
clone_repo() {
    git clone "$1" "$2"
}

# Function to compile the C code and rename the executable
compile_and_rename() {
    cd "$1"
    gcc -o term terminalpika.c
}

# Function to move the executable to /usr/bin
move_executable() {
    mv "$1/term" "/usr/bin/term"
}

# Function to replace the zshrc file
replace_zshrc() {
    cp "$1/.zshrc" "$HOME/.zshrc"
}

# Main script logic
repo_url="https://github.com/q4n0/terminalpika.tree/main"
clone_dir="cloned_repo"

install_zsh
switch_to_zsh

clone_repo "$repo_url" "$clone_dir"
compile_and_rename "$clone_dir"
move_executable "$clone_dir"
replace_zshrc "$clone_dir"

# Optional: Source the updated zshrc file
source ~/.zshrc
