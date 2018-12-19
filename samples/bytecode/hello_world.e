class HELLO_WORLD
 
create
	make

feature
	make
	do
		cat("Meow");
		Io.put_string("Hello world!!");
		-- Io.put_integer(arr[i]);
	end

	cat (str: STRING)
	LOCAL
		int_var: INTeger
	do
		Io.put_string(str)
		str := "AAAAAAAAAAAAAAAAA!"
		Io.new_line
		Io.put_string(str)
		Io.new_line
	end
end
