class START
create
	make

feature
	sa: ARRAY[String]
	make
	local
		ia: ARRAY[Integer]
		i0: INTEGER 
		s: BUBBLE_SORTER
	do
		-- CREATE s -- `make` is called
--		if s.ascending then    end
		-- ia := s.sort2(ia) -- BUBBLE_SORTER
		-- ia := s.sort(ia)  -- SORTER
		-- ia := s.bubble(ia, true)-- SORT_ALG

	end
end


class
	SORT_ALG

feature {NONE}
	init
	do

	end
feature {NONE}
	bubble(arr : ARRAY[INTEGER] ; ascending: BOOLEAN) : ARRAY[INTEGER]
	do
			Result := arr
	end
end

class
	SORTER

	inherit
		SORT_ALG 
		-- redefine init end

feature {ANY}
	-- init do  end

feature {none}
	ascending: BOOLEAN

feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		i, buf: INTEGER
	do
		IF ascending THEN
			Result := arr
		ELSE
			Result := arr
		END
	end
end

class
	BUBBLE_SORTER

	inherit
		SORTER  
		redefine
			ascending --, init
		end

feature 
	ascending : INTEGER
	
	--init	do	end
feature {} -- `{}` equivalent to `{NONE}`
	sort2(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
	local
		i, buf: INTEGER
	do
		IF ascending THEN
			Result := bubble(arr, false)
		ELSE
			Result := arr
		END
	end
end
