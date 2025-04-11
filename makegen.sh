#!/bin/bash

echo "Generating Makefile in root directory..."
echo -e "clean:\n\trm -f *.o *.out *.exe *.bin" > Makefile

for file in *.c; do
  [ -e "$file" ] || continue
  name=$(basename "$file" .c)
  echo -e "\n$name: $file\n\tgcc $file -o $name" >> Makefile
done

for dir in */; do
  cd "$dir" || continue
  echo "Generating Makefile in $dir..."

  echo -e "clean:\n\trm -f *.o *.out *.exe *.bin" > Makefile

  for file in *.c; do
    [ -e "$file" ] || continue
    name=$(basename "$file" .c)
    echo -e "\n$name: $file\n\tgcc $file -o $name" >> Makefile
  done

  cd ..
done