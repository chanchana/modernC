#!/bin/bash

################################################################################################
#######  ######### ################################           #####
#######  ########  ####### ######################   ############################################
#######  # ##### # ####### ####################   #################
#######  ## ### ## #   #   #   #   ##########   ###################
#######  ### # ### # # # # # ### ## #######   ##################################################
#######  #### #### #   #   #   # ## #####                ##########
################################################################################################

# More easy way to compile C Source file
# Use only "c <your source file's name>"
# Atomatically compile and run your program or use custom run mode
#
# to install, please type this line and press enter in terminal
# * make sure that you are in the directory that contain this file
#       chmod +x c && ./c --install
#
# This program use the default gcc compiler from your computer.
# Please make sure that you have installed gcc compiler

# Version 1.0
# Create by Chanchana Wicha 2018. All right reserved

################################################################################################

########## VARIABLES

RED="\033[31m"
GREEN="\033[0;32m"
NC="\033[0m"

########## FUNCTIONS

printError()
{
    echo -e "${RED}Error!${NC} $1"
}

initialize()
{
    path="${PATH%%:*}"
    cp c $path
    if [ -f "$path/c" ]
    then
        echo "Initialize successfully!"
        exit 999
    else
        printError "Cannot initialize"
    fi
}

########## MAIN

if [ "$1" = "--install" ]
then
    initialize
fi

source=$2

if [ -z "$2" ]
then
    source=$1
fi

if [ $# -eq 0 ]
then

    if [ ! -f "${PATH%%:*}/c" ]
    then
        initialize
    fi
    echo "Usage : "
    echo "   c [Run type] [C Scorce file name]"
    echo "   c --init : For initialize this program"
    echo "   [Run type]"
    echo "    Nothing : Compile and run"
    echo "    -c      : Compile only"
    echo "    -a      : Compile and run with arguments(type after -a)"
    echo "    -in     : Compile and run with input file"
    echo "    -ain    : Compile and run with arguments and input file"
    echo "    -ro     : Remove all object file"
    echo "    --install   : Install this program"
    echo "    --uninstall : Remove this program"
    exit 99
fi

if [ "$1" = "-ro" ]
then
    rm *.o
    exit 999
fi

if [ "$1" = "--uninstall" ]
then
    path="${PATH%%:*}"
    cd $path
    rm c
    echo "Uninstall successfully!"
    exit 999
fi

if [ ! -f "$source" ]
then
    printError "No file name $source in your directory"
    exit 0
fi

if [ ${source##*.} != "c" ]
then
    printError "Invalid .c source file"
    exit 1
fi

export=${source:0:${#source}-2}

if [ -f "$export" ]
then
    ##Found previous version
    rm $export
fi

echo "Input : $source"

gcc -o $export $source

if [ ! -f "$export" ]
then
	printError "$export cannot be compiled successfully"
    exit 2
fi

echo -e "${GREEN}Compiled to $export${NC}"

if [ "$1" = "-c" ]
then
    exit 999
fi

if [ "$1" = "-a" ]
then
    echo -e "${GREEN}Running $export${NC}"
    echo " "
    if [ -f "./$export" ]
    then
        ./$export < ${@:3}
    else
        $export < ${@:3}
    fi
fi

if [ "$1" = "-in" ]
then
    echo -e "${GREEN}Running $export${NC}"
    echo " "
    if [ -f "./$export" ]
    then
        ./$export < $3
    else
        $export < $3
    fi
fi

if [ -z $2 ]
then
    echo -e "${GREEN}Running $export${NC}"
    echo " "
    if [ -f "./$export" ]
    then
        ./$export
    else
        $export
    fi
fi