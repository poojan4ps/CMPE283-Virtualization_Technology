/*  CMPE283 file "Poojan"
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm/msr.h>

#define MAX_MSG 80

/*
 * Model specific registers (MSRs) by the module.
 * See SDM volume 4, section 2.1
 */
#define IA32_VMX_PINBASED_CTLS 0x481
#define IA32_VMX_PROCBASED_CTLS 0x482
#define IA32_VMX_PROCBASED_CTLS2 0x48B
#define IA32_VMX_EXIT_CTLS 0x483
#define IA32_VMX_ENTRY_CTLS 0x484
#define IA32_VMX_PROCBASED_CTLS3 0X92
/*
 * struct capability_info
 *
 * Represents a single capability (bit number and description).
 * Used by report_capability to output VMX capabilities.
 */
struct capability_info {
	uint8_t bit;
	const char *name;
};


/*
 * Pinbased capabilities
 * See SDM volume 3, section 24.6.1
 */
struct capability_info pinbasedctls[5] =
{
	{ 0, "External Interrupt Exiting" },
	{ 3, "NMI Exiting" },
	{ 5, "Virtual NMIs" },
	{ 6, "Activate VMX Preemption Timer" },
	{ 7, "Process Posted Interrupts" }
};


struct capability_info procbasedctls[22] =
{
	{ 2, "Interrupt Window Exiting" },
	{ 3, "Use TSC Offsetting" },
	{ 7, "HLT Exiting" },
	{ 9, "INVLPG Exiting" },
	{ 10, "MWAIT Exiting" },
	{ 11, "RDPMC Exiting" },
	{ 12, "RDTSC Exiting" },
	{ 15, "CR3 Load Exiting" },
	{ 16, "CR3 Store Exiting" },
	{ 17, "Activate Tertiary Controls" },
	{ 19, "CR8 Load Exiting" },
	{ 20, "CR8 Store Exiting" },
	{ 21, "Use TPR Shadow" },
	{ 22, "NMI Window Exiting" },
	{ 23, "MOV-DR Exiting" },
	{ 24, "Unconditional I/O Exiting" },
	{ 25, "Use I/O Bitmaps" },	
	{ 27, "Monitor Trap Flag" },
	{ 28, "Use MSR Bitmaps" },
	{ 29, "MONITOR Exiting" },
	{ 30, "PAUSE Exiting" },
	{ 31, "Activate Secondary Controls" }
};


struct capability_info procbased2ctls[27] =
{
    { 0, "Virtualize APIC accesses" },	
    { 1, "Enable EPT" },	
    { 2, "Descriptor Table Exiting" },	
    { 3, "Enable RDTSCP" },	
    { 4, "Virtualize x2APIC Mode" },	
    { 5, "Enable VPID" },	
    { 6, "WBINVD Exiting" },	
    { 7, "Unrestricted Guest" },	
    { 8, "APIC-register Virtualization" },	
    { 9, "Virtual-interrupt Delivery" },	
    { 10, "PAUSE-loop Exiting" },	
    { 11, "RDRAND exiting" },	
    { 12, "Enable INVPCID" },
    { 13, "Enable VM Functions" },
    { 14, "VMCS Shadowing" },
    { 15, "Enable ENCLS Exiting" },
    { 16, "RDSEED Exiting" },
    { 17, "Enable PML" },
    { 18, "EPT-violation #VE" },
    { 19, "Conceal VMX from PT" },
    { 20, "Enable XSAVES/XRSTORS" },
    { 22, "Mode-based Execute Control for EPT" },
    { 23, "Sub-page Write Permissions for EPT" },
    { 24, "Intel PT Uses Guest Physical Addresses" },
    { 25, "Use TSC Scaling" },
    { 26, "Enable User Wait and Pause" },
    { 28, "Enable ENCLV Exiting" }
};

