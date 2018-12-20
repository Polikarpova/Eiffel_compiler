class HELLO_WORLD
 
create
	make

feature
	cat (str: STRING)
	LOCAL
		int_var: INTeger
		-- class: ARRAY_TEST
	do
		Io.put_string(str)
		str := "AAAAAAAAAAAAAAAAA!"
		-- CREATE class.make
		-- Io.new_line
		-- Io.put_string(str)
		-- Io.new_line
	end

	make
	local
		isOk : BOOLEAN
	do
		meow(2+2);
		
		--isOk := NOT true;
		
		IF NOT true THEN
			Io.put_string("isOk");
		ELSE
			Io.put_string("!isOk");
		END
		
--		IF "a" < "b" THEN
--			Io.put_string("a < b");
--		ELSEIF "a" > "b" THEN
--			Io.put_string("a > b");
--		ELSE
--			Io.put_string("a = b");
--		END
	
		--cat("Meow");
		--Io.put_string("Hello world!!");
		-- Io.put_integer(arr[i]);
	end

end

class ARRAY_TEST
create
	make

feature
	a: ARRAY[INTEGER]

	make
	do
		-- io.put_string("Make array!");
		CREATE self.a.make(0,17);
		-- io.new_line;
		io.put_integer(a.count);
		-- String[] b;
		-- b = new String[13];
		-- b[4] = "my String";
		-- io.new_line();
		-- io.put_integer(b.length);
		-- io.new_line();
		-- io.put_string(b[4]);
	end
	
	self: ARRAY_TEST
	do
		Result := Current
	end
end