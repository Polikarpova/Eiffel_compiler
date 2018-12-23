class EIFFEL_TEST
create
	make

feature
	worker : SORTER
	
	make
	local
		arr: ARRAY[INTEGER]
	do
		-- Io.put_string("CREATE arr.make(0, 5) ... %N");
		CREATE arr.make(0, 5)
		-- Io.put_string("CREATE worker.init ... %N");
		CREATE worker.init

		arr[0] := 44;
		arr[1] := 6^2;
		arr[2] := 24;
		arr[3] := 37;
		arr[4] := 5;
		arr[5] := 0;
		
		Io.put_string("Start array: %N");
		Io.put_string("%TElements count: ");
		Io.put_integer(arr.count);
		
		print_arr(arr);
		
		Io.put_string("%N%NSorting...%N%N");
		worker.reversed
		arr := worker.sort(arr);
		
		Io.put_string("%NDescend-sorted array: ");
		print_arr(arr);
		
		worker.init
		arr := worker.sort(arr);
		
		Io.put_string("%NSorted array: ");
		print_arr(arr);
		
	end
	
	print_arr(arr:ARRAY[INTEGER])
	local
		i: INTEGER
	do
		FROM
			i := 0
		UNTIL
			i < arr.count
		LOOP
			Io.put_string("%N%TElement ");
			Io.put_integer(i);
			Io.put_string(": ");
			Io.put_integer(arr[i]);
			
			i := i + 1;
		end
	end
	
end

class SORTER

create
	init

feature {EIFFEL_TEST}
	forwarded
	do
		ascending := true;
	end
	
	reversed
	do
		ascending := false;
	end

feature {none}
	init
	do
		forwarded
	end
	
	ascending: BOOLEAN

feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		worker: SORT_ALG
	do
		CREATE worker.make
		worker.bubble_sort(arr, ascending)
		Result := arr
	end
end

class SORT_ALG
create
	make

feature {ANY}
	make
	do end
	
	bubble_sort(arr:ARRAY[INTEGER] ; ascending: BOOLEAN)
	local
		buf, i, j: INTEGER
	do
		Io.put_string("%N > call to SORT_ALG.bubble_sort()");
		FROM
			i := 0
		UNTIL
			i < arr.count
		LOOP
			FROM
				j := 0
			UNTIL
				j < (arr.count - i - 1)
			LOOP
				IF arr[j] < arr[j+1] xor ascending
				THEN
					buf := arr[j];
					arr[j] := arr[j+1];
					arr[j+1] := buf;
				END
				
				j := j + 1;
			end
			
			i := i + 1;
		end
	end
end

