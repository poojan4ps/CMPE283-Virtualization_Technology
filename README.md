# Rutvik Moradiya 016656367
# Jack Kalavadiya 016197519
# Discovering VMX Features

Done By Rutvik & Jack
 > Configure a Linux machine, either VM based or on real hardware. You may use any Linux distribution you wish.

Done By Jack 
 > Download and build the Linux kernel source code

Done By Rutvik
 > Create a new kernel module with the assignment functionality

Done By Rutvik & Jack 
 > Load (insert) the new module

Done By Rutvik & Jack 
 > Verify proper output in the system message log.

## Introduction

 > First of All,  intialize Google Cloud CLI on your local machine for managing the compute engine resources with the command and spin up a Linux instance by running the following commands,

`gcloud compute instances create YOUR_INSTANCE_NAME --enable-nested-virtualization --min-cpu-platform="Intel Haswell"`

 > Place your "YOUR_INSTANCE_NAME".

 > Choose the best suitable zone as per your need, we choose "us-west1-b" zone while installing Google Cloud CLI.

 > Then create nested virtualization by adding the flag "--enable-nested-virtualization" and the CPU platform is set to "Intel Haswell".

### Add SSH into your nested virtualization

 > add SSH into your instance by using the this command, where place your zone name and project name

`gcloud compute ssh --zone "YOUR_ZONE" "YOUR_INSTANCE_NAME" --project "YOUR_PROJECT_NAME"`

 > Once you are inside the linux instance, you need to setup a couple of tools in order to execute the C source code.

### Installation of the gcc and make in instance

`sudo apt install gcc make`

### Install headers in Linux OS

`sudo apt install linux-headers-$(uname -r)`

### Clone cod from GITHUB repo and Execute the code

 > Generate the C file by using the following command that will create ".ko" file form "vmx-cap.c" file

`make`

### Insetation of kernel module into the Linux kernel

 > Run the following command for inserting the module to Linux kernel

`sudo insmod vmx-cap.ko`

### Reterive output

 > Use the following command to display output from the kernel buffer

`sudo dmesg`


