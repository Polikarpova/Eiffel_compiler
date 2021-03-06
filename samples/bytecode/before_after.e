class EIFFEL_TEST
create
	make

feature
	
	make
	local
		i : INTEGER
		aa:A
		arr: ARRAY[INTEGER]
	do

		CREATE aa.init
		aa.isBool := false
		i := 3;
		CREATE arr.make(0,1);
		arr[0] := 9;
		arr[1] := 9;
		
		Io.put_string("BEFORE:%N");
		
		Io.put_boolean(aa.isBool);
		Io.new_line
		Io.put_integer(i)
		print_arr(arr)
		
		Io.put_string("%N%N%NAFTER:%N");
		func(aa, i, arr);
		
		Io.put_boolean(aa.isBool);
		Io.new_line
		Io.put_integer(i)
		print_arr(arr)
	end
	
	func(aa:A; i:INTEGER; arr: ARRAY[INTEGER])
	do
		aa.isBool := true;
		i := 666;
		arr[0] := 10;
		arr[1] := 10;
	end
	
	print_arr(arr:ARRAY[INTEGER])
	local
		i: INTEGER
	do
		FROM
			i := 0
		UNTIL
			i >= arr.count
		LOOP
			Io.put_string("%NElement ");
			Io.put_integer(i);
			Io.put_string(": ");
			Io.put_integer(arr[i]);

			i := i + 1;
		end
	end
end

class A

create
	init

feature
	isBool : BOOLEAN
	
	init -- creator
	do
		isBool := false;
	end
end