#!/bin/bash

echo "ZSH modifier by b0urn3 (Chris). Enjoy!"

# Exit if any command fails
set -e

# Check if the script is running as root
if [ "$EUID" -ne 0 ]; then
  echo "This script requires root privileges. Please run it with 'sudo'. Thanks."
  exit 1
fi

# Install important packages
echo "Installing necessary packages..."
if apt install -y curl wget gcc tmux fzf > /dev/null; then
  echo "Packages installed successfully."
else
  echo "Failed to install necessary packages."
  exit 1
fi

# Get terminal pika C banner
echo "Downloading terminalpika C source..."
if wget -q https://raw.githubusercontent.com/q4n0/terminalpika/main/termpika.c -P $HOME; then
  echo "Downloaded terminalpika C source."
else
  echo "Failed to download terminalpika C source."
  exit 1
fi

# Compile to /usr/bin directory for system-wide execution
echo "Compiling terminalpika..."
if gcc -o /usr/bin/term $HOME/termpika.c; then
  echo "Compiled terminalpika successfully."
else
  echo "Failed to compile terminalpika."
  exit 1
fi

# Optional: Clean up the source file after compiling
rm $HOME/termpika.c

# Get .zshrc config file into your system
echo "Downloading .zshrc configuration..."
if wget -q https://raw.githubusercontent.com/q4n0/terminalpika/main/.zshrc -O ~/.zshrc; then
  echo "Downloaded .zshrc configuration."
else
  echo "Failed to download .zshrc configuration."
  exit 1
fi

# Install Oh My Zsh if not already installed
if [ ! -d "$HOME/.oh-my-zsh" ]; then
  echo "Installing Oh My Zsh..."
  if sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"; then
    echo "Oh My Zsh installed successfully."
  else
    echo "Failed to install Oh My Zsh."
    exit 1
  fi
else
  echo "Oh My Zsh is already installed."
fi

# Install Zsh syntax highlighting if not already cloned
if [ ! -d "${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting" ]; then
  echo "Cloning Zsh syntax highlighting plugin..."
  if git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting; then
    echo "Zsh syntax highlighting plugin cloned successfully."
  else
    echo "Failed to clone Zsh syntax highlighting plugin."
    exit 1
  fi
fi

# Install Zsh autosuggestions if not already cloned
if [ ! -d "${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions" ]; then
  echo "Cloning Zsh autosuggestions plugin..."
  if git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions; then
    echo "Zsh autosuggestions plugin cloned successfully."
  else
    echo "Failed to clone Zsh autosuggestions plugin."
    exit 1
  fi
fi

# Reload your .zshrc to apply changes
echo "Reloading .zshrc..."
if source ~/.zshrc; then
  echo ".zshrc reloaded successfully."
else
  echo "Failed to reload .zshrc."
  exit 1
fi

echo "Setup complete! Enjoy your new terminal experience."
