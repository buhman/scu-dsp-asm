V=3

make TARGET=x86_64-pc-linux-gnu-       SUFFIX=.$V.Linux.x86_64       clean
make TARGET=x86_64-pc-linux-gnu-       SUFFIX=.$V.Linux.x86_64       all -j`nproc`

make TARGET=aarch64-unknown-linux-gnu- SUFFIX=.$V.Linux.aarch64      clean
make TARGET=aarch64-unknown-linux-gnu- SUFFIX=.$V.Linux.aarch64      all -j`nproc`

make TARGET=x86_64-w64-mingw32-        SUFFIX=.$V.Windows.x86_64.exe clean
make TARGET=x86_64-w64-mingw32-        SUFFIX=.$V.Windows.x86_64.exe all -j`nproc`

make TARGET=i686-w64-mingw32-          SUFFIX=.$V.Windows.i686.exe   clean
make TARGET=i686-w64-mingw32-          SUFFIX=.$V.Windows.i686.exe   all -j`nproc`
#make SUFFIX=$V.MacOS-Ventura.x86_64 clean all
