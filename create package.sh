#!/bin/sh
DIR_CURR=$(pwd)
rm -f makefile-creator*.deb
dpkg-deb -b "$DIR_CURR/Package" "$DIR_CURR"
zenity --info --text="Pacote criado com sucesso!"
