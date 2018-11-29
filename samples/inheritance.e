class
    A

feature
    f
        do
            -- Some code...
        end
    g
        do
            -- Some code...
        end

end

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

end

class
    C

inherit
    A
        --rename
          --  f as A_f    -- The feature f inherited from A is now called A_f within C
		redefine x
        end

    B
        --undefine
        --    g           -- The feature g inherited from B is no longer part of C
        --end

-- feature

end