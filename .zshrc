#~/.zshrc file for zsh interactive shells.

# Enable features and set options
setopt autocd              # change directory just by typing its name
setopt interactivecomments # allow comments in interactive mode
setopt magicequalsubst     # enable filename expansion for arguments of the form ‘anything=expression’
setopt nonomatch           # hide error message if there is no match for the pattern
setopt notify              # report the status of background jobs immediately
setopt numericglobsort     # sort filenames numerically when it makes sense
setopt promptsubst         # enable command substitution in prompt
WORDCHARS=${WORDCHARS//\/} # Don't consider certain characters part of the word

# hide EOL sign ('%')
PROMPT_EOL_MARK=""

# Configure key bindings
bindkey -e                                        # emacs key bindings
bindkey ' ' magic-space                           # do history expansion on space
bindkey '^U' backward-kill-line                   # ctrl + U
bindkey '^[[3;5~' kill-word                       # ctrl + Supr
bindkey '^[[3~' delete-char                       # delete
bindkey '^[[1;5C' forward-word                    # ctrl + ->
bindkey '^[[1;5D' backward-word                   # ctrl + <-
bindkey '^[[5~' beginning-of-buffer-or-history    # page up
bindkey '^[[6~' end-of-buffer-or-history          # page down
bindkey '^[[H' beginning-of-line                  # home
bindkey '^[[F' end-of-line                        # end
bindkey '^[[Z' undo                               # shift + tab undo last action

# Enable completion features
autoload -Uz compinit
compinit -d ~/.cache/zcompdump
zstyle ':completion:*:*:*:*:*' menu select
zstyle ':completion:*' auto-description 'specify: %d'
zstyle ':completion:*' completer _expand _complete
zstyle ':completion:*' format 'Completing %d'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' list-colors ''
zstyle ':completion:*' list-prompt %SAt %p: Hit TAB for more, or the character to insert%s
zstyle ':completion:*' matcher-list 'm:{a-zA-Z}={A-Za-z}'
zstyle ':completion:*' rehash true
zstyle ':completion:*' select-prompt %SScrolling active: current selection at %p%s
zstyle ':completion:*' use-compctl false
zstyle ':completion:*' verbose true
zstyle ':completion:*:kill:*' command 'ps -u $USER -o pid,%cpu,tty,cputime,cmd'

# History configurations
HISTFILE=~/.zsh_history
HISTSIZE=1000
SAVEHIST=2000
setopt hist_expire_dups_first # delete duplicates first when HISTFILE size exceeds HISTSIZE
setopt hist_ignore_dups       # ignore duplicated commands history list
setopt hist_ignore_space      # ignore commands that start with space
setopt hist_verify            # show command with history expansion to user before running it

# Force zsh to show the complete history
alias history="history 0"

# Configure time format
TIMEFMT=$'\nreal\t%E\nuser\t%U\nsys\t%S\ncpu\t%P'

# Set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# Set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# Enable colored prompt if terminal has the capability
force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
        color_prompt=yes
    else
        color_prompt=
    fi
fi

# Configure custom prompt with green and blue or purple and red combination
# Configure custom prompt with grey and blue combination and specific design
# Configure custom prompt with grey and blue combination and refined design
# Configure custom prompt with dimmed colors
# Configure custom prompt with dimmed colors
configure_prompt() {
    prompt_symbol=𓆲 # Default prompt symbol
    case "$PROMPT_ALTERNATIVE" in
        twoline)
            PROMPT=$'%F{240}┌──%F{67}%n'$prompt_symbol$'%m%F{240}-[%F{178}%~%F{240}]\n>> %f'
            ;;
        oneline)
            PROMPT=$'%F{240}┌──%F{67}%n'$prompt_symbol$'%m%F{240}-[%F{178}%~%F{240}] >> %f'
            RPROMPT=
            ;;
        backtrack)
            PROMPT=$'%F{240}┌──%F{67}%n'$prompt_symbol$'%m%F{240}-[%F{178}%~%F{240}] >> %f'
            RPROMPT=
            ;;
    esac
    unset prompt_symbol
}
# Kali config variables (do not modify)
PROMPT_ALTERNATIVE='twoline'
NEWLINE_BEFORE_PROMPT='no'

if [ "$color_prompt" = yes ]; then
    VIRTUAL_ENV_DISABLE_PROMPT=1
    configure_prompt

# Enable syntax-highlighting with dimmed colors
    if [ -f /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh ]; then
        . /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh
        ZSH_HIGHLIGHT_HIGHLIGHTERS=(main brackets pattern)
        ZSH_HIGHLIGHT_STYLES[default]=none
        ZSH_HIGHLIGHT_STYLES[unknown-token]=fg=160
        ZSH_HIGHLIGHT_STYLES[reserved-word]=fg=037,bold
        ZSH_HIGHLIGHT_STYLES[suffix-alias]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[global-alias]=fg=064,bold
        ZSH_HIGHLIGHT_STYLES[precommand]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[commandseparator]=fg=160
        ZSH_HIGHLIGHT_STYLES[autodirectory]=fg=064,underline
        ZSH_HIGHLIGHT_STYLES[path]=fg=178
        ZSH_HIGHLIGHT_STYLES[globbing]=fg=160
        ZSH_HIGHLIGHT_STYLES[history-expansion]=fg=160
        ZSH_HIGHLIGHT_STYLES[command-substitution]=none
        ZSH_HIGHLIGHT_STYLES[variable]=fg=178
    fi
    # Enable auto-completion
    if [ -f /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh ]; then
        . /usr/share/zsh/functions/Completion/Unix/CommandNotFound.zsh
    fi

    # Enable history sharing between shells
    setopt share_history

    # Add custom bin directory to PATH
    export PATH="$HOME/bin:$PATH"
fi

# Load environment variables
if [ -f ~/.zshenv ]; then
    source ~/.zshenv
fi

# Add any other custom functions or aliases here
# Customize ls colors for a dimmed appearance
export LS_COLORS="di=1;34:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43"

# Alias for listing files
alias ll='ls -l'
alias la='ls -A'
alias l='ls -CF'
alias ll='ls -l'
alias la='ls -a'
alias lla='ls -la'
alias cls='clear'
alias c='clear'
alias z3t4rupdate= 'sudo apt update && sudo apt upgrade -y && sudo apt autoremove'

# Show hidden files in directory listing
export LS_OPTIONS='--color=auto'
eval "$(dircolors -b)"

# Custom functions can be defined here
# e.g. alias lsd='ls --color=auto -l -d'

# Add color to man pages
export LESS_TERMCAP_mb=$'\E[1;31m'     # begin blink
export LESS_TERMCAP_md=$'\E[1;36m'     # begin bold
export LESS_TERMCAP_me=$'\E[0m'        # reset bold/blink
export LESS_TERMCAP_so=$'\E[01;44;33m' # begin reverse video
export LESS_TERMCAP_se=$'\E[0m'        # reset reverse video
export LESS_TERMCAP_us=$'\E[1;32m'     # begin underline
export LESS_TERMCAP_ue=$'\E[0m'        # reset underline

# Colored GCC warnings and errors
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'
# END USER CONFIGURATION
term
