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
	meth1(): REAL -- possibly wrong (TODO: check)
		LOCAL myLoc:STRING
		AmI_OK, cat_exists: BOOLEAN
		i: INTEGER
		arr: ARRAY[INTEGER]
		do
			--make
			--REsult := 2*(2+2)
			
			create arr.make(0,4);
			
			from
				i := 1
			until
				i /= 5
			loop
			
				Io.put_integer(arr[i]);	i := i + 1;
				--meth1() -- must cause an error
				arr[i][n(x)][4].call(arr[y],125)
			end
			
			
			if NOT i then
				Result := false
			elseif i = 4^2 then
				Result := "hmm"
			else
				Result := true
			end
			
			from
			until
				Result >= 10
			loop
				Result := (8^Result) XOR 7
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
