# polybin
A visualizer for [openargus](https://github.com/narain/openargus) project.

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
