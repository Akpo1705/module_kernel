#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h> 

MODULE_LICENSE("Dual BSD/GPL");

/* GPIO registers base address. */
#define BCM2708_PERI_BASE   (0x3F000000)
#define GPIO_BASE           (BCM2708_PERI_BASE + 0x200000)

/* GPIO registers */
struct S_GPIO_REGS
{
      uint32_t GPFSEL[6];
      uint32_t Reserved0;
      uint32_t GPSET[2];
      uint32_t Reserved1;
      uint32_t GPCLR[2];
      uint32_t Reserved2;
      uint32_t GPLEV[2];
      uint32_t Reserved3;
      uint32_t GPEDS[2];
      uint32_t Reserved4;
      uint32_t GPREN[2];
      uint32_t Reserved5;
      uint32_t GPFEN[2];
      uint32_t Reserved6;
      uint32_t GPHEN[2];
      uint32_t Reserved7;
      uint32_t GPLEN[2];
      uint32_t Reserved8;
      uint32_t GPAREN[2];
      uint32_t Reserved9;
      uint32_t GPAFEN[2];
      uint32_t Reserved10;
      uint32_t GPPUD;
      uint32_t GPPUDCLK[2];
      uint32_t Reserved11[4];
} *gpio_regs;

/* GPIO pins available on connector p1 */
typedef enum {GPIO_02 = 2,
              GPIO_03 = 3,
              GPIO_04 = 4,
              GPIO_05 = 5,
              GPIO_06 = 6,
              GPIO_07 = 7,
              GPIO_08 = 8,
              GPIO_09 = 9,
              GPIO_10 = 10,
              GPIO_11 = 11,
              GPIO_12 = 12,
              GPIO_13 = 13,
              GPIO_14 = 14,
              GPIO_15 = 15,
              GPIO_16 = 16,
              GPIO_17 = 17,
              GPIO_18 = 18,
              GPIO_19 = 19,
              GPIO_20 = 20,
              GPIO_21 = 21,
              GPIO_22 = 22,
              GPIO_23 = 23,
              GPIO_24 = 24,
              GPIO_25 = 25,
              GPIO_26 = 26,
              GPIO_27 = 27} GPIO;

/* GPIO Pin Pull-up/down */
typedef enum {PULL_NONE = 0,
              PULL_DOWN = 1,
              PULL_UP = 2} PUD;

/* GPIO Pin Alternative Function selection */
// By default GPIO pin is being used as an INPUT
typedef enum {GPIO_INPUT     = 0b000,
              GPIO_OUTPUT    = 0b001,
              GPIO_ALT_FUNC0 = 0b100,
              GPIO_ALT_FUNC1 = 0b101,
              GPIO_ALT_FUNC2 = 0b110,
              GPIO_ALT_FUNC3 = 0b111,
              GPIO_ALT_FUNC4 = 0b011,
              GPIO_ALT_FUNC5 = 0b010,} FSEL;

/*
 * SetGPIOFunction function
 *  Parameters:
 *   pin   - number of GPIO pin;
 *
 *   code  - alternate function code to which the GPIO pin is to be set
 *  Operation:
 *   Based on the specified GPIO pin number and function code, sets the GPIO pin to
 *   operate in the desired function. Each of the GPIO pins has at least two alternative functions.
 */
void SetGPIOFunction(GPIO pin, FSEL code)
{
    int regIndex = pin / 10;
    int bit = (pin % 10) * 3;

    unsigned oldValue = gpio_regs->GPFSEL[regIndex];
    unsigned mask = 0b111 << bit;

    gpio_regs->GPFSEL[regIndex] = (oldValue & ~mask) | ((code << bit) & mask);
}

/* PWM registers base address */
#define PWM_BASE (BCM2708_PERI_BASE + 0x20C000)
#define PWM_CLK_BASE (BCM2708_PERI_BASE + 0x101000)
#define PWMCLK_CTL  40
#define PWMCLK_DIV  41

