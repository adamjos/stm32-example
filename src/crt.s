.cpu cortex-m33
.thumb

.section .isr_vector, "a"
.global __vector_table
__vector_table:
    .word _stack_top
    .word reset_handler

.section .reset_handler, "ax"
.global reset_handler
.thumb_func
reset_handler:
    bl main
    b .
