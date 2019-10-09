for file in `ls misc/files/*.avm | sort -V`
do
	echo $file
	./avm "$file"
	echo
done
