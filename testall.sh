for file in `ls tests/*.avm | sort -V`
do
	echo $file
	./avm "$file"
	echo
done
