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
		i: INTEGER
	do
	
		-- cat(2+2);
		
		FROM
			--i := 0
		UNTIL
			not true
		LOOP
			--i := i+1;
		END
		
		IF "a" < "b" THEN
			Io.put_string("a < b");
		ELSEIF "a" > "b" THEN
			Io.put_string("a > b");
		ELSE
			Io.put_string("a = b");
		END
	
		--cat("Meow");
		--Io.put_string("Hello world!!");
		-- Io.put_integer(arr[i]);
	end

end

class ARRAY_TEST
create
	make

feature
	i: INTEGER
	a: ARRAY[INTEGER]
	b: ARRAY[String]
	make
	local
		i0: INTEGER
		s: BUBBLE
	do
		CREATE s -- `make` is called
--		if s.ascending then    end
		s.init
		
		-- io.put_string("Make array!");
		CREATE self.a.make(0,17);
			io.put_integer(a.count);
			io.new_line;
		i := 1
		a[i] := 123;
		i := 0
		a[i] := 456;
			Io.put_integer(a[i]);
		Current.i := 1
			Io.put_integer(a[i]);
			io.new_line;
		CREATE Current.b.make(0,13)
		b[4] := "my String"
		io.put_integer(b.count)
		io.new_line
		io.put_string(b[4])
	end
	
	self: ARRAY_TEST
	do
		Result := Current
	end
end

class
	SORT_ALG

feature {NONE}
	init
	do

	end
feature {}
	bubble(arr : ARRAY[INTEGER] ; ascending: BOOLEAN) : ARRAY[INTEGER]
	do
			Result := arr
	end
end

class
	SORTER

 inherit
 	SORT_ALG redefine init end

feature {ANY}
	init
	do

	end

feature {none}
	ascending: BOOLEAN

feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		i, buf: INTEGER
	do
		IF ascending THEN
			Result := arr
		ELSE
			Result := arr
		END
	end
end

class
	BUBBLE

inherit
	SORTER  redefine
		sort --, init
		 end

feature {NONE}
	--init	do	end
feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		i, buf: INTEGER
	do
		IF ascending THEN
			Result := bubble(arr, false)
		ELSE
			Result := arr
		END
	end
end
