class EIFFEL_TEST
create
	make

feature
	worker : QUICK_SORTER
	
	make
	local
		arr: ARRAY[INTEGER]
	do

		Io.put_string("Input array size: ");
		Io.read_integer;
		
		IF Io.last_integer > 2 AND THEN Io.last_integer > getFive THEN 
			Io.put_string("%NSize is greater than 5.");
		END
		
		CREATE arr.make(0, Io.last_integer-1)
		
		-- Io.put_string("CREATE worker.init ... %N");
		CREATE worker.init

		read_arr(arr);
		
		Io.put_string("%NStart array: ");
		Io.put_string("%TElements count: ");
		Io.put_integer(arr.count);
		
		print_arr(arr);
		
		Io.put_string("%N%NSorting...%N");
		
		--worker.reversed
		--arr := worker.sort(arr);
		
		--Io.put_string("%NDescend-sorted array: ");
		--print_arr(arr);
		
		worker.init
		worker.use_bubble := true
		arr := worker.sort(arr);
		
		Io.put_string("%NSorted array: ");
		print_arr(arr);
		
	end
	
	getFive : INTEGER
	do
		Io.put_string("%N% >_ called `getFive()` ");
		Result := 5
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
			Io.put_string("%N%TElement ");
			Io.put_integer(i);
			Io.put_string(": ");
			Io.put_integer(arr[i]);
			
			i := i + 1;
		end
	end
	
	read_arr(arr:ARRAY[INTEGER])
	local
		i:INTEGER
	do
		Io.put_string("Input array elements (one per line):%N")
		FROM
			i := 0
		UNTIL
			i >= arr.count
		LOOP
			
			Io.read_integer
			
			arr[i] := Io.last_integer
			
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
	init -- creator
	do
		forwarded
	end
	
	ascending: BOOLEAN

feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		worker: SORT_ALG
	do
		Io.put_string("%N > call to SORTER.sort()");
		CREATE worker.make
		worker.bubble_sort(arr, ascending)
		Result := arr
	end
end

class BUBBLE_SORTER inherit SORTER
		redefine sort end
create
	init
	
feature {none}
	init -- creator
	do
	end
feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	do
		Io.put_string("%N > call to BUBBLE_SORTER.sort()");
		PRECURSOR(arr)
		Result := arr
	end

end

class QUICK_SORTER inherit BUBBLE_SORTER
		redefine sort end
create
	init
	
feature {none}
	init -- creator
	do
		use_bubble := FALSE
	end
	
	
feature
	use_bubble: BOOLEAN

	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		worker: SORT_ALG
	do
		Io.put_string("%N > call to QUICK_SORTER.sort()");
		
		IF use_bubble THEN
			PRECURSOR(arr)
		ELSE
			CREATE worker.make
			worker.qsort(arr, 0, arr.count-1);
		end

		Result := arr
	end
end

class SORT_ALG
create
	make

feature {SORTER}
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
			i >= arr.count
		LOOP
			FROM
				j := 0
			UNTIL
				j >= (arr.count - i - 1)
			LOOP
				IF ascending xor arr[j] < arr[j+1]
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
	
	
feature {QUICK_SORTER}
	qsort(a : ARRAY[INTEGER]; start: INTEGER; endd:INTEGER)
	local
		buf,p:INTEGER
		i, j : iNTEGER
	do
		
		--указатели на исходные места есть: start и endd
		--получаем элемент посередине куска [start;endd]
		p := start + (endd-start)/2;
		p := a[p];
		
		--перераспределяем элементы в массиве
		FROM
			i := start
			j := endd
		UNTIL
			NOT ( i <= j)
		LOOP
			
			FROM
			UNTIL
				NOT (a[i] < p)
			LOOP
				i := i + 1;
			END
			
			FROM
			UNTIL
				NOT (a[j] > p)
			LOOP
				j := j - 1;
			END
			
			IF i <= j THEN
			  buf := a[i];
			  a[i] := a[j];
			  a[j] := buf;
			  i := i + 1;
			  j := j - 1;
			END
			
		end
		
		IF j > start THEN
			qsort(a, start, start+j);
		END
		
		IF i < endd THEN
			qsort(a, i, endd);
		END
	end

end

