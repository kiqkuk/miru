[[ -f ~/.local/share/miru/data/shell/env ]] && . ~/.local/share/miru/data/shell/env

if [[ -z $DISPLAY && $(tty) == /dev/tty1 ]]; then
  exec dwl-start
fi
