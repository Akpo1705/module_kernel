cmd_/home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/14_thread/Module.symvers := sed 's/ko$$/o/' /home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/14_thread/modules.order | scripts/mod/modpost -m -a   -o /home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/14_thread/Module.symvers -e -i Module.symvers   -T -