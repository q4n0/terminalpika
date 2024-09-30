#Get tmux
sudo apt install tmux

# Install oh-my-zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Install Zsh syntax highlighting
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# Install Zsh autosuggestions
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

#Install fzf
sudo apt install fzf

# Edit your .zshrc file
nano ~/.zshrc

# Find the line that starts with 'plugins=' and modify it to include the new plugins:
plugins=(git zsh-syntax-highlighting zsh-autosuggestions)

# Save and exit the editor (Ctrl+X, then Y, then Enter in nano)

# Reload your .zshrc to apply changes
source ~/.zshrc
