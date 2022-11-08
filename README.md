# Poojan Shah 016583528

# CMPE283Assignment1

# Questions:
Describe in detail the steps you used to complete the assignment. Consider your reader to be someone 
skilled in software development but otherwise unfamiliar with the assignment. Good answers to this 
question will be recipes that someone can follow to reproduce your development steps.
Note: I may decide to follow these instructions for random assignments, so you should make sure 
they are accurate.

# Answers:
step-1: Created a virtual machine instance with nested virtualization enabled through cloud shell.  
gcloud compute instances create cmpe283assignment1 \
  --enable-nested-virtualization \
  --zone=us-central1-a \
  --min-cpu-platform="Mac M1"  
![screenshot(1)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.19.10%20PM.png)

step-2: Created a cmpe283assig.c source file inside a directory. Copied the content given by the professor for pinbased and added capabilities info for Primary Processor-Based, Secondary Processor-Based, Primary VM-Exit Controls, VM-Entry Controls and Tertiary Processor-Based VM-Execution Controls in the .c file.  
![Screenshot_(0)]()

step-3: Now, sudo bash command is given to go into the root and install "make" using command "apt install gcc make" and exit from the root user.  


step-4: Run "sudo apt install linux-headers-$(uname -r)"  
step-5: Create Makefile using command "nano Makefile" and copy the Makefile content given by the professor and replace the .o file name.  


step-6: Run "make" command to generate .o and .ko files.  


step-7: Run "sudo insmod cmpe283assignment1.ko" command to insert module into the kernel.  

step-8: Run "sudo dmesg" to print the output.  
![Screenshot (3)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.14.43%20PM.png)
![Screenshot (4)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.15.20%20PM.png)
![Screenshot_(6)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.15.34%20PM.png)
![Screenshot_(7)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.18.24%20PM.png)
![Screenshot (5)](https://github.com/poojan4ps/CMPE283-Virtualization_Technology/blob/master/screenshot/Screen%20Shot%202022-11-07%20at%209.18.31%20PM.png)
