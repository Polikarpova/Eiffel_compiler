class TESTCLASS

create
	make

feature
	make
		do
			print("I'm born")
		end
end

class APPLICATION

inherit ARGUMENTS_32

create
	make

feature {NONE} -- Initialization

	make
			-- Run application.
		local
			test_class: TESTCLASS
		do
			--создать переменную нужного класса, а затем вместе с create вызвать make из созданной переменной-объекта
			create test_class.make
end

