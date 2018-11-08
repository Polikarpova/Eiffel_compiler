class NESTCLASS
feature {APPLICATION}
	make
		do
			create arr.make(0,4);
			
			from
				i := 1
			until
				i /= 5
			loop
			
				Io.put_integer(arr[i]);
				i := (i + 1) := 45 := arr[i];

				if NOT i then
					Result := false
				else
					if i = 4^2 then
						Result := "hmm" + "...";
					end
				end
			end
		end
end
