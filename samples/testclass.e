class TESTCLASS

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
		do
			REsult := 3.14159
		end
feature
	attr2 : REAL
feature {CLASS2, CLIENT5}
	testClients : CHARACTER --attribute
	emptyMethod
		do
		end
end
