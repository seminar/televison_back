#!/bin/bash



i=0

cat temp | while read line
do	
	echo "$line"
	if [ -f "$line" ];
		then

		i=$[$i+1]
		i=20
		echo $i
		tar cpf - "${line}" | tar xpf - -C ./
        if [ "$i" = "20" ];
        	then
    		echo $line $i
    		git pull origin master
			git add -A
			git commit  -a -m "[DTV-UPDAE] "$line" "
			git push origin master
			i=20
		fi
	fi
done