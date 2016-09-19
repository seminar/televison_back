#!/bin/bash


find $1 >temp
i=0

cat temp | while read line
do	
	if [ -f "$line" ];
		then

		i=%[$i+1]
		

		tar cpf - "${line}" | tar xpf - -C ./
        if [ "$i" = "20" ];
        	then
    		echo $line $i
    		git pull origin master
			git add -A
			git commit  -a -m "[DTV-UPDAE] "$line" "
			git push origin master
			i=0
		fi
	fi
done