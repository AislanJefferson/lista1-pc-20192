#!/bin/bash
echo "Compilando o codigo fonte..."
echo "- Compilando ex3_p"
gcc ex3_p.c -o ex3_p
gcc -pthread ex3_t.c -o ex3_t
echo "Executando os binarios"
echo " "
if [ "$(uname)" == "Darwin" ]; then
   args=-l
else
   args=-v
fi
/usr/bin/time $args ./ex3_p $1
echo " "
/usr/bin/time $args ./ex3_t $1
