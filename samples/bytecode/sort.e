class START
create
	make

feature
	b: ARRAY[String]
	make
	local
		i0: INTEGER
		s: BUBBLE
	do
		CREATE s -- `make` is called
--		if s.ascending then    end
		s.init

	end
end


class
	SORT_ALG

feature {NONE}
	init
	do

	end
feature {}
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
	BUBBLE

inherit
	SORTER  
		-- redefine
		-- sort --, init
		 -- end

feature {NONE}
	--init	do	end
feature
	sort(arr : ARRAY[INTEGER]) : ARRAY[INTEGER]
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
