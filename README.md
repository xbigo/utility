# utility

Misc or small helper components 

## Build

For Mac and Linux:

```bash
git clone https://github.com/xbigo/utility.git
mkdir build
cd build
cmake -S ../utility -D BUILD_TESTING=1
make
make check
make install
```

For MSVC:

```bat
git clone https://github.com/xbigo/utility.git
mkdir build
cd build
cmake -S ../utility -D BUILD_TESTING=1
cmake --build .
cmake --build . --target check
cmake --build . --target install
```

