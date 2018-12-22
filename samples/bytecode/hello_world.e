class ARRAY_TEST
create
	make

feature
	make
	local
		arr: ARRAY[INTEGER]
	do
		
		CREATE arr.make(0, 5)

		arr[0] := 44;
		arr[1] := 53;
		arr[2] := 24;
		arr[3] := 14;
		arr[4] := 5;
		arr[5] := 0;
		
		Io.put_string("Start array: %N");
		Io.put_string("%TElements count: ");
		Io.put_integer(arr.count);
		
		print_arr(arr);
		
		Io.put_string("%N%NSorting...%N%N");
		bubble_sort(arr);
		
		Io.put_string("Sorted array: %N");
		
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
	
	bubble_sort(arr:ARRAY[INTEGER])
	local
		buf, i, j: INTEGER
	do
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
				
				IF arr[j] > arr[j+1] THEN
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

