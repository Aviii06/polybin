# polybin
Helps you play a sequence of obj files.
# Build
```
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --build . -j $(nproc)
```

# Run
`./polybin /path/to/objs numberOfFiles`
