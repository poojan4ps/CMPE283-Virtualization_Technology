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
  --min-cpu-platform="Intel Haswell"  
![Screenshot (418)](Screen Shot 2022-11-07 at 9.19.10 PM.png)

step-2: Created a cmpe283assignment1.c source file inside a directory. Copied the content given by the professor for pinbased and added capabilities info for Primary Processor-Based, Secondary Processor-Based, Primary VM-Exit Controls, VM-Entry Controls and Tertiary Processor-Based VM-Execution Controls in the .c file.  
![Screenshot (419)](https://user-images.githubusercontent.com/45283425/200281266-3c6ebe0c-ab58-4c99-93d0-3c2b7b33e320.png)
![Screenshot (420)](https://user-images.githubusercontent.com/45283425/200281576-ad2a0c05-58e9-40c7-8fa6-da172c2eaa78.png)

step-3: Now, sudo bash command is given to go into the root and install "make" using command "apt install gcc make" and exit from the root user.  
![Screenshot (421)](https://user-images.githubusercontent.com/45283425/200282047-cdeb7eb3-0982-44d6-b6d8-052930cbe012.png)

step-4: Run "sudo apt install linux-headers-$(uname -r)"  
step-5: Create Makefile using command "nano Makefile" and copy the Makefile content given by the professor and replace the .o file name.  
![Screenshot (422)](https://user-images.githubusercontent.com/45283425/200282393-2887445b-9999-4cb8-abec-16580a42f4a9.png)

step-6: Run "make" command to generate .o and .ko files.  
![Screenshot (423)](https://user-images.githubusercontent.com/45283425/200282819-dd9b37ff-1a88-4154-9388-c5f9bd5bff60.png)

step-7: Run "sudo insmod cmpe283assignment1.ko" command to insert module into the kernel.  

step-8: Run "sudo dmesg" to print the output.  
![Screenshot (424)](https://user-images.githubusercontent.com/45283425/200283435-e90f55f1-c93e-4334-b929-54065eb36b8a.png)
![Screenshot (425)](https://user-images.githubusercontent.com/45283425/200283483-c09da4f1-3c5d-47ae-b0c6-c89c86bb7263.png)
![Screenshot (426)](https://user-images.githubusercontent.com/45283425/200283525-a2c1dc23-d6d3-4969-98e1-05d0cc8f5685.png)
