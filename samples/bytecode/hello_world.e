class EIFFEL_TEST
create
	make

feature
	worker : QUICK_SORTER
	
	make
	local
		arr: ARRAY[INTEGER]
		arrF: ARRAY[REAL]
		r: REAL
		n: INTEGER
		b: BOOLEAN
	do
	
		b:= 2.5 < 5 and 2.5 <= 5;
		Io.put_boolean(b);
		Io.new_line;
		b:= 2.5 > 5 or 2.5 >= 5
		Io.put_boolean(b);
		Io.new_line
		b:= 25 < 50.5 and 25 <= 50.5;
		Io.put_boolean(b);
		Io.new_line;
		b:= 25 > 50.5 or 25 >= 50.5
		Io.put_boolean(b);
		Io.new_line
		
		n:= 5;
		r := 2.5;

		Io.put_real(n);
		Io.new_line
		
		r:= n+n/r;
		Io.put_real(r);
		Io.new_line
		
		r:= n+r;
		Io.put_real(r);
		Io.new_line
		
		r:= n-r;
		Io.put_real(r);
		Io.new_line
		
		r:= n/r;
		Io.put_real(r);
		Io.new_line
		
		
--		Io.put_boolean( NOT true OR ELSE true implies NOT NOT false );
--		Io.new_line

		Io.put_string("Input array size: ");
		Io.read_integer;
		CREATE arr.make(0, Io.last_integer-1)
		CREATE arrF.make(0, Io.last_integer-1)
		
		-- Io.put_string("CREATE worker.init ... %N");
		CREATE worker.init

		read_arr(arr);
--		arr[0] := -+55;
--		arr[1] := 6^2;
--		arr[2] := +24;
--		arr[3] := +-37;
--		arr[4] := -5;
--		arr[5] := 0;
		
		-- conversion test
		-- arrF := arr; -- should fail
		Io.put_string(">_ arrF[0] := arr[0] : ");
		arrF[0] := arr[0]; -- should work OK
		Io.put_real(arrF[0]);
		Io.new_line
		
		Io.put_string("%NStart array: ");
		Io.put_string("%TElements count: ");
		Io.put_integer(arr.count);
		
		print_arr(arr);
		
		Io.put_string("%N%NSorting...%N");
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
	end
	
	qsort(a : ARRAY[INTEGER]; start: INTEGER; end:INTEGER)
	local
		buf,p:INTEGER
		i, j : iNTEGER
	do
		--указатели на исходные места есть: start и end
		--получаем элемент посередине куска [start;end]
		p := start + (end-start)/2;
		p := a[p];
		
		--перераспределяем элементы в массиве
		FROM
			i := start
			j := end
		UNTIL
			i > j
		LOOP
			
			FROM
			UNTIL
				a[i] >= p
			LOOP
				i := i + 1;
			END
			
			FROM
			UNTIL
				a[j] <= p
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
		
		IF j > 0 THEN
			qsort(a, start, start+j);
		END
		
		IF (end - start) > i THEN
			qsort(a, start+i, end - start-i);
		END
	end
feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	do
		Io.put_string("%N > call to QUICK_SORTER.sort()");
		qsort(arr, 0, arr.count-1);
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
end

