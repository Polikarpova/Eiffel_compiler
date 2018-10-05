class Cat
  -- hello. it's me. i'm here
  -- hello. it's me. I`m back
  create
    newCat(!)
end

inspect f
	when 1 then
		-- Code when input_integer equals 2
	when 3, 5 then
		-- Code when input_integer equals 3 or 5
	when 7.. 9 then
		-- Code when input_integer equals 7 or 8 or 9
	when 10 ..13 then
		-- Code when input_integer equals 7 or 8 or 9
	else
		-- Code when input_integer does not equal 2, 3, 5, 7, 8 nor 9
end

f:= 7
across 1|..| f as it loop
	Io.put_integer (it.item)
    Io.new_line
end