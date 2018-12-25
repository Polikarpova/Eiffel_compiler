EIFFEL_TEST (main)



class SORTER
   /      \
  /        \
class EMPTY_SORTER inherit SORTER
             \
			  \
class BUBBLE_SORTER inherit SORTER
		redefine sort end
		|    
		|     
class QUICK_SORTER inherit BUBBLE_SORTER
		redefine sort end


		
class SORT_ALG
{
feature {SORTER}
	bubble_sort(arr:ARRAY[INTEGER] ; ascending: BOOLEAN)
	
feature {QUICK_SORTER}
	qsort(a : ARRAY[INTEGER]; start: INTEGER; endd:INTEGER)
}