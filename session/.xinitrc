#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

eval $(/usr/bin/gnome-keyring-daemon --start --components=pkcs11,secrets,ssh)
export SSH_AUTH_SOCK
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

setxkbmap es

sh ~/.fehbg &

dwmstatus &

(sleep 3; clipit &)
nm-applet &
thunar --daemon &
xfce4-volumed &
xfce4-terminal --drop-down &
xfce4-power-manager &
(sleep 2; volti) &
(sleep 10; dropbox) &

compton &

exec dwm
