class APPLICATION

create
	make

feature
	make
	LOCAL
		i: INTEGER
		arr: ARRAY[INTEGER]
	do

		--создаем заполненный массив на 4 элемента
		--но я не поняла, чем он его заполняет...
		--думаю, можно просто make(int) сделать и нормально будет
		create arr.make_filled(4);
		
		from
			--я так поняла, что в eiffel нумерация с 1 идет
			i := 1
		until
			i != 5
		loop
			Io.put_integer(arr[i]);
			i := i + 1;
		end
		
	end
end
