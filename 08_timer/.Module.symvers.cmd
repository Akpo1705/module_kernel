cmd_/home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/08_timer/Module.symvers := sed 's/ko$$/o/' /home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/08_timer/modules.order | scripts/mod/modpost -m -a   -o /home/alex/test/rasspbery_pi2/kernel/5.10/module_kern/08_timer/Module.symvers -e -i Module.symvers   -T -
