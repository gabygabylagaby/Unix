#!/bin/bash

# clase 2

echo "Running script at "  ´date´

echo "Enter directory path"
read dir_path
echo "Content of the directory"
ls $dir_path
find $dir_path -name '*.log'


if [[  -lt  -gt  >  <]]; then 
    # code
    
fi



# clase 2.2
#!/bin/bash

echo "Running script at "  ´date´

echo "Enter directory path"
read dir_path
echo "Content of the directory"
ls $dir_path
echo $1
echo $2

# aqui clase 3 de bash



a = 1
b = 2
c = 3


if [$a -lt $b -a $c -gt $b]
then 
echo "conditional true"
else
echo "conditional false"
fi

i= 0 
while [$i -lt 10]
do
echo "counter at $1"
sleep 1
i = $((i+1))
if [&i -eq 5];
then
echo "counter at 5, next round"
continue
fi
echo "end of iteration"
done
fi
done

for j in 1 6 2 3 1 5
do
echo "counter at $j"
done

for k in {1..10}; do
echo "counter k at $k"
if [[k == 7]]; then
echo "counter at 7, next round"
fi
echo "end of iteration, next elements"
done

for ((c=0; c<12; c++)) do
echo "counter at $c"
done


for file in /etc/*.cont
do
if [[ -f ${file}.cont ]]; then
echo "file found at $file"
fi
done

