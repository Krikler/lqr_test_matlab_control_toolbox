# LQR comparison: MATLAB vs Control Toolbox

## Dependencies
- MATLAB with Control System Toolbox
- Control Toolbox: ct_core and ct_optcon

## Build
```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j
```

## Run
```bash
./test_lqr
```
