note
	description: "test_project application root class"
	date: "$Date$"
	revision: "$Revision$"

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
			var,xstr:STRING -- := "My Text first"
		do
			--| Add your code here
			var := "My Text first"
			print ("Hello Eiffel World!%N")
			Io.put_string (var)
			Io.new_line
			Io.put_integer (demo(2,1))
			Io.new_line
			Io.put_integer (xxx+(-2))
		end

	demo(diff, diff2 : INTEGER): INTEGER
	do
		Result := 999 + diff
	end
	xxx,zzz: INTEGER

end

note
	description: "Summary description for {CAT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

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
		inspect f
			when 1 then
				-- Code when input_integer equals 2
			when 3, 5 then
				-- Code when input_integer equals 3 or 5
			when 7.. 9 then
				-- Code when input_integer equals 7 or 8 or 9
			when 10..13 then
				-- Code when input_integer equals 7 or 8 or 9
			else
				-- Code when input_integer does not equal 2, 3, 5, 7, 8 nor 9
		end
	end

feature {NONE} -- Initialization

	make
			-- Initialization for `Current'.
		do
			create me
			it_.is_.a_(long).sequence.of_.calls(123)
			qulified.by(obj).procedure
			call_proc
			call_func0()
			call_func1(1)
			call_func2(1,2)
		end

end