/* PWM registers */
struct S_PWM_REGS
{
    uint32_t CTL;
    uint32_t STA;
    uint32_t DMAC;
    uint32_t reserved0;
    uint32_t RNG1;
    uint32_t DAT1;
    uint32_t FIF1;
    uint32_t reserved1;
    uint32_t RNG2;
    uint32_t DAT2;
} *pwm_regs;

struct S_PWM_CTL {
    unsigned PWEN1 : 1;
    unsigned MODE1 : 1;
    unsigned RPTL1 : 1;
    unsigned SBIT1 : 1;
    unsigned POLA1 : 1;
    unsigned USEF1 : 1;
    unsigned CLRF1 : 1;
    unsigned MSEN1 : 1;
    unsigned PWEN2 : 1;
    unsigned MODE2 : 1;
    unsigned RPTL2 : 1;
    unsigned SBIT2 : 1;
    unsigned POLA2 : 1;
    unsigned USEF2 : 1;
    unsigned Reserved1 : 1;
    unsigned MSEN2 : 1;
    unsigned Reserved2 : 16;
} *pwm_ctl;

struct S_PWM_STA {
    unsigned FULL1 : 1;
    unsigned EMPT1 : 1;
    unsigned WERR1 : 1;
    unsigned RERR1 : 1;
    unsigned GAPO1 : 1;
    unsigned GAPO2 : 1;
    unsigned GAPO3 : 1;
    unsigned GAPO4 : 1;
    unsigned BERR : 1;
    unsigned STA1 : 1;
    unsigned STA2 : 1;
    unsigned STA3 : 1;
    unsigned STA4 : 1;
    unsigned Reserved : 19;
} *pwm_sta;

volatile unsigned int *pwm_clk_regs; // Holds the address of PWM CLK registers

/*
 * Establish PWM frequency function
 *  Parameters:
 *   divi   - integer part of divisor.
 *  Operation:
 *   Based on the passed GPIO pin number and function code, sets the GPIO pin to
 *   operate the desired function. Each of the GPIO pins has at least two alternative functions.
 */
void pwm_frequency(uint32_t divi) {

    // Kill the clock
    *(pwm_clk_regs+PWMCLK_CTL) = 0x5A000020;

    // Disable PWM
    pwm_ctl->PWEN1 = 0;
    pwm_ctl->PWEN2 = 0;
    udelay(10);

    // Set the divisor
    *(pwm_clk_regs+PWMCLK_DIV) = 0x5A000000 | (divi << 12);

    // Set source to oscillator and enable clock
    *(pwm_clk_regs+PWMCLK_CTL) = 0x5A000011;
}

void set_up_pwm_channels(void){
    // Channel 1 set-up
    pwm_ctl->MODE1 = 0;
    pwm_ctl->RPTL1 = 0;
    pwm_ctl->SBIT1 = 0;
    pwm_ctl->POLA1 = 0;
    pwm_ctl->USEF1 = 0;
    pwm_ctl->CLRF1 = 1;
    pwm_ctl->MSEN1 = 1;

    // Channel 2 set-up
    pwm_ctl->MODE2 = 0;
    pwm_ctl->RPTL2 = 0;
    pwm_ctl->SBIT2 = 0;
    pwm_ctl->POLA2 = 0;
    pwm_ctl->USEF2 = 0;
    pwm_ctl->MSEN2 = 1;
}

