class EIFFEL_TEST
create
	make

feature
	workers : ARRAY[SORTER]
	
	make
	local
		sorter1 : SORTER
		bubble : BUBBLE_SORTER
		quick : QUICK_SORTER
		empty : EMPTY_SORTER
		
		arr: ARRAY[INTEGER]
		
		i : INTEGER
	do
		CREATE arr.make(0, 5)
		arr[0] := 9*3;
		arr[1] := 90/2;
		arr[2] := 7^2;
		arr[3] := 8-18;
		arr[4] := 1+5;
		
		CREATE workers.make(0, 3)
		CREATE sorter1.init
		CREATE bubble.init
		CREATE quick.init
		quick.use_bubble := true;
		CREATE empty.init
		
		workers[0] := sorter1;
		workers[1] := bubble;
		workers[2] := quick;
		workers[3] := empty;
		
		FROM
			I := 0
		UNTIL
			i = workers.count
		LOOP
			Io.put_string("%N i: "); Io.put_integer(i);
			arr := workers[i].sort(arr)
			
			i := i + 1;
		END
		
		Io.put_string("%N%NSorted array:");
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

class EMPTY_SORTER inherit SORTER
create
	init
	
feature {none}
	init -- creator
	do
	end
feature

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

feature
	make
	do end

feature {SORTER}
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