struct capability_info tertiaryprocbasedctls3[4] =
{
    { 0, "LOADIWKEY Exiting" },	
    { 1, "Enable HLAT" },
    { 2, "EPT Paging-write Control" },
    { 3, "Guest-paging Verification" }
};
struct capability_info exitctls[14] =
{
    { 2, "Save Debug Controls" },	
    { 9, "Host Address-Space Size" },	
    { 12, "Load IA32_PERF_GLOBAL_CTRL" },	
    { 15, "Acknowledge Interrupt On Exit" },	
    { 18, "Save IA32_PAT" },	
    { 19, "Load IA32_PAT" },	
    { 20, "Save IA32_EFER" },	
    { 21, "Load IA32_EFER" },	
    { 22, "Save VMXpreemption Timer Value" },	
    { 23, "Clear IA32_BNDCFGS" },	
    { 24, "Conceal VMX from PT" },	
    { 25, "Clear IA32_RTIT_CTL" },	
    { 28, "Load CET state" },	
    { 29, "Load PKRS" },
};


struct capability_info entryctls[12] =
{
    { 2, "Load Debug Controls" },	
    { 9, "IA-32e Mode Guest" },	
    { 10, "Entry to SMM" },	
    { 11, "Deactivate Dual Monitor Treatment" },	
    { 13, "Load IA32_PERF_GLOBAL_CTRL" },	
    { 14, "Load IA32_PAT" },	
    { 15, "Load IA32_EFER" },	
    { 16, "Load IA32_BNDCFGS" },	
    { 17, "Conceal VMX from PT" },	
    { 18, "Load IA32_RTIT_CTL" },	
    { 20, "Load CET State" },	
    { 22, "Load PKRS" } 
};
/*
 * report_capability
 *
 * Reports capabilities present in 'cap' using the corresponding MSR values
 * provided in 'min' and 'max'.
 *
 * Parameters:
 *  cap:  capability_info structure for tmaxs feature
 *  length: number of entries in 'cap'
 *  min: low 32 bits of capability MSR value describing tmaxs feature
 *  max: high 32 bits of capability MSR value describing tmaxs feature
 */
void
report_capability(struct capability_info *cap, uint8_t length, uint32_t min,
    uint32_t max)
{
	uint8_t res;
	struct capability_info *c;
	char info[MAX_MSG];

	memset(info, 0, sizeof(info));
      res=0;
      while ( res < length )
	 {
		c = &cap[res];
		snprintf(info, 79, "  %s: Can set=%s, Can clear=%s\n",
		    c->name,
		    (max & (1 << c->bit)) ? "Yes" : "No",
		    !(min & (1 << c->bit)) ? "Yes" : "No");
		printk(info);
            res++;
	}
}

/*
 * detect_vmx_features
 *
 * Detects and prints VMX capabilities of tmaxs host's CPU.
 */
void
  detect_vmx_features(void)
{
	uint32_t min, max;

	/* Pinbased controls */
	rdmsr(IA32_VMX_PINBASED_CTLS, min, max);
	pr_info("Pinbased Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(pinbasedctls, 5, min, max);
	
	/* Procbased controls */
	rdmsr(IA32_VMX_PROCBASED_CTLS, min, max);
	pr_info("Procbased Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(procbasedctls, 22, min, max);

	
	/* Procbased secondary controls */
	rdmsr(IA32_VMX_PROCBASED_CTLS2, min, max);
	pr_info("Procbased Secondary Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(procbased2ctls, 27, min, max);

     /* Procbased tertiary controls */
      rdmsr(IA32_VMX_PROCBASED_CTLS3, min, max);
	pr_info("Procbased tertiary Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(tertiaryprocbasedctls3, 4, min, max);


	
	/* Exit controls */
	rdmsr(IA32_VMX_EXIT_CTLS, min, max);
	pr_info("Exit Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(exitctls, 14, min, max);

	
	/* Entry controls */
	rdmsr(IA32_VMX_ENTRY_CTLS, min, max);
	pr_info("Entry Controls MSR: 0x%llx\n",
		(uint64_t)(min | (uint64_t)max << 32));
	report_capability(entryctls, 12, min, max);


}

/*
 * init_module
 *
 * Module entry point
 *
 * Return Values:
 *  Always 0
 */
int
init_module(void)
{
	printk(KERN_INFO "CMPE 283 Assignment 1 Module Start\n");

	  detect_vmx_features();


	/* 
	 * A non 0 return means init_module failed; module can't be minaded. 
	 */
	return 0;
}

/*
 * cleanup_module
 *
 * Function called on module unminad
 */
void
cleanup_module(void)
{
	printk(KERN_INFO "CMPE 283 Assignment 1 Module Exits\n");
}
MODULE_LICENSE("GPL");