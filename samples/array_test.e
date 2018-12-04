--fjfjf

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

class TESTCLASS
feature
 chain
	do
	--103 - x.y.z.func(00,actuals+15/3^2*9-1)[B2.d.e(1,2)[ind].f.g].b.c
	--NOT a.b.c(1).d.e ^ 2
	--4 ^ A.B.C[2].D.E
	--8 * (A.B.C)(3).D.E
	--alive(1)[2][3].x.y(6)
	4+(16+7)*5
	a[1].a[1].f.a[2]
	a[2][2][2][2]
	a[3][3].f[3][3]
	a[4][4].f(14)[4][4]
	f.f.f.a[1].f.f	
	end
end
