class Cat
  -- hello. it's me. i'm here
  -- hello. it's me. I`m back
  create
    newCat, make
  feature {ALL}
	newCat
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
			-- Run application.
		local
			var:STRING -- := "My Text first"
		do
			--| Add your code here
			var := "My Text first"
			print ("Hello Eiffel World!%N")
			Io.put_string (var)
			Io.put_integer (demo)
		end

	demo(): INTEGER
	do

	end

end
