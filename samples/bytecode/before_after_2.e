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
		aa.setBool( false );
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
		aa.setBool( true );
		arr[0] := 10;
		arr[1] := 10;
		-- ошибочные присваивания:
		i := 666;
		CREATE arr.make(0,1); 
		arr.count := 123;
		aa.getBool := true;
		true := aa.getBool;
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

feature {ANY}
	isBool : BOOLEAN

	init -- creator
	do
		isBool := false;
	end
	setBool(b: BOOLEAN) 
	do
		isBool := b;
	end
	getBool : BOOLEAN
	do
		Result := isBool;
	end
end