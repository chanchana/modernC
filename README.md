# modernC
No more makefile, type just "c".

More easy way to compile C Source file<br>
Use only "c <your source file's name>"<br>
Atomatically compile and run your program or use custom run mode

# Installation & Update
```shell
git clone https://github.com/chanchana/modernC.git && cd modernC
chmod +x c && ./c --install
cd .. && rm -rf modernC
```

# How to use
```shell
c
```
For compiling all C source files in current directory and link them if it need!<br>
Same as make file but you just need to type "c"<br>
<br>
```shell
c MySourceFile.c
```
Compiling MySourceFile.c and run it<br>
<br>
<br>
```shell
c MySourceFile.c argv1 argv2 < input.dat > output.dat
```
Do what you want just like the same!<br>
<br>
<br>
```shell
c -help
```
To see all detail<br>
<br>
