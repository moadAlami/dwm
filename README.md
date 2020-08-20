# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Patches

This build uses the following patches:

  * [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/) - Actually toggle fullscreen for a window, instead of toggling the status bar and the monocle layout.
  * [alpha](https://dwm.suckless.org/patches/alpha/) - Allow dwm to have translucent bars, while keeping all the text on it opaque.
  * [dragmfact](https://dwm.suckless.org/patches/dragmfact/) - Adds the ability to resize the split in the tile layout by holding the modkey and dragging the mouse.
  * [fakefullscreen](https://dwm.suckless.org/patches/fakefullscreen/) - Only allows clients to "fullscreen" into the space given to them.
  * [fullscreen](https://dwm.suckless.org/patches/fullscreen/) - Applies the monocle layout with the focused client on top and hides the bar.
  * [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/) - Prevents dwm from drawing tags with no clients on the bar.
  * [moveresize](https://dwm.suckless.org/patches/moveresize/) - Adds the ability to move and resize floating clients.
  * [movestack](https://dwm.suckless.org/patches/movestack/) - Allows for moving clients around the stack and swapping them with the master.
  * [noborder](https://dwm.suckless.org/patches/noborder/) - Remove the border when there is only one window visible.
  * [pertag](https://dwm.suckless.org/patches/pertag/) - Keeps layout, mwfact, barpos and nmaster per tag.
  * [ru gaps](https://dwm.suckless.org/patches/ru_gaps/) - Adds useless gaps to dwm.
  * [savefloats](https://dwm.suckless.org/patches/save_floats/) - Saves size and position of every floating window before it is forced into tiled mode. If the window is made floating again, the old dimensions will be restored.
  * [scratchpad](https://dwm.suckless.org/patches/scratchpad/) - Allows for spawning or restoring a terminal window.
  * [setborderpx](https://dwm.suckless.org/patches/setborderpx/) - Allows for changing border pixels at runtime
  * [stackmfact](https://dwm.suckless.org/patches/stackmfact/) - Allows for vertically resizing clients in the stack.
  * [status2d](https://dwm.suckless.org/patches/status2d/) - Allows colors and rectangle drawing in DWM status bar.
  * [statuscmd](https://dwm.suckless.org/patches/statuscmd/) - Adds the ability to execute shell commands based on the mouse button and position when clicking the status bar.
  * [sticky](https://dwm.suckless.org/patches/sticky/) - Adds the ability to make a client sticky. Which makes it visible on all tags.
  * [swallow](https://dwm.suckless.org/patches/swallow/) - Adds "window swallowing" to dwm.
  * [zoomswap](https://dwm.suckless.org/patches/zoomswap/) - Swaps the current window with the previous master when zooming.
