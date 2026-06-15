# neural-network

A two-layer neural network in C that predicts XOR outputs, accelerated with AVX2 SIMD.

## What it is

A feedforward neural network that takes two numbers (0 or 1) as input and outputs a confidence score for whether the XOR result is 0 or 1. The forward pass is powered by a hand-written SIMD dot product in NASM assembly, giving a significant speedup over scalar computation.

## How it works

```
input [x1, x2]
    - dot product + bias  (hidden layer, 2 neurons)
    - sigmoid
    - dot product + bias  (output layer, 1 neuron)
    - sigmoid
    - confidence score (0.0 to 1.0)
```

The network uses hardcoded pretrained weights — no training code is included.

## Dependencies

- GCC
- NASM
- [simd-lib](https://github.com/OchErdene/simd-lib) (included as a git submodule)

## Build

```bash
git clone --recurse-submodules https://github.com/OchErdene/neural-network
cd neural-network
make
./bin/main
```

## Usage

Inputs are the four XOR cases:

| Input | Expected Output |
|------------|-----------------|
| `{0, 0}`   | 0 |
| `{0, 1}`   | 1 |
| `{1, 0}`   | 1 |
| `{1, 1}`   | 0 |

The program prints the confidence score for both 0 and 1 for each input, using both the scalar and SIMD dot product implementations.

## Benchmark

Tested on x86-64 Linux (AVX2):

| Implementation | Time |
|----------------|------------|
| Scalar | 0.000049s |
| SIMD | 0.000006s |
| **Speedup** | **~8x**    |

## Project Structure

```
neural-network/
├── src/
│   └── main.c
├── simd-lib/        # submodule
│   └── src/
│       ├── math.asm
│       └── simdlib.h
├── bin/
│   └── main
└── Makefile
```