void pwm_ratio_c1(unsigned n, unsigned m) {

    // Disable PWM Channel 1
    pwm_ctl->PWEN1 = 0;

    // Set the PWM Channel 1 Range Register
    pwm_regs->RNG1 = m;
    // Set the PWM Channel 1 Data Register
    pwm_regs->DAT1 = n;

    // Check if PWM Channel 1 is not currently transmitting
    if ( !pwm_sta->STA1 ) {
        if ( pwm_sta->RERR1 ) pwm_sta->RERR1 = 1; // Clear RERR bit if read occured on empty FIFO while channel was transmitting
        if ( pwm_sta->WERR1 ) pwm_sta->WERR1 = 1; // Clear WERR bit if write occured on full FIFO while channel was transmitting
        if ( pwm_sta->BERR ) pwm_sta->BERR = 1; // Clear BERR bit if write to registers via APB occured while channel was transmitting
    }
    udelay(10);

    // Enable PWM Channel 1
    pwm_ctl->PWEN1 = 1;
}

void pwm_ratio_c2(unsigned n, unsigned m) {

    // Disable PWM Channel 2
    pwm_ctl->PWEN2 = 0;

    // Set the PWM Channel 2 Range Register
    pwm_regs->RNG2 = m;
    // Set the PWM Channel 2 Data Register
    pwm_regs->DAT2 = n;

    // Check if PWM Channel 2 is not currently transmitting
    if ( !pwm_sta->STA2 ) {
        if ( pwm_sta->RERR1 ) pwm_sta->RERR1 = 1; // Clear RERR bit if read occured on empty FIFO while channel was transmitting
        if ( pwm_sta->WERR1 ) pwm_sta->WERR1 = 1; // Clear WERR bit if write occured on full FIFO while channel was transmitting
        if ( pwm_sta->BERR ) pwm_sta->BERR = 1; // Clear BERR bit if write to registers via APB occured while channel was transmitting
    }
    udelay(10);

    // Enable PWM Channel 2
    pwm_ctl->PWEN2 = 1;
}


/* Declaration of my_pwm_driver.c functions */
int my_pwm_driver_init(void);
void my_pwm_driver_exit(void);
static int my_pwm_driver_open(struct inode *, struct file *);
static int my_pwm_driver_release(struct inode *, struct file *);
static ssize_t my_pwm_driver_read(struct file *, char *buf, size_t , loff_t *);
static ssize_t my_pwm_driver_write(struct file *, const char *buf, size_t , loff_t *);
static long my_pwm_driver_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Structure that declares my_pwm_driver file operations */
struct file_operations my_pwm_driver_fops =
{
    open            :   my_pwm_driver_open,
    release         :   my_pwm_driver_release,
    read            :   my_pwm_driver_read,
    write           :   my_pwm_driver_write
};

/* Declaration of the init and exit functions. */
module_init(my_pwm_driver_init);
module_exit(my_pwm_driver_exit);

/* Major number. */
int my_pwm_driver_major;


