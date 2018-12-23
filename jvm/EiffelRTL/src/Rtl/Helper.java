package rtl;
 
/**
 *
 * @author Пользователь
 */
public class Helper {
    
    //возведение в степень
    public int powerI(int left, int right) {
        return (int)Math.pow(left, right);
    }    
    public float powerF(float left, float right) {
    
        return (float)Math.pow(left, right);
    }
    
    //cкладывание строк
    public String addS(String left, String right) {
        return left+right;
    }
    
    //==
    public boolean equalI(int left, int right) {
        return left == right;
    }
    public boolean equalF(float left, float right) {
        return left == right;
    }   
    public boolean equalS(String left, String right) {
        
        return left.compareTo(right) == 0;
    }
    
    //!=
    public boolean notEqualI(int left, int right) {
        return left != right;
    }
    public boolean notEqualF(float left, float right) {
        return left != right;
    }   
    public boolean notEqualS(String left, String right) {
        return left.compareTo(right) != 0;
    }
    
    //<
    public boolean lessI(int left, int right) {
        return left < right;
    }
    public boolean lessF(float left, float right) {
        return left < right;
    }   
    public boolean lessS(String left, String right) {      
        return left.compareTo(right) < 0;
    }
    
    //>
    public boolean greaterI(int left, int right) {
        return left > right;
    }
    public boolean greaterF(float left, float right) {
        return left > right;
    }   
    public boolean greaterS(String left, String right) {      
        return left.compareTo(right) > 0;
    }
    
    //<=
    public boolean lessOrEqualI(int left, int right) {
        return left <= right;
    }
    public boolean lessOrEqualF(float left, float right) {
        return left <= right;
    }   
    public boolean lessOrEqualS(String left, String right) {              
        return lessS(left, right) || equalS(left, right);
    }
    
    //>=
    public boolean greaterOrEqualI(int left, int right) {
        return left >= right;
    }
    public boolean greaterOrEqualF(float left, float right) {
        return left >= right;
    }   
    public boolean greaterOrEqualS(String left, String right) {              
        return greaterS(left, right) || equalS(left, right);
    }
    
    public boolean or(boolean left, boolean right) {
        return left || right;
    }
    
    public boolean xor(boolean left, boolean right) {
        return left ^ right;
    }
    
    public boolean and(boolean left, boolean right) {
        return left && right;
    }
 
    public boolean implies(boolean left, boolean right) {
        return (!left) || right;             
    }
	
	public int verifyArrayMake(int lower, int upper) {
		String error_info = "";
		if(lower != 0) {
			error_info += "\n ignoring `lower` = " + lower + ". Values other than zero are not supported.";
		}
		if(upper < 0) {
			error_info += "\n ignoring negative `upper` = " + upper + ". Defaulting to 0.";
			upper = 0;
		}
		if( ! error_info.isEmpty() )
			System.out.println("/!\\ Warning: Invalid prerands passed to `ARRAY.make(lower, upper)` :" + error_info);
		
		return upper + 1;
	}
}
