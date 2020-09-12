# GUI Makefile Generator
This program don't is complete


![Alt text](/screenshots/main.png?raw=true "Tela principal")

## Build
install gtk+ 2.0:
`apt-get install libgtk2.0-dev`

to copile:
```sh
gcc -Wall -o makcreator makcreator.c utils.c `` `pkg-config --libs --cflags gtk+-2.0` ``
```

makcreator.c is the main file
