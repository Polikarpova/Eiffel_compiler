class APPLICATION

create
	make

feature
	make
	do
		arr_test
	end
arr_test
	LOCAL
		i: INTEGER
		arr: ARRAY[INTEGER]
	do

		--создаем незаполненный массив на 4 элемента
		-- [obsolete] make(min_index, max_index)
		create arr.make(0,4);
		
		from
			-- нумерация идет по индексам как задано в конструкторе
			i := 0
		until
			i = 5
		loop
			Io.put_integer(i);
			Io.put_string(" : ");
			arr[i] :=  i+20
			Io.put_integer(arr[i]);
			Io.new_line
			i := i + 1;
		end

		Io.new_line
		arr[2] := 10;

		-- view
		from
			i := 0
		until
			i = 5
		loop
			Io.put_integer(i);
			Io.put_string(" : ");
			Io.put_integer(arr[i]);
			Io.new_line
			i := i + 1;
		end

	end
end
