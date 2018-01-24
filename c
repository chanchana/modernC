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

# Version 1.1.1
# Updated 24 JAN 2018
# Bug fixed
# Updated 23 JAN 2018
# 1.1 - Add atomatic compile and link all C files in directory
# Create by Chanchana Wicha 2018. All right reserved

################################################################################################

########## VARIABLES

VERSION="1.1.1"

RED="\033[31m"
GREEN="\033[0;32m"
NC="\033[0m"

########## FUNCTIONS

printError()
{
    echo -e "${RED}Error!${NC} $1"
}

printUsage()
{
    echo "Usage : "
    echo "   c [Run type] [C Scorce file name]"
    echo "   c        : Compile all C files and link them"
    echo "   [Run type]"
    echo "    Nothing     : Compile and run"
    echo "    All Nothing : Compile all C files and link them"
    echo "    -c      : Compile only"
    echo "    -a      : Compile and run with arguments(type after -a)"
    echo "    -in     : Compile and run with input file"
    echo "    -ain    : Compile and run with arguments and input file"
    echo "    -ro     : Remove all object file"
    echo "    -v      : Version"
    echo "   <Any argument> : Place this string after call the program"
    echo "    --install   : Install this program"
    echo "    --uninstall : Remove this program"
}

initialize()
{
    path="${PATH%%:*}"
    cp c $path
    echo "$path"
    if [ -f "$path/c" ]
    then
        echo "Initialize successfully!"
        exit 999
    else
        printError "Cannot initialize"
    fi
}

compileAll()
{

    array=()
    while IFS=  read -r -d $'\0'; do
        array+=("$REPLY")
    done < <(find *.c -print0)

    mainFiles=()
    linkFiles=()
    compileErrorFiles=()

    for x in ${array[*]}; do
        echo $x
        gcc -c $x
        name="${x:0:${#x}-2}"
        oname="$name.o"
        if [ -f "$oname" ]
        then
            list=$(nm $oname)
            if [[ "$list" =~ "main" ]]
            then
                echo -e "${GREEN}$x has main function${NC}"
                mainFiles+=($x)
            else
                linkFiles+=($x)
            fi
        else
            compileErrorFiles+=($x)
        fi
        #echo 
    done

    exportFiles=()
    errorFiles=()

    for x in ${mainFiles[*]}; do
        name="${x:0:${#x}-2}"
        echo "$name"
        if [ -f "$name" ]
        then
            rm $name
        fi
        gcc -o $name $x ${linkFiles[*]}
        if [ -f "$name" ]
        then
            exportFiles+=($name)
        else
            errorFiles+=($name)
        fi
    done

    echo "Compile finish!"
    for x in ${exportFiles[*]}; do
        echo -e "${GREEN}Exported to $x${NC}"
    done

    for x in ${errorFiles[*]}; do
        printError "cannot export to ${RED}$x${NC}"
    done

    for x in ${compileErrorFiles[*]}; do
        printError "compiling error with ${RED}$x${NC}"
    done

    rm *.o
    #echo "${array[*]}"
    #gcc -o a $files
}

########## MAIN

if [ "$1" = "-v" ]
then
    echo "modernC version $VERSION"
    exit 99
fi

if [ "$1" = "--install" ]
then
    initialize
fi

if [ $# -eq 0 ]
then
    if [ ! -f "${PATH%%:*}/c" ]
    then
        initialize
    fi
    compileAll
    exit 999999
fi

source=$2

if [ -z "$2" ]
then
    source=$1
fi

if [ "$1" = "-help" ]
then
    printUsage
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


if [ "$1" = "." ]
then
    compileAll
    exit 0
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

if [ ! -z $2 ]
then
    echo -e "${GREEN}Running $export${NC}"
    echo " "
    if [ -f "./$export" ]
    then
        ./$export ${@:2}
    else
        $export ${@:2}
    fi
    
fi