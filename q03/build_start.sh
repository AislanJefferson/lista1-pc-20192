#!/bin/bash
echo "Compilando o codigo fonte..."
echo "- Compilando ex3_p"
gcc ex3_p.c -o ex3_p
gcc ex3_t.c -o ex3_t
echo "Executando os binarios"
echo " "
/usr/bin/time ./ex3_p $1
echo " "
/usr/bin/time ./ex3_t $1
