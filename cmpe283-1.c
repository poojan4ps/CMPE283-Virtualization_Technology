/*  
 * cmpe283-1.c - Kernel module for CMPE283 assignment 1
 * for page reference -> Combined Volume Set of Intel® 64 and IA-32 Architectures Software Developers Manuals
 * book link: https://cdrdv2.intel.com/v1/dl/getContent/671200
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm/msr.h>

#define MAX_MSG 128

/*
 * Model specific registers (MSRs) by the module.
 * SDM volume 4 Model-Specific Registers, 
 * Section 2.1 ARCHITECTURAL MSRS, 
 * Table 2-2. IA-32 Architectural MSRs (Contd.)
 * Page 4340
 */
#define IA32_VMX_PINBASED_CTLS	0x481
#define IA32_VMX_PROCBASED_CTLS 0x482
#define IA32_VMX_PROCBASED_CTLS2 0x48B
#define IA32_VMX_PROCBASED_CTLS3 0x492
#define IA32_VMX_EXIT_CTLS 0x483
#define IA32_VMX_ENTRY_CTLS 0x484

/*
 * struct caapability_info
 *
 * Represents a single capability (bit number and description).
 * Used by report_capability to output VMX capabilities.
 */
struct capability_info {
	uint8_t bit;
	const char *name;
};

/*
 * IA32_VMX_PINBASED_CTLS : 0x481
 * Pin-Based VM-Execution Controls
 * SDM volume 3 System Programming Guide, 
 * Section 24.6.1 Pin-Based VM-Execution Controls, 
 * Table 24-5. Definitions of Pin-Based VM-Execution Controls
 * Page 3746
 */
struct capability_info pin_based_exe_ctls[5] =
{
	{ 0, "External-Interrupt Exiting" },
	{ 3, "NMI Exiting" },
	{ 5, "Virtual NMIs" },
	{ 6, "Activate VMX-Preemption Timer" },
	{ 7, "Process Posted Interrupts" }
};

/*
 * IA32_VMX_PROCBASED_CTLS: 0x482
 * Processor-Based VM-Execution Controls - Primary
 * SDM volume 3 System Programming Guide, 
 * Section 24.6.2 Processor-Based VM-Execution Controls, 
 * Table 24-6. Definitions of Primary Processor-Based VM-Execution Controls
 * Page 3746
 */
struct capability_info proc_p_based_exe_ctls[22] =
{
	{ 2, "Interrupt-Window Exiting" },
	{ 3, "Use TSC Offsetting" },
	{ 7, "HLT Exiting" },
	{ 9, "INVLPG Exiting" },
	{ 10, "MWAIT Exiting" },
	{ 11, "RDPMC Exiting" },
	{ 12, "RDTSC Exiting" },
	{ 15, "CR3-Load Exiting" },
	{ 16, "CR3-Store Exiting" },
	{ 17, "Activate Tertiary Controls" },
	{ 19, "CR8-Load Exiting" },
	{ 20, "CR8-Store Exiting" },
	{ 21, "Use TPR Shadow" },
	{ 22, "NMI-Window Exiting" },
	{ 23, "MOV-DR Exiting" },
	{ 24, "Unconditional I/O Exiting" },
	{ 25, "Use I/O Bitmaps" },
	{ 27, "Monitor Trap Flag" },
	{ 28, "Use MSR Bitmaps" },
	{ 29, "MONITOR Exiting" },
	{ 30, "PAUSE Exiting" },
	{ 31, "Activate Secondary Controls" }
};

/*
 * IA32_VMX_PROCBASED_CTLS2 : 0x48B
 * Processor-Based VM-Execution Controls - Secondary
 * SDM volume 3 System Programming Guide,
 * Section 24.6.2 Processor-Based VM-Execution Controls, 
 * Table 24-7. Definitions of Secondary Processor-Based VM-Execution Controls
 * Page 3748
 */
