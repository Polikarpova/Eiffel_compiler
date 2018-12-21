/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Rtl;
 
/**
 *
 * @author Пользователь
 */
public class Helper {
    
    //возведение в степень
    public int power(int left, int right) {
        return (int)Math.pow(left, right);
    }    
    public float power(float left, float right) {
    
        return (float)Math.pow(left, right);
    }
    
    //==
    public boolean equal(int left, int right) {
        return left == right;
    }
    public boolean equal(float left, float right) {
        return left == right;
    }   
    public boolean equal(String left, String right) {
        
        return left.compareTo(right) == 0;
    }
    
    //!=
    public boolean notEqual(int left, int right) {
        return left != right;
    }
    public boolean notEqual(float left, float right) {
        return left != right;
    }   
    public boolean notEqual(String left, String right) {
        return left.compareTo(right) != 0;
    }
    
    //<
    public boolean less(int left, int right) {
        return left < right;
    }
    public boolean less(float left, float right) {
        return left < right;
    }   
    public boolean less(String left, String right) {      
        return left.compareTo(right) < 0;
    }
    
    //>
    public boolean greater(int left, int right) {
        return left > right;
    }
    public boolean greater(float left, float right) {
        return left > right;
    }   
    public boolean greater(String left, String right) {      
        return left.compareTo(right) > 0;
    }
    
    //<=
    public boolean lessOrEqual(int left, int right) {
        return left <= right;
    }
    public boolean lessOrEqual(float left, float right) {
        return left <= right;
    }   
    public boolean lessOrEqual(String left, String right) {              
        return less(left, right) || equal(left, right);
    }
    
    //>=
    public boolean greaterOrEqual(int left, int right) {
        return left >= right;
    }
    public boolean greaterOrEqual(float left, float right) {
        return left >= right;
    }   
    public boolean greaterOrEqual(String left, String right) {              
        return greater(left, right) || equal(left, right);
    }
    
    public boolean or(boolean left, boolean right) {
        return left || right;
    }
    
    public boolean orElse(boolean left, boolean right) {
        
        if (left)
            return true;
        else 
            return or(left, right);       
    }
    
    public boolean xor(boolean left, boolean right) {
        return left ^ right;
    }
    
    public boolean and(boolean left, boolean right) {
        return left && right;
    }
    
    public boolean andThen(boolean left, boolean right) {
        
        if (left)
            return true;
        else 
            return and(left, right);       
    }
 
    public boolean implies(boolean left, boolean right) {
        
        if (!left)
            return true;
        else 
            return right;       
    }
}
