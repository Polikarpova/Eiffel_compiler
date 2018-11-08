class
    B

feature
    f
        do
            -- Some different code...
        end
    g
        do
            -- Some different code...
        end

   x do  end

end

class
    INHERITCLASS

inherit
 B
		-- другие последовательности невалидны
        --rename f as f_B
        --undefine g
		redefine x
		end

feature g do end
feature x do end
end
