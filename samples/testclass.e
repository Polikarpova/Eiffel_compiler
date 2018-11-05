class TESTCLASS
inherit
    A
		redefine x, y , mtdZZZ
        end

    B
        end

create
	construct2_me, make

feature {APPLICATION}
	make(age:INTEGER;weight:Real)
		do
			print("I'm born")
		end
	meth1(): REAL
		LOCAL myLoc:STRING
		AmI_OK, cat_exists: BOOLEAN
		i: INTEGER
		do
			--REsult := 2*(2+2)
			
			if NOT i then
				Result := false
			elseif i = 4^2 then
				Result := "hmm"
			else
				Resul := true
			end
			
			from
			until
				1 >= 10
			loop
				Result := 1 + 1
			end
			
			from
				Result := 666
			until
				666 implies 9.7
			loop
				Result := (8^0) XOR 7
			end
			
		end
feature
	attr2 : REAL
feature {CLASS2, CLIENT5}
	testClients : CHARACTER --attribute
	emptyMethod
		do
		end
end

Class TRIVIAL 
end

Class INHERIT_only 
inherit
    A
		end
    TRIVIAL
		end
end
