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

(sleep 3; clipit &)
nm-applet &
thunar --daemon &
xfce4-volumed &
xfce4-terminal --drop-down &
xfce4-power-manager &
(sleep 2; volti) &
(sleep 10; dropbox) &

compton &

while true; do

# Volume Level
#DWM_VOL=$( amixer -c0 sget Master | awk -vORS=' ' '/Mono:/ {print($6$4)}' | sed 's/ $/''/' );
DWM_VOL=$( amixer -c0 sget Master | awk -vORS=' ' '/Mono:/ {print($6$4)}');
DWM_VOL_NUMBER=$(echo $DWM_VOL | grep '[0-9]*' -o)
if [[ $DWM_VOL == *"off"* ]]; then
  DWM_VOL_ICON=""
elif (( $DWM_VOL_NUMBER < 50 )); then
  DWM_VOL_ICON=""
else
  DWM_VOL_ICON=""
fi

# Date and Time
DWM_CLOCK=$( date '+%e %b %Y %a - %k:%M' | sed 's/^ /''/');

# Overall output command
#DWM_STATUS="$DWM_VOL_ICON $DWM_VOL_NUMBER    $DWM_CLOCK";
DWM_STATUS=" $DWM_CLOCK";
xsetroot -name "$DWM_STATUS";
sleep 60;

done &

exec dwm
