#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/types.h>


static int nr = 1;


int main (int argc, char** argv)
{
	struct task_struct *task;
	task = find_task_by_pid((pid_t)nr);
	
	struct mm_struct *a_mm; 
	a_mm = task->active_mm;
	
	printk(KERN_INFO "taskinfo: START CODE SEGMENT ADDRESS –0x%08X\n", (u32)a_mm->start_code);
	printk(KERN_INFO "taskinfo:     END CODE SEGMENT ADDRESS –0x%08X\n", (u32)a_mm->end_code);
	printk(KERN_INFO "taskinfo: CODE SEGMENT LENGTH – 0x%08X\n",(u32)(a_mm->end_code – a_mm->start_code));
	
	return 0;
}