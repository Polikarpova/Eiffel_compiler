class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make

feature {NONE} -- Initialization

	make
			-- Run application.
		local
			var,xstr:STRING -- "My Text first"
			Caty:CAT
		do
			--| Add your code here
			var := "My Text first"
			print ("Hello Eiffel World!%N")
			Io.put_string (var)
			Io.new_line
			Io.put_integer (demo(2,1))
			Io.new_line
			Io.put_integer (xxx+(-2))
			create Caty.newCat
		end

	demo(diff, diff2 : INTEGER): INTEGER
	local
		xxx,zzz: INTEGER
	do
		Result := 999 + diff
	end

end


-- another file
class
	CAT

  -- hello. it's me. i'm here
  -- hello. it's me. I`m back
  create
    newCat, make
  feature {ANY}
	newCat(f:INTEGER)
	do
		-- body
	end

feature {NONE} -- Initialization

	make
			-- Initialization for `Current'.
		do
			create me.make
			it_.is_[0].a_(long)[1].sequence.of_.calls(12,'3')
			qulified[654].by(obj).procedure
			call_proc
			call_func0()
			call_func1(1)
			call_func2(1,2)
		end
end