```
[   92.247815] CMPE-283-Assignment-1 Module Start
[   92.253628] Pinbased Controls MSR: 0x3f00000016
[   92.259683]   External Interrupt Exiting: Can set=Yes, Can clear=Yes
[   92.267708]   NMI Exiting: Can set=Yes, Can clear=Yes
[   92.274494]   Virtual NMIs: Can set=Yes, Can clear=Yes
[   92.281133]   Activate VMX Preemption Timer: Can set=No, Can clear=Yes
[   92.289165]   Process Posted Interrupts: Can set=No, Can clear=Yes
[   92.300100] Procbased Controls MSR: 0xf7b9fffe0401e172
[   92.306733]   Interrupt Window Exiting: Can set=Yes, Can clear=Yes
[   92.314411]   Use TSC Offsetting: Can set=Yes, Can clear=Yes
[   92.321575]   HLT Exiting: Can set=Yes, Can clear=Yes
[   92.328121]   INVLPG Exiting: Can set=Yes, Can clear=Yes
[   92.334936]   MWAIT Exiting: Can set=Yes, Can clear=Yes
[   92.341831]   RDPMC Exiting: Can set=Yes, Can clear=Yes
[   92.348531]   RDTSC Exiting: Can set=Yes, Can clear=Yes
[   92.354428]   CR3 Load Exiting: Can set=Yes, Can clear=No
[   92.359942]   CR3 Store Exiting: Can set=Yes, Can clear=No
[   92.365882]   Activate Tertiary Controls: Can set=No, Can clear=Yes
[   92.372257]   CR8 Load Exiting: Can set=Yes, Can clear=Yes
[   92.377851]   CR8 Store Exiting: Can set=Yes, Can clear=Yes
[   92.383529]   Use TPR Shadow: Can set=Yes, Can clear=Yes
[   92.388949]   NMI Window Exiting: Can set=No, Can clear=Yes
[   92.394627]   MOV-DR Exiting: Can set=Yes, Can clear=Yes
[   92.400163]   Unconditional I/O Exiting: Can set=Yes, Can clear=Yes
[   92.406537]   Use I/O Bitmaps: Can set=Yes, Can clear=Yes
[   92.412050]   Monitor Trap Flag: Can set=No, Can clear=Yes
[   92.417641]   Use MSR Bitmaps: Can set=Yes, Can clear=Yes
[   92.423146]   MONITOR Exiting: Can set=Yes, Can clear=Yes
[   92.428657]   PAUSE Exiting: Can set=Yes, Can clear=Yes
[   92.433992]   Activate Secondary Controls: Can set=Yes, Can clear=Yes
[   92.442294] Secondary Procbased Controls MSR: 0x51ff00000000
[   92.448065]   Virtualize APIC accesses: Can set=Yes, Can clear=Yes
[   92.454352]   Enable EPT: Can set=Yes, Can clear=Yes
[   92.459419]   Descriptor Table Exiting: Can set=Yes, Can clear=Yes
[   92.465702]   Enable RDTSCP: Can set=Yes, Can clear=Yes
[   92.471032]   Virtualize x2APIC Mode: Can set=Yes, Can clear=Yes
[   92.477146]   Enable VPID: Can set=Yes, Can clear=Yes
[   92.482313]   WBINVD Exiting: Can set=Yes, Can clear=Yes
[   92.487739]   Unrestricted Guest: Can set=Yes, Can clear=Yes
[   92.493608]   APIC-register Virtualization: Can set=Yes, Can clear=Yes
[   92.500246]   Virtual-interrupt Delivery: Can set=No, Can clear=Yes
[   92.506629]   PAUSE-loop Exiting: Can set=No, Can clear=Yes
[   92.512309]   RDRAND exiting: Can set=No, Can clear=Yes
[   92.517643]   Enable INVPCID: Can set=Yes, Can clear=Yes
[   92.523181]   Enable VM Functions: Can set=No, Can clear=Yes
[   92.528943]   VMCS Shadowing: Can set=Yes, Can clear=Yes
[   92.534362]   Enable ENCLS Exiting: Can set=No, Can clear=Yes
[   92.540212]   RDSEED Exiting: Can set=No, Can clear=Yes
[   92.545547]   Enable PML: Can set=No, Can clear=Yes
[   92.550621]   EPT-violation #VE: Can set=No, Can clear=Yes
[   92.556214]   Conceal VMX from PT: Can set=No, Can clear=Yes
[   92.561980]   Enable XSAVES/XRSTORS: Can set=No, Can clear=Yes
[   92.567920]   Mode-based Execute Control for EPT: Can set=No, Can clear=Yes
[   92.574990]   Sub-page Write Permissions for EPT: Can set=No, Can clear=Yes
[   92.582058]   Intel PT Uses Guest Physical Addresses: Can set=No, Can clear=Yes
[   92.589496]   Use TSC Scaling: Can set=No, Can clear=Yes
[   92.594916]   Enable User Wait and Pause: Can set=No, Can clear=Yes
[   92.601288]   Enable ENCLV Exiting: Can set=No, Can clear=Yes
[   92.608737] Exit Controls MSR: 0x3fefff00036dff
[   92.613380]   Save Debug Controls: Can set=Yes, Can clear=No
[   92.619320]   Host Addres-Space Size: Can set=Yes, Can clear=Yes
[   92.625434]   Load IA32_PERF_GLOBAL_CTRL: Can set=No, Can clear=Yes
[   92.631808]   Acknowledge Interrupt On Exit: Can set=Yes, Can clear=Yes
[   92.638622]   Save IA32_PAT: Can set=Yes, Can clear=Yes
[   92.643955]   Load IA32_PAT: Can set=Yes, Can clear=Yes
[   92.649289]   Save IA32_EFER: Can set=Yes, Can clear=Yes
[   92.654717]   Load IA32_EFER: Can set=Yes, Can clear=Yes
[   92.660137]   Save VMXpreemption Timer Value: Can set=No, Can clear=Yes
[   92.666861]   Clear IA32_BNDCFGS: Can set=No, Can clear=Yes
[   92.672570]   Conceal VMX from PT: Can set=No, Can clear=Yes
[   92.678423]   Clear IA32_RTIT_CTL: Can set=No, Can clear=Yes
[   92.684191]   Clear IA32_LBR_CTL: Can set=No, Can clear=Yes
[   92.689871]   Load CET state: Can set=No, Can clear=Yes
[   92.695209]   Load PKRS: Can set=No, Can clear=Yes
[   92.700113]   Activate Secondary Controls: Can set=No, Can clear=Yes
[   92.708188] Entry Controls MSR: 0xd3ff000011ff
[   92.712744]   Load Debug Controls: Can set=Yes, Can clear=No
[   92.718511]   IA-32e Mode Guest: Can set=Yes, Can clear=Yes
[   92.724191]   Entry to SMM: Can set=No, Can clear=Yes
[   92.729351]   Deactivate Dual Monitor Treatment: Can set=No, Can clear=Yes
[   92.736422]   Load IA32_PERF_GLOBAL_CTRL: Can set=No, Can clear=Yes
[   92.742796]   Load IA32_PAT: Can set=Yes, Can clear=Yes
[   92.748139]   Load IA32_EFER: Can set=Yes, Can clear=Yes
[   92.753559]   Load IA32_BNDCFGS: Can set=No, Can clear=Yes
[   92.759151]   Conceal VMX from PT: Can set=No, Can clear=Yes
[   92.764918]   Load IA32_RTIT_CTL: Can set=No, Can clear=Yes
[   92.770695]   Load CET State: Can set=No, Can clear=Yes
[   92.776030]   Load Guest IA32_LBR_CTL: Can set=No, Can clear=Yes
[   92.782143]   Load PKRS: Can set=No, Can clear=Yes

root@instance-1:/home/rutvikjack/one#
```

 > Now we can decide that CPU does not have Tertiary Procbased Controls as the "Activate Tertiary Controls" feature in Procbased Controls cannot be set. Secondary Procbased Controls are available because the "Activate Secondary Controls" under Procbased Controls can be set and we can see those features listed as well.

### Removing the Linux kernel

 > By using the rmod command we can remove the module from the kernel

`rmmod vmx-cap`

### Clean

 > Run the following command to remove all the executables

`make clean`

### References:

https://cloud.google.com/compute/docs/instances/nested-virtualization/enabling
https://sjsu.instructure.com/courses/1530373/files/70231909
