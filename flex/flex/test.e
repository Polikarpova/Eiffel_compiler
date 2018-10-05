5.6
--
5..6
--
5...6
--
5.. 6
--
5..		6
--
5.. 	 6
--
5	 .. 6
--
5	..6
--
5  .. 6
--

agent_real
real_inspect

-1_234_567e123
+0.066e-13
2e2
'%A'
"%A%/20/%/32/%/65/%/120/%/220/%/255/"
"%!%B%C%D%F%H%L%N_%Q%R%S%T-%V+%%%'%"%(%)%<%>"


-- a simple Hello world
claSs
    HELLO_WORLD
create
    say_it
feature
    say_it
        do
            Io.put_string ("Hello World!");
        end
end

-- Features example
class
    BAKERY
feature
    
    number_of_cakes : INTEGER
        -- A variable containing an integer
    name_of_my_favourite_cake : STRING
        -- A variable containing a string
    price_of_one_cake : REAL
        -- A variable containing a floating point number
    buy_cake (price : REAL; flavour : STRING, fake : Void)   -- A function accepting arguments
		local x  : INTEGER
        do
            -- Some code here...
			x := -0c666-111_222_333
			x := 080_404.505
			x := +2.6
			x := 0b101_001 + -0xA_2
			
			Io.put_string ("double--quoted--multi-
-line--string--with--special--%%--char")
        end
    is_cake_available : BOOLEAN   -- A function returning true or false 
        do
            Result := number_of_cakes > 0  OR  FALSE
        end
end
