```c++
/* execve (system call) execution flow - Linux Kernel v5.0 */

SYSCALL_DEFINE3(execve){
    do_execve(filename, __argv, __envp){
        struct user_arg_ptr argv = { .ptr.native = __argv };
        struct user_arg_ptr envp = { .ptr.native = __envp };
        do_execveat_common(AT_FDCWD, filename, argv, envp, 0){
            __do_execve_file(fd, filename, argv, envp, flags, NULL){ /* sys_execve() executes a new program. */
                struct linux_binprm *bprm; /* This structure is used to hold the arguments that are used when loading binaries. */
                bprm = kzalloc(sizeof(*bprm), GFP_KERNEL);
                prepare_bprm_creds(bprm){ /* Prepare credentials */
                    bprm->cred = prepare_exec_creds()
                }
                bprm->file = do_open_execat(fd, filename, flags);
                bprm_mm_init(bprm){  /* Create a new mm_struct and populate it with a temporary stack vm_area_struct. */
                    bprm->mm = mm = mm_alloc();
                    __bprm_mm_init(bprm){
                        bprm->vma = vma = vm_area_alloc(mm);
                        vma->vm_end = STACK_TOP_MAX;
                        vma->vm_start = vma->vm_end - PAGE_SIZE;
                        vma->vm_flags = VM_SOFTDIRTY | VM_STACK_FLAGS | VM_STACK_INCOMPLETE_SETUP;
                        vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
                    }
                }
                prepare_arg_pages(bprm, argv, envp);
                prepare_binprm(bprm){ /* Fill the binprm structure from the inode. Check permissions, then read the first 128 (BINPRM_BUF_SIZE) bytes.*/
                    bprm_fill_uid(bprm);
                    security_bprm_set_creds(bprm);
                    kernel_read(bprm->file, bprm->buf, BINPRM_BUF_SIZE, &pos);
                }
                copy_strings(bprm->envc, envp, bprm);
                copy_strings(bprm->argc, argv, bprm);

                exec_binprm(bprm){
                    search_binary_handler(bprm){ /* cycle the list of binary formats handler, until one recognizes the image */
                        load_elf_binary(bprm){ /* fmt->load_binary(bprm); */
                            elf_phdata = load_elf_phdrs();

                            elf_interpreter = kmalloc();
                            interpreter = open_exec(elf_interpreter);

                            interp_elf_phdata = load_elf_phdrs();  /* Load the interpreter program headers */

                            flush_old_exec(bprm); /* Flush all traces of the currently running executable */
                            setup_new_exec();
                            install_exec_creds(bprm){  /* commits the new creds */
                                commit_creds(bprm->cred);
                            }
                            setup_arg_pages();  /* Do this so that we can load the interpreter, if need be. */
                            current->mm->start_stack = bprm->p;

                            for (; i < loc->elf_ex.e_phnum; ) {  /* mmapping the ELF image into the correct location in memory */
                                elf_map(bprm->file, load_bias + vaddr, elf_ppnt, elf_prot, elf_flags, total_size);
                            }
                            
                            if (elf_interpreter)
                                elf_entry = load_elf_interp(&loc->interp_elf_ex, interpreter, &interp_map_addr, load_bias, interp_elf_phdata);
                            else
                                elf_entry = loc->elf_ex.e_entry;

                            current->mm->end_code = end_code;
                            current->mm->start_code = start_code;
                            current->mm->start_data = start_data;
                            current->mm->end_data = end_data;
                            current->mm->start_stack = bprm->p;

                            start_thread(regs, elf_entry /* new_ip */, bprm->p /* new_sp */){
                                regs->ip = new_ip;
                                regs->sp = new_sp;
                                force_iret();
                            }
                        }
                    }
                }
            }
        }
    }
}
```