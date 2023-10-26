# FIONA-Workload: Neural Network Applications with Photonic Backends

[![version](https://img.shields.io/badge/version-1.1-orange)](https://github.com/hkust-fiona/) 
[![appear](https://img.shields.io/badge/appear-at_ICCAD_2023-blue)](https://iccad.com/)
[![license](https://img.shields.io/badge/license-Apache%202.0-light)](https://github.com/hkust-fiona/fiona-workload/LICENSE)

🎉Welcome to the **FIONA Workload** repository!   
🎯This sub-project is an integral part of the [FIONA-Toolchain](https://github.com/hkust-fiona/) and aims to provide a bundle of hand-tuned kernels and example neural-network applications that can run on [FIONA-SpikeSim](https://github.com/hkust-fiona/fiona-spikesim) and [FIONA-Hardware](https://github.com/hkust-fiona/fiona-hardware). The project hierarchy of this sub-project is shown as follows:

```
fiona-workload/
    |-- app/
        |-- hello_fiona/        ... hello-world sample for initial test
        |-- math_*/             ... example workloads of math library
        |-- nn_*/               ... example workloads of nn library
    |-- lib/
        |-- baremetal/          ... essential files for running without proxy kernels
        |-- base/               ... most basic headers including instruction defines
        |-- math/               ... provide libraries of photonic-backend math operations
        |-- nn/                 ... provide libraries of photonic-backend nn modules
        |-- utils/              ... provide utilities such as matrix printing
    |-- Makefile                ... script to auto compile all workloads
```


## Quickstarts
To compile the workloads, the RISC-V toolchain is required. Please follow the installation instructions by [RISC-V GNU Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) and [RISC-V Proxy Kernel](https://github.com/riscv-software-src/riscv-pk) before we continue the FIONA-Workload compilation.

```bash
# after you install RISC-V GNU Toolchain
export RISCV="<path/to/risc-v>"
git clone https://github.com/hkust-fiona/fiona-workload.git
cd fiona-workload/ && make
```

The compiled ELF files will be located in the directory of `build/`. To run on **spike** or **verilator**:

```bash
# please refer to the sibling project FIONA-SpikeSim
spike --extension=fiona pk build/<workload>.elf
```

## Citations
🎓Please cite the following paper if you find this work useful:

> Yinyi Liu, Bohan Hu, Zhenguo Liu, Peiyu Chen, Linfeng Du, Jiaqi Liu, Xianbin Li, Wei Zhang, Jiang Xu. **FIONA: Photonic-Electronic Co-Simulation Framework and Transferable Prototyping for Photonic Accelerator.** In *2023 IEEE/ACM International Conference on Computer-Aided Design (ICCAD).* IEEE, 2023.

## Acknowledgements
❤️I would like to express my sincere gratitude and appreciation to several organizations for their invaluable contributions to my work. Without their support, this endeavor would not have been possible:

|**Organizations**|**Supports**|
|---|---|
|[University Grants Committee (Hong Kong)](https://www.ugc.edu.hk/eng/ugc/index.html)|Research Funds|
|Guangzhou-HKUST(GZ) Joint Funding Program|Research Funds|


