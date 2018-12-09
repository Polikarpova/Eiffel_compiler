/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rtl;

/**
 *
 * @author Пользователь
 */
public class Io {
    
    public static void put_string( String v ) {
    
        System.out.print(v);
    }
    
    public static void put_integer( int v) {
        System.out.print(v);
    }
    
    public static void put_real( double v) {
    
        System.out.print(v);
    }
    
    public static void put_boolean( boolean v) {
    
        System.out.print(v ? "True" : "False");
    }
    
    public static void new_line() {
    
        System.out.println();
    }
}
