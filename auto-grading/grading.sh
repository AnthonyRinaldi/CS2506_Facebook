#!/bin/bash

points=0
INTERACTIVE=1
FILE=1

IFS="
"

printf "\n\n\033[1;37;44mCOMPILING PROGRAM"
tput sgr0
printf "\n"

cd ..
gcc *.c -o social_network -Wall -Werror
if [ $? = 0 ]; then
	echo -e "\033[1;32mCompilaion Successful"
	tput sgr0
	cp social_network auto-grading/
	cd auto-grading
else
	echo -e "\033[1;31mCompilaion Error. There are warnings in your program. Please fix this or you will lose 10 points. Recomiping without treating warnings as errors ..."
	tput sgr0
	points=$((points - 10))
	gcc *.c -o social_network -Wall
	if [ $? = 0 ]; then
		echo -e "\033[1;32mCompilaion Successful with warnings"
		echo -e "\033[1;33mDo you want to continue grading or exit to fix the warnings? Enter yes to continue and no to exit:"
        	tput sgr0
		read choice </dev/tty
		if [ $choice = "yes" ]; then
        		cp social_network auto-grading/
        		cd auto-grading
		else
			exit 1
		fi
	else
		echo -e "\033[1;31mCompilaion Error."
        	tput sgr0
		exit 1
	fi
fi


echo "Your initial points = $points"


if [ $INTERACTIVE = 1 ]; then
printf "\n\n\033[1;37;44mINTERACTIVE GRADING STARTS" 
tput sgr0
printf "\n"

#read test </dev/tty

for (( index=1; index<41; index=index+1 )); do

./social_network -i > student_out << EOF
`cat test_cases/error$index.txt`
EOF

if [ $? != 0 ]; then
	echo -e "\033[0;31mYour program crashed while executing this FILE: test_cases/error$index in interactive mode. Do you want to continue[y] or stop[n]? [y/n]:"
	tput sgr0
	read choice </dev/tty
	if [ $choice = n ]; then
		echo -e "\033[1;33mpoints earned so far = $points"
		tput sgr0
		exit 1
	fi
fi

./social_network_ta -i > ta_out << EOF
`cat test_cases/error$index.txt`
EOF

cmp -s student_out ta_out
if [ $? = 0 ]; then
	points=$(echo "$points + 0.5" | bc)
	printf "\n----------------------------------------------------------\n"
	echo -e "\033[0;32m\"FILE: test_cases/error$index\" (interactive) successfully executed. \033[1mTotal points = $points \033[0m"
	tput sgr0
else
	printf "\n-----------------------------------------------------------\n"
	echo -e "\033[0;31m\"FILE: test_cases/error$index\" (interactive) failed. The TA's implementation returned \033[0;35m"
	cat ta_out
	echo -e "\033[0;31mand your implementation retuned \033[0;36m"
	cat student_out
	tput sgr0
	echo -e "\033[1;33mDo you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
		echo -e "\033[1;33mYou can see your program's output in the file student_out and the TA's output in the file ta_out. Points earned so far = $points"
		tput sgr0
                exit 1
        fi
fi	

rm ta_out
rm student_out

done

for (( index=1; index<61; index=index+1 )); do

./social_network -i > student_out << EOF
`cat test_cases/test$index.txt`
EOF

if [ $? != 0 ]; then
        echo -e "\033[0;31mYour program crashed while executing this FILE: test_cases/test$index in interactive mode. Do you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mpoints earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

./social_network_ta -i > ta_out << EOF
`cat test_cases/test$index.txt`
EOF

cmp -s student_out ta_out
if [ $? = 0 ]; then
        points=$(echo "$points + 0.5" | bc)
        printf "\n----------------------------------------------------------\n"
        echo -e "\033[0;32m\"FILE: test_cases/test$index\" (interactive) successfully executed. \033[1mTotal points = $points \033[0m"
        tput sgr0
else
        printf "\n-----------------------------------------------------------\n"
        echo -e "\033[0;31m\"FILE: test_cases/test$index\" (interactive) failed. The TA's implementation returned \033[0;35m"
        cat ta_out
        echo -e "\033[0;31mand your implementation retuned \033[0;36m"
        cat student_out
        tput sgr0
        echo -e "\033[1;33mDo you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mYou can see your program's output in the file student_out and the TA's output in the file ta_out. Points earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

rm ta_out
rm student_out

done

fi



if [ $FILE = 1 ]; then
printf "\n\n\033[1;37;44mFILE MODE GRADING STARTS"
tput sgr0
printf "\n"


for (( index=1; index<41; index=index+1 )); do

./social_network -f test_cases/error$index.txt student_out

if [ $? != 0 ]; then
        echo -e "\033[0;31mYour program crashed while executing this FILE: test_cases/error$index in file mode. Do you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mpoints earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

./social_network_ta -f test_cases/error$index.txt ta_out

cmp -s student_out ta_out
if [ $? = 0 ]; then
        points=$(echo "$points + 0.5" | bc)
        printf "\n----------------------------------------------------------\n"
        echo -e "\033[0;32m\"FILE: test_cases/error$index\" (file) successfully executed. \033[1mTotal points = $points \033[0m"
        tput sgr0
else
        printf "\n-----------------------------------------------------------\n"
        echo -e "\033[0;31m\"FILE: test_cases/error$index\" (file) failed. The TA's implementation returned \033[0;35m"
        cat ta_out
        echo -e "\033[0;31mand your implementation retuned \033[0;36m"
        cat student_out
        tput sgr0
        echo -e "\033[1;33mDo you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mYou can see your program's output in the file student_out and the TA's output in the file ta_out. Points earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

rm ta_out
rm student_out

done


for (( index=1; index<61; index=index+1 )); do

./social_network -f test_cases/test$index.txt student_out

if [ $? != 0 ]; then
        echo -e "\033[0;31mYour program crashed while executing this FILE: test_cases/test$index in file mode. Do you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mpoints earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

./social_network_ta -f test_cases/test$index.txt ta_out

cmp -s student_out ta_out
if [ $? = 0 ]; then
        points=$(echo "$points + 0.5" | bc)
        printf "\n----------------------------------------------------------\n"
        echo -e "\033[0;32m\"FILE: test_cases/test$index\" (file) successfully executed. \033[1mTotal points = $points \033[0m"
        tput sgr0
else
        printf "\n-----------------------------------------------------------\n"
        echo -e "\033[0;31m\"FILE: test_cases/test$index\" (file) failed. The TA's implementation returned \033[0;35m"
        cat ta_out
        echo -e "\033[0;31mand your implementation retuned \033[0;36m"
        cat student_out
        tput sgr0
        echo -e "\033[1;33mDo you want to continue[y] or stop[n]? [y/n]:"
        tput sgr0
        read choice </dev/tty
        if [ $choice = n ]; then
                echo -e "\033[1;33mYou can see your program's output in the file student_out and the TA's output in the file ta_out. Points earned so far = $points"
                tput sgr0
                exit 1
        fi
fi

rm ta_out
rm student_out

done


fi