struct capability_info proc_s_based_exe_ctls[28] =
{
	{ 0, "Virtualize APIC Accesses" },
	{ 1, "Enable EPT" },
	{ 2, "Descriptor-Table Exiting" },
	{ 3, "Enable RDTSCP" },
	{ 4, "Virtualize x2APIC Mode" },
	{ 5, "Enable VPID" },
	{ 6, "WBINVD Exiting" },
	{ 7, "Unrestricted Guest" },
	{ 8, "APIC-Register Virtualization" },
	{ 9, "Virtual-Interrupt Delivery" },
	{ 10, "PAUSE-Loop Exiting" },
	{ 11, "RDRAND Exiting" },
	{ 12, "Enable INVPCID" },
	{ 13, "Enable VM Functions" },
	{ 14, "VMCS Shadowing" },
	{ 15, "Enable ENCLS Exiting" },
	{ 16, "RDSEED Exiting" },
	{ 17, "Enable PML" },
	{ 18, "EPT-Violation #VE" },
	{ 19, "Conceal VMX From PT" },
	{ 20, "Enable XSAVES/XRSTORS" },
	{ 22, "Mode-Based Execute Control For EPT" },
	{ 23, "Sub-Page Write Permissions For EPT" },
	{ 24, "Intel PT Uses Guest Physical Addresses" },
	{ 25, "Use TSC Scaling" },
	{ 26, "Enable User Wait And Pause" },
	{ 27, "Enable PCONFIG" },
	{ 28, "Enable ENCLV Exiting" }
};

/*
 * IA32_VMX_PROCBASED_CTLS3 : 0x492
 * Processor-Based VM-Execution Controls - Tertiary
 * SDM volume 3 System Programming Guide
 * Section 24.6.2 Processor-Based VM-Execution Controls
 * Table 24-8. Definitions of Tertiary Processor-Based VM-Execution Controls
 * Page 3749
 */
struct capability_info proc_t_based_exe_ctls[4] =
{
	{ 0, "LOADIWKEY Exiting" },
	{ 1, "Enable HLAT" },
	{ 2, "EPT Paging-Write Control" },
	{ 3, "Guest-Paging Verification" }
};


/*
 * IA32_VMX_EXIT_CTLS : 0x483
 * VM-Exit Controls
 * SDM volume 3 System Programming Guide
 * Section 24.7.1 VM-Exit Controls
 * Table 24-13. Definitions of Primary VM-Exit Controls
 * Page 3756
 */
struct capability_info exit_ctls[17] =
{
	{ 2, "Save Debug Controls" },
	{ 9, "Host Address-Space Size" },
	{ 12, "Load IA32_PERF_GLOBAL_CTRL" },
	{ 15, "Acknowledge Interrupt On Exit" },
	{ 18, "Save IA32_PAT" },
	{ 19, "Load IA32_PAT" },
	{ 20, "Save IA32_EFER" },
	{ 21, "Load IA32_EFER" },
	{ 22, "Save VMX-Preemption Timer Value" },
	{ 23, "Clear IA32_BNDCFGS" },
	{ 24, "Conceal VMX from PT" },
	{ 25, "Clear IA32_RTIT_CTL" },
	{ 26, "Clear IA32_LBR_CTL" },
	{ 28, "Load CET State" },
	{ 29, "Load PKRS" },
	{ 30, "Save IA32_PERF_GLOBAL_CTL" },
	{ 31, "Activate Secondary Controls" }
};

/*
 * IA32_VMX_ENTRY_CTLS : 0x484
 * VM-Entry Controls
 * SDM volume 3 System Programming Guide
 * Section 24.8.1 VM-Entry Controls 
 * Table 24-15. Definitions of VM-Entry Controls
 * Page 3758
 */
struct capability_info entry_ctls[13] =
{
	{ 2, "Load Debug Controls" },
	{ 9, "IA-32e Mode Guest" },
	{ 10, "Entry To SMM" },
	{ 11, "Deactivate Dualmonitor Treatment" },
	{ 13, "Load IA32_PERF_GLOBA L_CTRL" },
	{ 14, "Load IA32_PAT" },
	{ 15, "Load IA32_EFER" },
	{ 16, "Load IA32_BNDCFGS" },
	{ 17, "Conceal VMX From PT" },
	{ 18, "Load IA32_RTIT_CTL" },
	{ 20, "Load CET State" },
	{ 21, "Load Guest IA32_LBR_CTL" },
	{ 22, "Load PKRS" }
};

/*
 * report_capability
 *
 * Reports capabilities present in 'cap' using the corresponding MSR values
 * provided in 'lo' and 'hi'.
 *
 * Parameters:
 *  cap: capability_info structure for this feature
 *  len: number of entries in 'cap'
 *  lo: low 32 bits of capability MSR value describing this feature
 *  hi: high 32 bits of capability MSR value describing this feature
 */
