class ARRAY_TEST
create
	make

feature
	make
	do
		if 1 /= 2 then
			io.put_string("not eq!")
		else
			io.put_string("equal!")
		end
		
	end
end