int my_pwm_driver_init(void)
{
    int result = -1;

    printk(KERN_INFO "Inserting my_pwm_driver module..\n");

    /* Registering device. */
    result = register_chrdev(0, "my_pwm_driver", &my_pwm_driver_fops);
    if (result < 0)
    {
        printk(KERN_INFO "my_pwm_driver: cannot obtain major number %d\n", my_pwm_driver_major);
        return result;
    }

    my_pwm_driver_major = result;
    printk(KERN_INFO "my_pwm_driver major number is %d\n", my_pwm_driver_major);

    // Map the GPIO register space from PHYSICAL address space to VIRTUAL address space
    gpio_regs = (struct S_GPIO_REGS *)ioremap(GPIO_BASE, sizeof(struct S_GPIO_REGS));
    if(!gpio_regs)
    {
        result = -ENOMEM;
        goto fail_no_virt_mem;
    }

    // Map the PWM register space from PHYSICAL address space to VIRTUAL address space
    pwm_regs = (struct S_PWM_REGS *)ioremap(PWM_BASE, sizeof(struct S_PWM_REGS));
    if(!pwm_regs)
    {
        result = -ENOMEM;
        goto fail_no_virt_mem;
    }
    pwm_ctl = (struct S_PWM_CTL *) &pwm_regs -> CTL;
    pwm_sta = (struct S_PWM_STA *) &pwm_regs -> STA;

    // Map the PWM Clock register space from PHYSICAL address space to VIRTUAL address space
    pwm_clk_regs = ioremap(PWM_CLK_BASE, 4096);
    if(!pwm_clk_regs)
    {
        result = -ENOMEM;
        goto fail_no_virt_mem;
    }

    // Setting the GPIO pins alternative functions to PWM
    SetGPIOFunction(GPIO_26, GPIO_ALT_FUNC0); // Setting GPIO_12 pin to alternative function 0 - PWM channel 0
    SetGPIOFunction(GPIO_23, GPIO_ALT_FUNC0); // Setting GPIO_13 pin to alternative function 0 - PWM channel 1
    //SetGPIOFunction(GPIO_18, GPIO_ALT_FUNC5); // Setting GPIO_18 pin to alternative function 5 - PWM channel 0
    //SetGPIOFunction(GPIO_19, GPIO_ALT_FUNC5); // Setting GPIO_19 pin to alternative function 5 - PWM channel 1

    // Set up PWM channels
    set_up_pwm_channels();

    // Setting PWM with approx 1kHz frequency and fine tuning with 0.1% duty cycle step
    // PWM frequency can be calculated with formula pwmFrequency in Hz = 19200000Hz / divi / pwm_range.
    pwm_frequency(19); 
    pwm_ratio_c1(200, 1000);
    //pwm_ratio_c2(500, 1000);

    return 0;

fail_no_virt_mem:

    // Unmap the GPIO registers PHYSICAL address space from VIRTUAL memory
    if (gpio_regs)
        iounmap(gpio_regs);
    // Unmap the PWM registers PHYSICAL address space from VIRTUAL memory
    if (pwm_regs)
        iounmap(pwm_regs);
    // Unmap the PWM Clock registers PHYSICAL address space from VIRTUAL memory
    if (pwm_clk_regs)
        iounmap(pwm_clk_regs);

    /* Freeing the major number. */
    unregister_chrdev(my_pwm_driver_major, "my_pwm_driver");

    return result;
}

void my_pwm_driver_exit(void)
{
    // Clearing the GPIO pins - setting to LOW
    gpio_regs->GPCLR[12/32] |= (1 << (12 % 32));
    gpio_regs->GPCLR[13/32] |= (1 << (13 % 32));
    gpio_regs->GPCLR[18/32] |= (1 << (18 % 32));
    gpio_regs->GPCLR[19/32] |= (1 << (19 % 32));

    // Setting the GPIO pins to default function - as INPUT
    SetGPIOFunction(GPIO_26, GPIO_INPUT);
    SetGPIOFunction(GPIO_13, GPIO_INPUT);
    //SetGPIOFunction(GPIO_18, GPIO_INPUT);
    //SetGPIOFunction(GPIO_19, GPIO_INPUT);

    // Unmap the GPIO registers PHYSICAL address space from VIRTUAL memory
    if (gpio_regs)
        iounmap(gpio_regs);
    // Unmap the PWM registers PHYSICAL address space from VIRTUAL memory
    if (pwm_regs)
        iounmap(pwm_regs);
    // Unmap the PWM Clock registers PHYSICAL address space from VIRTUAL memory
    if (pwm_clk_regs)
        iounmap(pwm_clk_regs);

    printk(KERN_INFO "Removing my_pwm_driver module\n");

    /* Freeing the major number. */
    unregister_chrdev(my_pwm_driver_major, "my_pwm_driver");
}

static int my_pwm_driver_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int my_pwm_driver_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t my_pwm_driver_read(struct file *filp, char *buf, size_t len, loff_t *f_pos)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");

    return -EPERM; // Operation not permitted error
}

static ssize_t my_pwm_driver_write(struct file *filp, const char *buf, size_t len, loff_t *f_pos)
{
    printk(KERN_ALERT "Sorry, this operation isn't supported.\n");

    return -EPERM; // Operation not permitted error
}