void
report_capability(struct capability_info *cap, uint8_t len, uint32_t lo,
    uint32_t hi)
{
	uint8_t i;
	struct capability_info *c;
	char msg[MAX_MSG];

	memset(msg, 0, sizeof(msg));

	for (i = 0; i < len; i++) {
		c = &cap[i];
		snprintf(msg, 127, "%d  %s: Can set=%s, Can clear=%s\n",
		    c->bit,
			c->name,
		    (hi & (1 << c->bit)) ? "Yes" : "No",
		    !(lo & (1 << c->bit)) ? "Yes" : "No");
		printk(msg);
	}
}

/*
 * detect_vmx_features
 *
 * Detects and prints VMX capabilities of this host's CPU.
 */
void
detect_vmx_features(void)
{
	uint32_t lo, hi;

	/* Pin-Based VM-Execution Controls (5) */
	printk(KERN_INFO "Printing Pin-Based VM-Execution Controls... \n");
	rdmsr(IA32_VMX_PINBASED_CTLS, lo, hi);
	pr_info("Pin-Based VM-Execution Controls MSR: 0x%llx\n",
		(uint64_t)(lo | (uint64_t)hi << 32));
	report_capability(pin_based_exe_ctls, 5, lo, hi);

	/* Processor-Based VM-Execution Controls - Primary (22) */
	printk(KERN_INFO "Printing Primary Processor-Based VM-Execution Controls... \n");
	rdmsr(IA32_VMX_PROCBASED_CTLS, lo, hi);
	pr_info("Primary Processor-Based VM-Execution Controls MSR: 0x%llx\n",
		(uint64_t)(lo | (uint64_t)hi << 32));
	report_capability(proc_p_based_exe_ctls, 22, lo, hi);

	/* Validation Check For Printing Secondary Processor-Based VM-Execution Controls */
	/* proc_p_based_exe_ctls[21] = { 31, "Activate Secondary Controls" } */
	if (hi & (1 << 31)) {
		/* Processor-Based VM-Execution Controls - Secondary (28) */
		printk(KERN_INFO "Printing Secondary Processor-Based VM-Execution Controls...\n");
		rdmsr(IA32_VMX_PROCBASED_CTLS2, lo, hi);
		pr_info("Secondary Processor-Based VM-Execution Controls MSR: 0x%llx\n",
			(uint64_t)(lo | (uint64_t)hi << 32));
		report_capability(proc_s_based_exe_ctls, 28, lo, hi);
	}
	else {
		printk(KERN_INFO "Secondary Processor-Based VM-Execution Controls Printing Is Skiped As It Is Not Activated... \n");
	}

	/* Validation Check For Printing Tertiary Processor-Based VM-Execution Controls */
	/* proc_p_based_exe_ctls[9] = { 17, "Activate Tertiary Controls" } */
	if (hi & (1 << 17)) {
		/* Processor-Based VM-Execution Controls - Tertiary (4) */
		printk(KERN_INFO "Printing Tertiary Processor-Based VM-Execution Controls... \n");
		rdmsr(IA32_VMX_PROCBASED_CTLS3, lo, hi);
		pr_info("Tertiary Processor-Based VM-Execution Controls MSR: 0x%llx\n",
			(uint64_t)(lo | (uint64_t)hi << 32));
		report_capability(proc_t_based_exe_ctls, 4, lo, hi);	
	}
	else {
		printk(KERN_INFO "Tertiary Processor-Based VM-Execution Controls Printing Is Skiped As It Is Not Activated... \n");
	}

	/* VM-Exit Controls (17) */
	printk(KERN_INFO "Printing VM-Exit Controls... \n");
	rdmsr(IA32_VMX_EXIT_CTLS, lo, hi);
	pr_info("VM-Exit Controls MSR: 0x%llx\n",
		(uint64_t)(lo | (uint64_t)hi << 32));
	report_capability(exit_ctls, 17, lo, hi);

	/* VM-Entry Controls (13) */
	printk(KERN_INFO "Printing VM-Entry Controls... \n");
	rdmsr(IA32_VMX_ENTRY_CTLS, lo, hi);
	pr_info("VM-Entry Controls: 0x%llx\n",
		(uint64_t)(lo | (uint64_t)hi << 32));
	report_capability(entry_ctls, 13, lo, hi);	

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
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

/*
 * cleanup_module
 *
 * Function called on module unload
 */
void
cleanup_module(void)
{
	printk(KERN_INFO "CMPE 283 Assignment 1 Module Exits\n");
}

MODULE_LICENSE("GPL");
