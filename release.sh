V=2
M=scu-dsp-asm.$V

make TARGET=x86_64-pc-linux-gnu- MAIN=$M.Linux.x86_64       clean all
make TARGET=x86_64-w64-mingw32-  MAIN=$M.Windows.x86_64.exe clean all
make TARGET=i686-w64-mingw32-    MAIN=$M.Windows.i686.exe   clean all
#make MAIN=$M.MacOS-Ventura.x86_64 clean all
