#!/bin/bash

# Function to check if ZSH is installed
is_zsh_installed() {
    command -v zsh >/dev/null 2>&1
}

# Function to install ZSH (if not installed)
install_zsh() {
    if ! is_zsh_installed; then
        echo -n "Installing ZSH..."
        (sudo apt install zsh -y >/dev/null 2>&1) & spinner
    fi
}

# Function to switch to ZSH (if not the default shell)
switch_to_zsh() {
    if [[ "$SHELL" != "/bin/zsh" ]]; then
        echo -n "Switching to ZSH..."
        (chsh -s /bin/zsh "$USER" >/dev/null 2>&1) & spinner
    fi
}

# Function to clone the GitHub repository
clone_repo() {
    echo -n "Cloning repository..."
    (git clone "$1" "$2" >/dev/null 2>&1) & spinner
}

# Function to compile the C code and rename the executable
compile_and_rename() {
    echo -n "Compiling C code..."
    (cd "$1" && gcc -o term terminalpika.c >/dev/null 2>&1) & spinner
}

# Function to move the executable to /usr/bin
move_executable() {
    echo -n "Moving executable to /usr/bin..."
    (sudo mv "$1/term" "/usr/bin/term" >/dev/null 2>&1) & spinner
}

# Function to replace the zshrc file
replace_zshrc() {
    echo -n "Replacing .zshrc..."
    [ -f "$HOME/.zshrc" ] && cp "$HOME/.zshrc" "$HOME/.zshrc.bak"
    (cp "$1/.zshrc" "$HOME/.zshrc" >/dev/null 2>&1) & spinner
}

# Spinner function to show progress
spinner() {
    local pid=$!
    local delay=0.1
    local spinstr='|/-\'
    while ps -p $pid >/dev/null 2>&1; do
        for s in $spinstr; do
            echo -ne "\b$s"
            sleep $delay
        done
    done
    echo -ne "\b Done!\n"
}

# Main script logic
repo_url="https://github.com/q4n0/terminalpika.git"
clone_dir="cloned_repo"

install_zsh
switch_to_zsh

clone_repo "$repo_url" "$clone_dir"
compile_and_rename "$clone_dir"
move_executable "$clone_dir"
replace_zshrc "$clone_dir"

# Optional: Source the updated zshrc file
echo -n "Sourcing .zshrc..."
(source ~/.zshrc >/dev/null 2>&1) & spinner

echo "Setup complete."
