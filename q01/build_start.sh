#!/bin/bash
build_dir="build/"
jar_filename="q01.jar"
if [ -d $build_dir ]; then
    rm -rf $build_dir $jar_filename
fi
mkdir $build_dir
javac -d ./$build_dir *.java
cd $build_dir
jar cvfe ../$jar_filename Main *
cd ../
rm -rf $build_dir
if [ -e $jar_filename ]; then
    echo "Executavel construido com sucesso"
else
    echo "Erro ao construir o executavel"
fi
echo "Executando binario da q01..."
java -jar $jar_filename
