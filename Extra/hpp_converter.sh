find . -name '*.hpp' -and -not -path '*ThirdParty_Librarys*'  | while read line; do
    	filename=$(basename "$line")
	dir=$(dirname "$line")
	extension="${filename##*.}"
	des_extension="hpp"
	file="${filename%.*}"
	
	if [ "$extension" == "$des_extension" ]; then
		if [ ! -f "$dir/$file.cpp" ]; then
			echo "-------------------------------------------------------"
			echo "Processing header file: $dir/$file.$extension"
			echo "    adding: #include <$file.hpp> to file: $dir/$file.cpp"
			echo "#include <$file.hpp>" > "$dir/$file.cpp"
		else
			echo "File: $dir/$file.cpp already exists!"
		fi
	fi
done

