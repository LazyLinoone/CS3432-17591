start:
addi x5, x0, 2
sw   x5, 0(x0)
addi x5, x5, 4
sw   x5, 4(x0)
lw   x6, 0(x0)
lw   x7, 0(x0)
addi x5, x0, 3
sub  x8, x6, x7
and  x9, x5, x8
loop:
beq  x5, x0, start
addi x5, x5, -1
beq  x0, x0, loop 